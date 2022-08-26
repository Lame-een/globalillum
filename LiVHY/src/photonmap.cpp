#include "pch.h"
#include "photonmap.h"
#include "util/tracerConsts.h"
#include "objects/light.h"
#include "objects/rectLight.h"
#include "objects/pointLight.h"

void ClearMaps()
{
	for(auto photon : g_GlobalPhotons)
	{
		delete photon;
	}
	g_GlobalPhotons.clear();
	for(auto photon : g_CausticPhotons)
	{
		delete photon;
	}
	g_CausticPhotons.clear();
}

void AddPhoton(RGB photon, std::vector<Photon*>& photonStorage, const HitInfo& hitInfo, PhotonType type)
{
	Photon* emittedPhoton = new Photon(hitInfo.point, hitInfo.ray.Dir());
	RGBtoRGBE(photon, emittedPhoton->rgbe);

	photonStorage.push_back(emittedPhoton);
}

void TracePhoton(const Scene& scene, Ray ray, RGB photon, std::vector<Photon*>& photonStorage, PhotonType type, int photonCount)
{
	//do not store first bounce in a caustic map
	bool store = (type != PhotonType::Caustic);
	HitInfo hitInfo;

	//russian roulette
	for(int i = 0; i < c_MaxPhotonDepth &&
		scene.Hit(ray, scene.Cam()->NearPlane(), scene.Cam()->FarPlane(), hitInfo); i++)
	{
		if(photonStorage.size() >= photonCount)
		{
			return;
		}

		const BRDF& brdf = *hitInfo.object->Brdf();
		const double cosTheta = glm::dot(hitInfo.normal, -hitInfo.ray.Dir());

		//diffuse interraction - don't store first caustic hit
		if(brdf.IsDiffuse() && store)
		{
			AddPhoton(photon, photonStorage, hitInfo, type);
		}

		double reflCoeff = 0;
		if(brdf.IsTransparent())
		{
			reflCoeff = SchlicksApprox(ray.Dir(), hitInfo.normal, 1.0, brdf.IOR());
		}

		//generate probabilities for each bounce
		double maxRGBVal = maxChannelValue(photon);
		double probDiffuse = maxChannelValue(brdf.Color() * photon) / maxRGBVal;

		//double probTransmission = probDiffuse; //not using seperate color for transmission
		//double probSpecular = probDiffuse + reflCoeff * probTransmission;
		//probTransmission *= (1.0 - reflCoeff);
		double probTransmission = probDiffuse * (1.0 - reflCoeff); //slight optimization due to using a single color
		double probSpecular = probDiffuse + reflCoeff * probDiffuse;

		double probTerminate = c_RayAbsorptionProbability;
		double probTotal = probDiffuse + probSpecular + probTransmission + probTerminate;

		//scaling down to 1.0, if less than 1.0 the rest is implicit absorption
		double r = lameutil::g_RandGen.getDouble();
		if(probTotal > 1.0)
		{
			r *= probTotal;
		}

		Vec3 sampledDir;

		//bounce and redo
		if(r < probDiffuse)
		{
			//terminate on caustic-diffuse (absorbed)
			if(type == PhotonType::Caustic)
			{
				break;
			}
			else
			{
				store = true;	//always store global photons
			}

			sampledDir = DiffuseSample(hitInfo.normal);

			photon *= brdf.Color() / probDiffuse;
		}
		else if(r < probDiffuse + probTransmission)
		{
			//caustics can store photons after transmission sample
			if(type == PhotonType::Caustic)
			{
				store = true;
			}
			//exact refraction
			
			Vec3 exactDir = TransmissiveRefract(hitInfo);

			//importance sampled refraction
			sampledDir = SpecularSample(exactDir, brdf.Shininess(), cosTheta);

			photon *= (1.0 - reflCoeff) * brdf.Color() / probTransmission;
		}
		else if(r < probDiffuse + probTransmission + probSpecular)
		{
			//caustics can store photons after specular sample
			if(type == PhotonType::Caustic)
			{
				store = true;
			}

			//exact reflection
			Vec3 exactDir = glm::reflect(ray.Dir(), hitInfo.normal);
			//importance sampled reflection
			sampledDir = SpecularSample(exactDir, brdf.Shininess(), cosTheta);

			photon *= (brdf.Color() + reflCoeff * brdf.Color()) / probSpecular;
		}
		else
		{
			//photon was absorbed
			break; //terminate the ray
		}

		ray.SetOrigin(hitInfo.point);	//not necessary to add epsilon due to minimum intersection being epsilon
		ray.SetDir(glm::normalize(sampledDir));
	}
}

