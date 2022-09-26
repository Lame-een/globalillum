#pragma once
#include "demoIncludes.h"
#include <vector>
#include <sstream>
#include <string>

/*
void sandbox()
{
	Viewport vp(Settings::imgWidth, Settings::imgHeight, Settings::fov);
	Camera cam({0,-5,1}, {0,1,0}, {0,0,1});

	Diffuse matGround(Colors::navy);
	Diffuse matSphere(Colors::crimson);
	Light matEmissive(Colors::white, 5);
	Transmissive matGlass(1.4);
	Sphere sphereOrigin(Vec3(0.0, 0.0, 1.0), 1.0, &matGlass);
	Sphere sphereLight(Vec3(0.0, 0.0, 3.0), 0.5, &matEmissive);

	TriangleMesh bunny("bunny", &matSphere);

	Quad floor(Vec3(-20, -20, 0),
			   Vec3(20, -20, 0),
			   Vec3(20, 20, 0),
			   Vec3(-20, 20, -0), &matGround);



	Scene scene;
	scene.SetCamera(&cam);
	scene.AddObject(&floor);
	scene.AddObject(&sphereOrigin);
	scene.AddObject(&sphereLight);
	scene.AddObject(&bunny);

	scene.ConstructBvh();	//MUST be called before the raytracer is called

	RayTracer(vp, scene);
	return;
}
*/

void sandbox()
{
	Viewport vp(Settings::imgWidth, Settings::imgHeight, Settings::fov);
	Camera cam({0,-5,2}, {0,1,-0.3}, {0,0,1});

	Diffuse matUp(StringToRGB("#808080"));
	Diffuse matDown(StringToRGB("#808080"));
	Diffuse matBack(StringToRGB("#808080"));
	Diffuse matCrimson(Colors::crimson);
	Diffuse matMathos(StringToRGB("#0047bb"));
	Specular matSpecular(Colors::lightgray, 0.01);
	Light matEmissive(Colors::white, 40);

	Quad floor(Vec3(-2, -2, 0),
			   Vec3(2, -2, 0),
			   Vec3(2, 2, 0),
			   Vec3(-2, 2, 0), &matDown);
	//Quad ceiling(Vec3(-2, -2, 3),
	//			 Vec3(-2, 2, 3),
	//			 Vec3(2, 2, 3),
	//			 Vec3(2, -2, 3), &matUp);
	Quad backWall(Vec3(-2, 2, 0),
				  Vec3(2, 2, 0),
				  Vec3(2, 2, 3),
				  Vec3(-2, 2, 3), &matBack);
	Quad emissiveQuad0(Vec3(-0.5, -0.5, 4.99),
					   Vec3(-1.5, -0.5, 4.99),
					   Vec3(-1.5, 0.5, 4.99),
					   Vec3(-0.5, 0.5, 4.99), &matEmissive);
	Quad emissiveQuad1(Vec3(1.5, -0.5, 4.99),
					   Vec3(0.5, -0.5, 4.99),
					   Vec3(0.5, 0.5, 4.99),
					   Vec3(1.5, 0.5, 4.99), &matEmissive);

	TriangleMesh bunnies("bunnies", &matCrimson);
	TriangleMesh mathos("mathosLogo", &matMathos);

	Scene scene;
	scene.SetCamera(&cam);

	scene.AddObject(&floor);
	scene.AddObject(&backWall);
	scene.AddObject(&emissiveQuad0);
	scene.AddObject(&emissiveQuad1);
	scene.AddObject(&mathos);
	scene.AddObject(&bunnies);

	scene.ConstructBvh();	//MUST be called before the raytracer is called

	RayTracer(vp, scene);
	return;
}