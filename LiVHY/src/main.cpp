#include "pch.h"
//#include <iostream>
//#include <utility>
//#include <memory>
//#include <filesystem>

//#include "util/colors.h"
#include "demos/demos.h"
#include "util/image.h"
#include "scene.h"
#include "objects/sphere.h"
#include "objects/triangle.h"
#include "objects/triangleMesh.h"
#include "objects/quad.h"

#include "raytracer.h"

#include "glm/gtx/string_cast.hpp"

#include "camera.h"
#include "viewport.h"

#include "nanoflann.hpp"
#include <iomanip>

//#include "glm/gtx/norm.hpp"
//#include "lame/benchmark.h"

void cornellBox()
{
	Viewport vp(Settings::imgWidth, Settings::imgHeight, Settings::fov);
	Camera cam({0,-6,1}, {0,1,0}, {0,0,1});

	Diffuse mat0(stringToRGB("#f0f0f0"));
	Transmissive mat1(1.4);
	Diffuse mat2(Colors::limegreen);
	Diffuse mat3(Colors::blue);
	Diffuse mat4(Colors::white);
	Specular mat5(Colors::lightgray, 0.2);
	Diffuse mat6(Colors::crimson);
	Light matEmissive(Colors::white, 50);

	Quad floor(Vec3(-2, -2, -1),
			   Vec3(2, -2, -1),
			   Vec3(2, 2, -1),
			   Vec3(-2, 2, -1), &mat0);
	Quad ceiling(Vec3(-2, -2, 3),
				 Vec3(-2, 2, 3), Vec3(2, 2, 3),
				 Vec3(2, -2, 3), &mat0);
	Quad leftWall(Vec3(-2, -2, -1),
				  Vec3(-2, 2, -1),
				  Vec3(-2, 2, 3),
				  Vec3(-2, -2, 3), &mat6);
	Quad backWall(Vec3(-2, 2, -1),
				  Vec3(2, 2, -1),
				  Vec3(2, 2, 3),
				  Vec3(-2, 2, 3), &mat2);
	Quad rightWall(Vec3(2, 2, -1),
				   Vec3(2, -2, -1),
				   Vec3(2, -2, 3),
				   Vec3(2, 2, 3), &mat3);
	Quad emissiveQuad(Vec3(0.5, -0.5, 3),
					  Vec3(-0.5, -0.5, 3),
					  Vec3(-0.5, 0.5, 3),
					  Vec3(0.5, 0.5, 3), &matEmissive);
	Quad emissiveQuad1(Vec3(0.5 - 1, -0.5, 3),
					   Vec3(-0.5 - 1, -0.5, 3),
					   Vec3(-0.5 - 1, 0.5, 3),
					   Vec3(0.5 - 1, 0.5, 3), &matEmissive);
	Quad emissiveQuad2(Vec3(0.5 + 1, -0.5, 3),
					   Vec3(-0.5 + 1, -0.5, 3),
					   Vec3(-0.5 + 1, 0.5, 3),
					   Vec3(0.5 + 1, 0.5, 3), &matEmissive);
	Triangle emissiveTri(Vec3(0.5, -0.5, 3),
						 Vec3(-0.5, -0.5, 3),
						 Vec3(-0.5, 0.5, 3), &matEmissive);


	Sphere sphere0(Vec3(0.5, 0.5, 0.0), 0.5, &mat1);
	//Sphere sphere0(Vec3(0, 0, 0), 0.5, &mat1);
	Sphere sphere1(Vec3(0.5, -1, -0.5), 0.5, &matEmissive);

	TriangleMesh box(std::vector<Vec3>{Vec3(-1.25, -0.75, -1),
					 Vec3(-1, -1, -1),
					 Vec3(-1.25, -1.25, -1),
					 Vec3(-1.5, -1, -1),
					 Vec3(-1.25, -0.75, 0),
					 Vec3(-1, -1, 0),
					 Vec3(-1.25, -1.25, 0),
					 Vec3(-1.5, -1, 0)},
					 std::vector<Vec3i>{Vec3i(0, 1, 2),
					 Vec3i(2, 3, 0),
					 Vec3i(5, 1, 0),
					 Vec3i(0, 4, 5),
					 Vec3i(6, 2, 1),
					 Vec3i(1, 5, 6),
					 Vec3i(4, 0, 3),
					 Vec3i(3, 7, 4),
					 Vec3i(6, 5, 4),
					 Vec3i(4, 7, 6),
					 Vec3i(7, 3, 2),
					 Vec3i(2, 6, 7)}, & mat1);

	TriangleMesh pyramid(std::vector<Vec3>{
		Vec3(-1, 0, 1),
			Vec3(0, -1, 1),
			Vec3(1, 0, 1),
			Vec3(0, 1, 1),
			Vec3(0, 0, 0)},
						 std::vector<Vec3i>{Vec3i(0, 1, 2),
			Vec3i(2, 3, 0),
			Vec3i(4, 1, 0),
			Vec3i(4, 2, 1),
			Vec3i(4, 3, 2),
			Vec3i(4, 0, 3)
		}, & mat1);

	Glossy gloss(Colors::crimson, 0.5, 50);

	Sphere ssphere(Vec3(0, 0, 0), 1, &gloss);

	Scene scene;
	scene.SetCamera(&cam);

	scene.AddObject(&floor);
	scene.AddObject(&ceiling);
	scene.AddObject(&leftWall);
	scene.AddObject(&rightWall);
	scene.AddObject(&backWall);
	scene.AddObject(&emissiveQuad);
	//scene.AddObject(&emissiveTri);
	//scene.AddObject(&emissiveQuad1);
	//scene.AddObject(&emissiveQuad2);
	//scene.AddObject(&sphere1);
	//scene.AddObject(&glassSphere);
	scene.AddObject(&ssphere);
	//scene.AddObject(&pyramid);

	scene.ConstructBvh();

	rayTracer(vp, scene);
	return;
}

