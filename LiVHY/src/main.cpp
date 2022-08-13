#include <iostream>
#include <utility>
#include <memory>
#include <filesystem>

#include "util/image.h"
#include "scene.h"
#include "objects/sphere.h"
#include "util/colors.h"
#include "objects/pointLight.h"
#include "objects/triangle.h"
#include "objects/triangleMesh.h"
#include "objects/quad.h"

#include "raytracer.h"

#include "BRDF.h"
#include "camera.h"
#include "viewport.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
#include "lame/benchmark.h"

void cornellBox()
{
	Camera cam({0,-6,1}, {0,1,0}, {0,0,1});
	Viewport vp(640, 640);
	Image img(vp.Width(), vp.Height());


	BRDF brdf0(stringToRGB("#f0f0f0"), 0.0, 0.0, 1.0);
	BRDF brdf1(Colors::crimson, 0.0, 0.0, 1.0);
	BRDF brdf2(Colors::limegreen, 0.0, 0.0, 1.0);
	BRDF brdf3(Colors::blueviolet, 0.0, 0.0, 1.0);
	BRDF brdfEmissive(Colors::white, 0.0, 0.0, 1.0);
	brdfEmissive.SetEmission(Colors::white);

	Quad floor(Vec3(-2, -2, -1), Vec3(2, -2, -1), Vec3(2, 2, -1), Vec3(-2, 2, -1), &brdf0);
	Quad ceiling(Vec3(2, -2, 3), Vec3(-2, -2, 3), Vec3(-2, 2, 3), Vec3(2, 2, 3), &brdf0);
	Quad leftWall(Vec3(-2, -2, -1), Vec3(-2, 2, -1), Vec3(-2, 2, 3), Vec3(-2, -2, 3), &brdf1);
	Quad backWall(Vec3(-2, 2, -1), Vec3(2, 2, -1), Vec3(2, 2, 3), Vec3(-2, 2, 3), &brdf2);
	Quad rightWall(Vec3(2, 2, -1), Vec3(2, -2, -1), Vec3(2, -2, 3), Vec3(2, 2, 3), &brdf3);
	Quad emissiveQuad(Vec3(0.5, -0.5, 2.99), Vec3(-0.5, -0.5, 2.99), Vec3(-0.5, 0.5, 2.99), Vec3(0.5, 0.5, 2.99), &brdfEmissive);

	Sphere sphere0(Vec3(0.5, 0.5, 0.0), 1);
	Sphere sphere1(Vec3(-1, -1, -0.5), 0.5);

	PointLight light({0,0,1}, Colors::white, 1);

	Scene scene;
	scene.SetBackground(Colors::black);

	scene.AddLight(&light);

	scene.AddObject(&floor);
	scene.AddObject(&ceiling);
	scene.AddObject(&leftWall);
	scene.AddObject(&rightWall);
	scene.AddObject(&backWall);
	scene.AddObject(&emissiveQuad);
	scene.AddObject(&sphere0);
	scene.AddObject(&sphere1);

	scene.ConstructBvh();

	RayTracer(cam, vp, scene);
}

//use this, very fast and good.
void branchlessONB(const Vec3& n, Vec3& b1, Vec3& b2)
{
	float sign = copysignf(1.0f, n.z);
	const float a = -1.0f / (sign + n.z);
	const float b = n.x * n.y * a;
	b1 = Vec3(1.0f + sign * n.x * n.x * a, sign * b, -sign * n.x);
	b2 = Vec3(b, sign + n.y * n.y * a, -n.y);
}


int main()
{
	cornellBox();
	return 0;
	//Camera cam({0,-5,2}, {0,1,0}, {0,0,1});
	//cam.LookAt({0,0,0});

	Camera cam({0,-6,1}, {0,1,0}, {0,0,1});
	Viewport vp(640, 640);
	Image img(vp.Width(), vp.Height());

	BRDF brdf(Colors::darkcyan, 0, 0, 1);
	BRDF brdf2(Colors::blueviolet, 0, 0, 1);
	BRDF brdf3(Colors::tomato, 0, 0, 1);



	Scene scene;
	scene.SetBackground(Colors::darkgray);

	PointLight light({0,0,1}, Colors::white, 1);
	Sphere sphere({0,0,0}, 0.5);
	TriangleMesh quad1({Vec3(-1,-1,-0.5),Vec3(1,-1,-0.5),Vec3(1,1,0),Vec3(-1,1,0)},{Vec3i(0,1,2),Vec3i(2,3,0)});

	std::vector<Sphere*> spheres;
	double r = 3;
	for(int i = 0; i < 10; i++)
	{
		Vec3 pos(cos(i * M_PI * 2 / 10) * 3, sin(i * M_PI * 2 / 10) * 3, 0);
		spheres.push_back(new Sphere(pos, 0.25, &brdf3));
		scene.AddObject(spheres[i]);
	}
	scene.AddObject(&sphere);
	scene.AddObject(&quad1);
	scene.ConstructBvh();

	scene.AddLight(&light);

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
				col = hitInfo.object->Brdf()->Diffuse() * scaler * 50.0 * scene.Lights()[0]->Intensity() / glm::distance2(scene.Lights()[0]->Pos(),hitInfo.point);
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

	std::filesystem::create_directory("./out");
	//img.write("./out/a.ppm");

	std::cout << "Light is Very Hard, yo\n";
}