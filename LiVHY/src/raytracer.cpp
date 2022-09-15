#include "pch.h"
#include "raytracer.h"

RGB TraceRay(const Scene& scene, const Ray& ray, int depth)
{
	if(depth == Settings::raytracerDepth)
	{
		return Colors::black;
	}

	HitInfo hitInfo;
	if(!scene.Hit(ray, scene.Cam()->NearPlane(), scene.Cam()->FarPlane(), hitInfo))
	{
		return scene.Background(ray.Dir());
	}

	ScatterInfo scatterInfo;

	RGB emitted = hitInfo.object->GetMaterial()->Emit(ray, hitInfo);

	if(!hitInfo.object->GetMaterial()->Scatter(ray, hitInfo, scatterInfo))
		return emitted;
	if(scatterInfo.isSpecular)
	{
		return scatterInfo.color
			* TraceRay(scene, scatterInfo.bounceRay, depth + 1);
	}

	Ray scatteredRay;
	double pdfVal = 0.0;

	if(scene.SamplingTargets().size() > 0)
	{
		ObjectsPDF targetsPdf(hitInfo.point);
		targetsPdf.AddObject(scene.SamplingTargets());
		MixturePDF mixturePdf(scatterInfo.Pdf(), &targetsPdf);

		Vec3 scatterDir = glm::normalize(mixturePdf.Generate());
		scatteredRay = Ray(hitInfo.point + scatterDir * c_Epsilon, scatterDir);

		pdfVal = mixturePdf.Value(scatteredRay.Dir());
	}
	else
	{
		Vec3 scatterDir = glm::normalize(scatterInfo.Pdf()->Generate());
		scatteredRay = Ray(hitInfo.point + scatterDir * c_Epsilon, scatterDir);

		pdfVal = scatterInfo.Pdf()->Value(scatteredRay.Dir());
	}
	if(pdfVal == 0.0) return Colors::black;

	return emitted
		+ scatterInfo.color * hitInfo.object->GetMaterial()->ScatterPDF(ray, hitInfo, scatteredRay)
		* TraceRay(scene, scatteredRay, depth + 1) / pdfVal;
}

void RayTracer(const Viewport& vp, const Scene& scene)
{
	std::cout << "\nRendering..." << std::endl;
	const Camera& cam = *scene.Cam();

	Image img(vp.Width(), vp.Height());

	int i = 0;
	int lim = vp.Height();
	lameutil::LoadingBar bar(i, lim, "<=");
	for(; i < vp.Height(); i++)
	{
		bar.bar();
#pragma omp parallel for
		for(int j = 0; j < vp.Width(); j++)
		{
			RGB colorBuffer = Colors::black;
			for(int s = 0; s < Settings::samplesPerPixel; s++)
			{
				double r1 = lameutil::g_RandGen.getDouble();
				double r2 = lameutil::g_RandGen.getDouble();
				double x = (2.0 * (j + r1) / vp.Width() - 1.0) * tan(vp.HFOV() / 2.f) * vp.AspectRatio();
				double y = (1 - 2.0 * (i + r2) / vp.Height()) * tan(vp.HFOV() / 2.f);

				Ray ray(cam.Position(), x * cam.Right() + y * cam.Up() + cam.Dir());
				ray.Normalize();

				colorBuffer += TraceRay(scene, ray);
			}
			colorBuffer *= (1.0 / Settings::samplesPerPixel);

			img.SetPixel(j, i, colorBuffer);
		}
		if(Settings::continuousWrite)
		{
			img.WriteFile("./out/");
		}
	}
	bar.bar();

	img.WriteFile("./out/");
}