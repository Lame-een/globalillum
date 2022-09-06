#pragma once
#include "demoIncludes.h"

inline void threeMetals()
{
	Viewport vp;
	Camera cam({1.3,-4,1.7}, {-0.1983, 0.7399, -0.6428}, {-0.1664, 0.6209, 0.7660});
	Image img(vp.Width(), vp.Height());

	Light matEmissive(Colors::white, 10);
	Specular matBlue(stringToRGB("#4a7cd7"), 0.1);
	Specular silver(RGB(0.508273, 0.508273, 0.508273), 0.05);
	Specular copper(RGB(0.580594, 0.223257, 0.0695701), 0.15);
	Specular gold(RGB(0.797357, 0.723991, 0.208006), 0.0);

	Quad floor(Vec3(-1, -2, -1),
			   Vec3(2, -2, -1),
			   Vec3(2, 1.5, -1),
			   Vec3(-1, 1.5, -1), &matBlue);
	Quad emissiveQuad(Vec3(-0.5, -0.5, 2.99),
					   Vec3(-1.5, -0.5, 2.99),
					   Vec3(-1.5, 0.5, 2.99),
					   Vec3(-0.5, 0.5, 2.99), &matEmissive);

	Sphere sphere0(Vec3(1.5, -1.5, -0.5), 0.5, &silver);
	Sphere sphere1(Vec3(0.5, -0.5,  -0.5), 0.5, &copper);
	Sphere sphere2(Vec3(-0.5, 0.5,  -0.5), 0.5, &gold);

	Scene scene;
	scene.SetCamera(&cam);

	scene.AddObject(&floor);
	scene.AddObject(&emissiveQuad);
	scene.AddObject(&sphere0);
	scene.AddObject(&sphere1);
	scene.AddObject(&sphere2);

	scene.ConstructBvh();

	rayTracer(vp, scene);
	return;
}