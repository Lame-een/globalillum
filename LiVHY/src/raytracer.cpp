#include "raytracer.h"
#include "glm/geometric.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
#include <filesystem>


//compare performance between normalizing lightDir and using glm::distance in shadowhit
void ComputeIllumination(const Scene& scene, const HitInfo& hitInfo, const Light* light, double cosTheta, RGB& color)
{
	double distToLight = glm::distance(light->Pos(), hitInfo.point);
	HitInfo shadowHit;
	Vec3 lightDir = glm::normalize(light->Pos() - hitInfo.point);
	Vec3 shadowOrig = hitInfo.point + hitInfo.normal * c_Epsilon;

	//probably not necessary?
	//Vec3 shadowOrig = glm::dot(hitInfo.normal, lightDir) < 0 ?
	//hitInfo.point - hitInfo.normal * c_Epsilon : hitInfo.point + hitInfo.normal * c_Epsilon;

	Ray shadowRay(shadowOrig, lightDir);
	shadowRay.Normalize();

	if(scene.Hit(shadowRay, 0, distToLight, shadowHit))
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

void DirectIllumination(const Scene& scene, const HitInfo& hitInfo, double cosTheta, RGB& color)
{
	for(const Light* light : scene.Lights())
	{
		ComputeIllumination(scene, hitInfo, light, cosTheta, color);
	}
}

//return perfect reflective bounce
Vec3 ReflectiveBounce(Vec3 normal, const Vec3& view, double cosTheta)
{
	// Flip normal to incident side of surface
	if(cosTheta < 0)
	{
		normal = -normal;
		cosTheta *= -1.0;
	}

	Vec3 dn = normal * cosTheta;  // dot(normal, view)
	Vec3 refl = view + dn * 2.0;
	return glm::normalize(refl);
}

//return direction of a perfect transmissive bounce (or reflective if internal refraction happened)
Vec3 TransmissiveBounce(const HitInfo& hitInfo, double cosTheta)
{
	double eta;
	Vec3 normal = hitInfo.normal;
	//flip normal if angle is bigger than 90°
	if(cosTheta < 0)
	{
		// exit - assuming air ior 1.0
		eta = hitInfo.object->Brdf()->IOF() / 1.0;
		normal = -normal;
		cosTheta *= -1;
	}
	else
	{
		// entry
		eta = 1.0 / hitInfo.object->Brdf()->IOF();
	}

	double theta = acos(cosTheta);
	double sinPhi = eta * sin(theta);

	//total internal reflection
	if(sinPhi < -1.0 || 1.0 < sinPhi)
	{
		return ReflectiveBounce(normal, hitInfo.ray.Dir(), cosTheta);
	}

	//return refraction direction
	double phi = asin(sinPhi);
	Vec3 viewParallel = glm::normalize(hitInfo.ray.Dir() + normal * cosTheta);
	return glm::normalize(viewParallel * tan(phi) - normal);
}

void TransmissiveIllumination(const Scene& scene, const HitInfo& hitInfo, double cosTheta, double transCoeff, RGB& color)
{
	Vec3 bounce = TransmissiveBounce(hitInfo, cosTheta);
	//...
}

void TraceRay(const Scene& scene, const Ray& ray, const HitInfo& hitInfo, RGB& color)
{
	const BRDF* brdf = hitInfo.object->Brdf();
	double cosTheta = glm::dot(hitInfo.normal, -ray.Dir());
	double reflCoeff = 0.0;		//fresnel reflection coefficient

	if(brdf->IsDiffuse())
	{
		DirectIllumination(scene, hitInfo, cosTheta, color);
	}

	if(brdf->IsTransparent())
	{
		//Schlick's approximation for the reflection coeff - assuming IoR for air 1.0
		double r0 = pow((1.0 - brdf->IOF()) / (1.0 + brdf->IOF()), 2);

		reflCoeff = r0 + (1 - r0) * pow(1 - cosTheta, 5);

		if(reflCoeff < 1.0)
		{
			TransmissiveIllumination(scene, hitInfo, cosTheta, 1 - reflCoeff, color);
		}
	}

	if(brdf->IsGlossy() || reflCoeff > 0)
	{
	}
}

void RayTracer(const Camera& cam, const Viewport& vp, const Scene& scene)
{
	Image img(vp.Width(), vp.Height());

	for(int i = 0; i < vp.Height(); i++)
	{
		for(int j = 0; j < vp.Width(); j++)
		{
			double x = (2.0 * (j + 0.5) / vp.Width() - 1.0) * tan(vp.HFOV() / 2.f) * vp.AspectRatio();
			double y = (1 - 2.0 * (i + 0.5) / vp.Height()) * tan(vp.HFOV() / 2.f);

			Ray ray(cam.Position(), x * cam.Right() + y * cam.Up() + cam.Dir());
			ray.Normalize();
			RGB color(0.0, 0.0, 0.0);

			HitInfo hitInfo;

			if(scene.Hit(ray, cam.NearPlane(), cam.FarPlane(), hitInfo))
			{
				TraceRay(scene, ray, hitInfo, color);
			}
			else
			{
				color = scene.Background();
			}

			img.bitmap[j + i * img.nx][0] = (char)(255 * std::max(0., std::min(1., color[0])));
			img.bitmap[j + i * img.nx][1] = (char)(255 * std::max(0., std::min(1., color[1])));
			img.bitmap[j + i * img.nx][2] = (char)(255 * std::max(0., std::min(1., color[2])));
		}
	}

	img.write("./out/", scene.Name());
}