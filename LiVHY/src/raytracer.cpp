#include "pch.h"
#include "raytracer.h"
//#include <filesystem>

// TODO add for area lights and emissive meshes
void DirectIllumination(const Scene& scene, const HitInfo& hitInfo, RGB& color)
{
	for(const Light* light : scene.Lights())
	{
		double distToLight = glm::distance(light->Pos(), hitInfo.point);
		HitInfo shadowHit;
		Vec3 lightDir = glm::normalize(light->Pos() - hitInfo.point);
		Vec3 shadowOrig = hitInfo.point + hitInfo.normal * c_Epsilon;

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
}

// Returns a random direction given a normal
// Uses cosine-weighted hemisphere sampling
static inline glm::vec3 sampleHemisphereWeighted(const glm::vec3& n)
{
	// Samples cosine weighted positions.
	float r1 = rand() / static_cast<float>(RAND_MAX);
	float r2 = rand() / static_cast<float>(RAND_MAX);
	float theta = acos(sqrt(1.0f - r1));
	float phi = 2.0f * glm::pi<float>() * r2;
	float xs = sinf(theta) * cosf(phi);
	float ys = cosf(theta);
	float zs = sinf(theta) * sinf(phi);
	glm::vec3 y(n.x, n.y, n.z);
	glm::vec3 h = y;

	if((abs(h.x) <= abs(h.y)) && (abs(h.x) <= abs(h.z)))
	{
		h.x = 1.0;
	}
	else if((abs(h.y) <= abs(h.x)) && (abs(h.y) <= abs(h.z)))
	{
		h.y = 1.0;
	}
	else
	{
		h.z = 1.0;
	}

	glm::vec3 x = glm::normalize(glm::cross(h, y));
	glm::vec3 z = glm::normalize(glm::cross(x, y));

	return glm::normalize(xs * x + ys * y + zs * z);
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
	double cosTheta = glm::dot(hitInfo.normal, -ray.Dir());
	double reflCoeff = 0.0;		//fresnel reflection coefficient

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