void EmitPhotons(const Scene& scene, const Light* light, PhotonType type, int count)
{
	//normalize photon power
	RGB photon = light->Color();
	double photonPower = photon.r + photon.g + photon.b;
	photon /= photonPower;

	std::vector<Photon*> stackStorage;	//keeping initial storage on stack for faster insertions
	stackStorage.reserve(count);

	//emit photon based on light source
	if(light->type == LightType::Rect)
	{
		const RectLight* rect = static_cast<const RectLight*>(light);

		for(int i = 0; i < count; i++)
		{
			//computing random sample point on the light
			double r0 = lameutil::g_RandGen.getDouble() - 0.5;
			double r1 = lameutil::g_RandGen.getDouble() - 0.5;
			Vec3 samplePoint = r0 * rect->Edge(0) + r1 * rect->Edge(1) + rect->Pos();

			//pick ray direction based on diffuse importance sample
			Ray ray(samplePoint, DiffuseSample(rect->Normal()));
			TracePhoton(scene, ray, photon, stackStorage, type, count);
		}
	}
	else if(light->type == LightType::Point)
	{
		const PointLight* point = static_cast<const PointLight*>(light);

		for(int i = 0; i < count; i++)
		{
			Ray ray(point->Pos(), glm::normalize(PointInUnitSphere()));
			TracePhoton(scene, ray, photon, stackStorage, type, count);
		}
	}

	// add local photons to global
	if(type == PhotonType::Global)
	{
		g_GlobalPhotons.insert(g_GlobalPhotons.end(), stackStorage.begin(), stackStorage.end());
	}
	else if(type == PhotonType::Caustic)
	{
		g_CausticPhotons.insert(g_CausticPhotons.end(), stackStorage.begin(), stackStorage.end());
	}
}

void PhotonTracer(const Scene& scene, int globalNum, int causticNum, const std::vector<double>& lightPowers, double totalPower)
{
	//global photon casting
	for(int i = 0; i < scene.Lights().size(); i++)
	{
		EmitPhotons(scene, scene.Lights()[i], PhotonType::Global, (lightPowers[i] / totalPower) * (double)globalNum);
	}

	//caustic photon casting
	for(int i = 0; i < scene.Lights().size(); i++)
	{
		EmitPhotons(scene, scene.Lights()[i], PhotonType::Caustic, (lightPowers[i] / totalPower) * (double)globalNum);
	}
}

void MapPhotons(const Scene& scene)
{
	ClearMaps();

	//calculating total power in scene
	const std::vector<Light*>& lights = scene.Lights();
	std::vector<double> lightPowers(lights.size());
	double totalPower = 0.0;

	for(int i = 0; i < lights.size(); i++)
	{
		lightPowers[i] += lights[i]->Color().r + lights[i]->Color().g + lights[i]->Color().b;
		lightPowers[i] *= lights[i]->Area();
		if(lights[i]->type == LightType::Rect)
		{
			lightPowers[i] *= 4 * M_PI; //flux over hemisphere
		}
		else
		{
			lightPowers[i] *= 4 * M_PI; //flux over sphere
		}
		totalPower += lightPowers[i];
	}


	int photonsPerThread = c_GlobalPhotonCount / c_ThreadCount;
	int causticPhotonsPerThread = c_CausticPhotonCount / c_ThreadCount;

#pragma omp parallel for //poor mans parallelization
	for(int i = 0; i < c_ThreadCount; i++)
	{
		PhotonTracer(scene, photonsPerThread, causticPhotonsPerThread, lightPowers, totalPower);
	}


}