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

void TraceRay(const Scene& scene, const Ray& ray, const HitInfo& hitInfo, RGB& color)
{
	const BRDF* brdf = hitInfo.object->Brdf();
	double cosTheta = glm::dot(hitInfo.normal, -ray.Dir());

	if(brdf->IsDiffuse())
	{
		DirectIllumination(scene, hitInfo, cosTheta, color);
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