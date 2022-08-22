#include "pch.h"
#include "raytracer.h"
//#include <filesystem>

// TODO add for area lights and emissive meshes
void DirectIllumination(const Scene& scene, const HitInfo& hitInfo, RGB& color)
{
	for(const Light* light : scene.Lights())
	{
		const double distToLight = glm::distance(light->Pos(), hitInfo.point);
		HitInfo shadowHit;
		Vec3 lightDir = glm::normalize(light->Pos() - hitInfo.point);
		Vec3 shadowOrig = hitInfo.point;

		Ray shadowRay(shadowOrig, lightDir);
		shadowRay.Normalize();

		if(scene.Hit(shadowRay, scene.Cam()->NearPlane(), distToLight, shadowHit))
		{
			if(shadowHit.t < distToLight)
			{
				return;
			}
		}
		color += light->Reflection(hitInfo);
		//color += light->DiffuseReflection(hitInfo);
		//color += light->SpecularReflection(hitInfo);
	}
}

RGB TraceRay(const Scene& scene, const Ray& ray, int depth)
{
	if(depth == c_MaxRaytracerDepth)
	{
		return Colors::black;
	}

	HitInfo hitInfo;
	if(!scene.Hit(ray, scene.Cam()->NearPlane(), scene.Cam()->FarPlane(), hitInfo))
	{
		return scene.Background();
	}

	const BRDF* brdf = hitInfo.object->Brdf();
	const double cosTheta = glm::dot(hitInfo.normal, -ray.Dir());

	if(brdf->IsEmissive())
	{
		if(depth == 0)
		{
			//direct hit from viewport to emissive surface
			return brdf->Emission() + brdf->Emission() * cosTheta;
		}
		else
		{
			return brdf->Emission() * cosTheta;
		}
	}

	RGB colorBuffer = Colors::black;

	// Direct illumination - explicit light sampling
	if(brdf->IsDiffuse())
	{
		DirectIllumination(scene, hitInfo, colorBuffer);
	}


	/*
	// Indirect lighting - currently disable due to noise (not using stratified sampling)
	if(brdf->IsDiffuse())
	{
		//shoot rays and integrate diffuse lighting
		Ray indirectRay(hitInfo.point, DiffuseImportanceSample(hitInfo.normal));
		RGB radiance = TraceRay(scene, indirectRay, depth + 1);

		//ray carries backwards the radiance

		colorBuffer += brdf->DiffuseLighting(-indirectRay.Dir(), hitInfo.normal, radiance);

		//blend colors for reflective/transparent materials
		colorBuffer *= brdf->Opacity(); //* brdf->Reflectivity();
	}
	*/



	// Refract + Reflect
	if(brdf->IsTransparent())
	{
		const double n1 = 1.0;
		const double n2 = brdf->IOR();
		const double schlickCoeffOutside = SchlicksApprox(ray.Dir(), hitInfo.normal, n1, n2);
		Ray refractRay(hitInfo.point, glm::refract(ray.Dir(), hitInfo.normal, n1 / n2));
		double refractCoeff = (1.0 - schlickCoeffOutside) * (1.0 - brdf->Opacity());


		HitInfo refractHit;
		if(scene.Hit(refractRay, scene.Cam()->NearPlane(), scene.Cam()->FarPlane(), refractHit))
		{
			//self-intersect check (only for spheres atm necessary)
			if(hitInfo.object == refractHit.object)
			{
				const double schlickCoeffInside = SchlicksApprox(refractRay.Dir(), -refractHit.normal, n2, n1);

				Ray refractOutRay(refractHit.point, glm::refract(refractRay.Dir(), -refractHit.normal, n2 / n1));
				const double insideRefractCoeff = (1.0 - schlickCoeffInside);

				//depth doesn't increase - same ray
				RGB radiance = insideRefractCoeff * TraceRay(scene, refractOutRay, depth);
				colorBuffer += refractCoeff * brdf->DiffuseLighting(refractRay.Dir(), hitInfo.normal, radiance);
			}
			else
			{
				//ISSUE double calling for hits
				//TODO - can be fixed by splitting trace ray in a raycast/hit and a shading part
				colorBuffer += refractCoeff * TraceRay(scene, refractRay, depth + 1);
			}
		}
		else
		{
			colorBuffer += scene.Background();
		}

		//reflect the rest of the ray
		Ray specularRay(hitInfo.point, glm::reflect(ray.Dir(), hitInfo.normal));
		const double reflectCoeff = schlickCoeffOutside * (1.0 - brdf->Opacity());
		colorBuffer += reflectCoeff * TraceRay(scene, specularRay, depth + 1);
	}


	return colorBuffer;
}

void RayTracer(const Viewport& vp, const Scene& scene)
{
	const Camera& cam = *scene.Cam();

	Image img(vp.Width(), vp.Height());

	int i = 0;
	int lim = vp.Height();
	lameutil::LoadingBar bar(i, lim, "<");
	for(; i < vp.Height(); i++)
	{
		bar.bar();

#pragma omp parallel for
		for(int j = 0; j < vp.Width(); j++)
		{
			double x = (2.0 * (j + 0.5) / vp.Width() - 1.0) * tan(vp.HFOV() / 2.f) * vp.AspectRatio();
			double y = (1 - 2.0 * (i + 0.5) / vp.Height()) * tan(vp.HFOV() / 2.f);

			Ray ray(cam.Position(), x * cam.Right() + y * cam.Up() + cam.Dir());
			ray.Normalize();

			RGB color = TraceRay(scene, ray);

			img.bitmap[j + i * img.nx][0] = (char)(255 * std::max(0., std::min(1., color[0])));
			img.bitmap[j + i * img.nx][1] = (char)(255 * std::max(0., std::min(1., color[1])));
			img.bitmap[j + i * img.nx][2] = (char)(255 * std::max(0., std::min(1., color[2])));
		}
	}

	img.write("./out/", scene.Name());
}