void simpleTest()
{
	Camera cam({0,-6,1}, {0,1,0}, {0,0,1});
	//Viewport vp(256, 256);
	Viewport vp(Settings::imgWidth, Settings::imgHeight);
	Image img(vp.Width(), vp.Height());

	Diffuse mat0(Colors::crimson);
	Light mat1(Colors::white, 100.0);
	Diffuse mat2(Colors::blue);
	Diffuse mat3(Colors::blue);

	Sphere sphere(Vec3(0, 0, 0), 1.0, &mat0);
	Sphere light(Vec3(0, -6, 3), 0.5, &mat1);
	/*
	Quad floor(Vec3(-2, -2, -1),
			   Vec3(2, -2, -1),
			   Vec3(2, 2, -1),
			   Vec3(-2, 2, -1), &mat2);
	Quad leftWall(Vec3(-2, -2, -1),
				  Vec3(-2, 2, -1),
				  Vec3(-2, 2, 3),
				  Vec3(-2, -2, 3), &mat3);
	*/
	/*
	Quad backWall(Vec3(-2, 2-1, -1),
				  Vec3(2, 2-1, -1),
				  Vec3(2, 2, 3),
				  Vec3(-2, 2, 3), &mat2);
	*/
	TriangleMesh box(std::vector<Vec3>{Vec3(-1.25, -0.75 + 2, -1),
					 Vec3(-1, -1 + 2, -1),
					 Vec3(-1.25, -1.25 + 2, -1),
					 Vec3(-1.5, -1 + 2, -1),
					 Vec3(-1.25, -0.75 + 2, 0),
					 Vec3(-1, -1 + 2, 0),
					 Vec3(-1.25, -1.25 + 2, 0),
					 Vec3(-1.5, -1 + 2, 0)
	}, std::vector<Vec3i>{Vec3i(0, 1, 2),
					 Vec3i(2, 3, 0),
					 Vec3i(5, 1, 0),
					 Vec3i(0, 4, 5),
					 Vec3i(6, 2, 1),
					 Vec3i(1, 5, 6),
					 Vec3i(3, 0, 4),
					 Vec3i(4, 7, 3),
					 Vec3i(6, 5, 4),
					 Vec3i(4, 7, 6),
					 Vec3i(7, 3, 2),
					 Vec3i(2, 6, 7)}, & mat2);

	Scene scene;
	scene.SetBackground(Colors::black);
	scene.SetCamera(&cam);

	//scene.AddObject(&sphere);
	//scene.AddObject(&floor);
	scene.AddObject(&light);
	scene.AddObject(&box);
	//scene.AddObject(&box);

	scene.ConstructBvh();
	//MapPhotons(scene);

	rayTracer(vp, scene);
	//ClearMaps();
}

int main(int argc, char* argv[])
{
	InitDemos();

	if(Settings::ArgParser(argc, argv))
	{
		return 1;
	}
	else
	{
		Settings::PrintSettings();
	}

	lameutil::g_TimerPrecision = lameutil::TimerType::SEC;
	std::cout << "\nRendering..." << std::endl;
	{
		lameutil::BenchTimer timer;
		if(Settings::demoIndex != -1)
		{
			g_Demos[Settings::demoIndex]();
		}
		else
		{
			cornellBoxDiffuse();
			return 0;
			cornellBox();

			//simpleTest();
		}
	}
	return 0;
}