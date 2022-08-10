#include <iostream>
#include <utility>
#include <memory>

#include "util/image.h"
#include "scene.h"
#include "objects/sphere.h"
#include "util/colors.h"
#include "objects/pointLight.h"
#include "objects/triangle.h"
#include "objects/triangleMesh.h"

#include "BRDF.h"
#include "camera.h"
#include "viewport.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
#include "lame/benchmark.h"

int main()
{
	Camera cam({0,-5,2}, {0,1,0}, {0,0,1});
	cam.LookAt({0,0,0});
	//Camera cam({0,-2,0}, {0,1,0}, {0,0,1});
	Viewport vp(640, 640, M_PI / 2);
	Image img(vp.Width(), vp.Height());
	BRDF brdf;
	BRDF brdf2(Colors::blueviolet, 0, 0, 1);
	BRDF brdf3(Colors::tomato, 0, 0, 1);

	Sphere sphere({0,0,0}, 0.5);

	TriangleMesh quad({Vec3(-1,-1,0),Vec3(1,-1,0),Vec3(1,1,2),Vec3(-1,1,0)},{Vec3i(0,1,2),Vec3i(2,3,0)});
	PointLight light({0,0,20}, Colors::yellow, 0.1);

	std::vector<Sphere*> spheres;

	Scene scene;
	scene.SetBackground(Colors::darkgray);

	double r = 3;
	for(int i = 0; i < 10; i++)
	{
		Vec3 pos(cos(i * M_PI * 2 / 10) * 3, sin(i * M_PI * 2 / 10) * 3, 0);
		spheres.push_back(new Sphere(pos, 0.25, &brdf3));
		scene.AddObject(spheres[i]);
	}
	scene.AddObject(&sphere);
	scene.AddObject(&quad);
	scene.AddLight(&light);
	scene.ConstructBvh();

	for(int i = 0; i < vp.Height(); i++)
	{
		for(int j = 0; j < vp.Width(); j++)
		{
			double x = (2.0 * (j + 0.5) / vp.Width() - 1.0) * tan(vp.HFOV() / 2.f) * vp.AspectRatio();
			double y = (1 - 2.0 * (i + 0.5) / vp.Height()) * tan(vp.HFOV() / 2.f);

			Ray ray(cam.Position(), x * cam.Right() + y * cam.Up() + cam.Dir());

			RGB col = {0,0,0};

			HitInfo hitInfo;

			if(scene.Hit(ray, cam.NearPlane(), cam.FarPlane(), hitInfo))
			{
				double scaler = glm::dot(scene.Lights()[0]->Pos() - hitInfo.point, hitInfo.normal);
				col = hitInfo.object->Brdf()->Diffuse() * scaler * scene.Lights()[0]->Intensity();
			}
			else
			{
				col = scene.Background();
			}

			img.bitmap[j + i * img.nx][0] = (char)(255 * std::max(0., std::min(1., col[0])));
			img.bitmap[j + i * img.nx][1] = (char)(255 * std::max(0., std::min(1., col[1])));
			img.bitmap[j + i * img.nx][2] = (char)(255 * std::max(0., std::min(1., col[2])));
		}
	}

	img.write("./a.ppm");

	std::cout << "Light is Very Hard, yo\n";
}