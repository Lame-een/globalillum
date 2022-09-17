#pragma once
#include "demoIncludes.h"

void sandbox()
{
	Viewport vp(Settings::imgWidth, Settings::imgHeight, Settings::fov);
	Camera cam({0,-5,1}, {0,1,0}, {0,0,1});

	Diffuse matGround(Colors::navy);
	Diffuse matSphere(Colors::crimson);
	Light matEmissive(Colors::white, 5);
	Transmissive matGlass(1.4);
	Quad floor(Vec3(-20, -20, 0),
			   Vec3(20, -20, 0),
			   Vec3(20, 20, 0),
			   Vec3(-20, 20, -0), &matGround);

	Sphere sphereOrigin(Vec3(0.0, 0.0, 1.0), 1.0, &matGlass);
	Sphere sphereLight(Vec3(0.0, 0.0, 3.0), 0.5, &matEmissive);

	Scene scene;
	scene.SetCamera(&cam);
	scene.AddObject(&floor);
	scene.AddObject(&sphereOrigin);
	scene.AddObject(&sphereLight);

	scene.ConstructBvh();	//MUST be called before the raytracer is called

	RayTracer(vp, scene);
	return;
}