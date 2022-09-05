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

	Diffuse matDiffGray(stringToRGB("#f0f0f0"));
	Transmissive glass(1.4);
	Diffuse matDiffGreen(Colors::limegreen);
	Diffuse matDiffBlue(Colors::blue);
	Diffuse matDiffWhite(Colors::white);
	Specular matSpecular(Colors::lightgray, 0.2);
	Diffuse matDiffCrimson(Colors::crimson);
	Light matEmissive(Colors::white, 50);
	Quad floor(Vec3(-2, -2, -1),
			   Vec3(2, -2, -1),
			   Vec3(2, 2, -1),
			   Vec3(-2, 2, -1), &matDiffGray);
	Quad ceiling(Vec3(-2, -2, 3),
				 Vec3(-2, 2, 3), Vec3(2, 2, 3),
				 Vec3(2, -2, 3), &matDiffGray);
	Quad leftWall(Vec3(-2, -2, -1),
				  Vec3(-2, 2, -1),
				  Vec3(-2, 2, 3),
				  Vec3(-2, -2, 3), &matDiffCrimson);
	Quad backWall(Vec3(-2, 2, -1),
				  Vec3(2, 2, -1),
				  Vec3(2, 2, 3),
				  Vec3(-2, 2, 3), &matDiffGreen);
	Quad rightWall(Vec3(2, 2, -1),
				   Vec3(2, -2, -1),
				   Vec3(2, -2, 3),
				   Vec3(2, 2, 3), &matDiffBlue);
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


	Sphere sphere0(Vec3(0.5, 0.5, 0.0), 0.5, &matDiffCrimson);
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
					 Vec3i(2, 6, 7)}, &matSpecular);

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
		}, &glass);

	Quad frontWall0(Vec3(-4, -2.1, 0),
				  Vec3(4, -2.1, 0),
				  Vec3(4, -2.1, 2),
				  Vec3(-4, -2.1, 2), &glass);
	Quad frontWall1(Vec3(4, -2, 2),
					Vec3(4, -2, 0),
					Vec3(-4, -2, 0),
					Vec3(-4, -2, 2), &glass);

	Glossy gloss(Colors::crimson, 0.5, 50);

	//Sphere ssphere(Vec3(0, 0, 0), 1, &gloss);
	Sphere ssphere(Vec3(1, -1, 0), 0.5, &glass);

	Scene scene;
	scene.SetCamera(&cam);

	scene.AddObject(&floor);
	scene.AddObject(&ceiling);
	scene.AddObject(&leftWall);
	scene.AddObject(&rightWall);
	scene.AddObject(&backWall);
	//scene.AddObject(&frontWall0);
	//scene.AddObject(&frontWall1);
	//scene.AddObject(&emissiveQuad);
	//scene.AddObject(&emissiveTri);
	scene.AddObject(&emissiveQuad1);
	scene.AddObject(&emissiveQuad2);
	//scene.AddObject(&sphere1);
	//scene.AddObject(&glassSphere);
	//scene.AddObject(&ssphere);
	scene.AddObject(&pyramid);

	scene.ConstructBvh();

	rayTracer(vp, scene);
	return;
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
			//cornellBoxTransmissive();
			cornellBox();

			//simpleTest();
		}
	}
	return 0;
}