#pragma once
#include "demoIncludes.h"

inline void threeMetals()
{
	Viewport vp;
	Camera cam({1.3f,-4.0f,1.7f}, {-0.1983f, 0.7399f, -0.6428f}, {-0.1664f, 0.6209f, 0.7660f});
	Image img(vp.Width(), vp.Height());

	Light matEmissive(Colors::white, 10.0f);
	Specular matBlue(stringToRGB("#4a7cd7"), 0.1f);
	Specular silver(RGB(0.508273f, 0.508273f, 0.508273f), 0.05f);
	Specular copper(RGB(0.580594f, 0.223257f, 0.0695701f), 0.15f);
	Specular gold(RGB(0.797357f, 0.723991f, 0.208006f), 0.0f);

	Quad floor(Vec3(-1.0f, -2.0f, -1.0f),
			   Vec3(2.0f, -2.0f, -1.0f),
			   Vec3(2.0f, 1.5f, -1.0f),
			   Vec3(-1.0f, 1.5f, -1.0f), &matBlue);
	Quad emissiveQuad(Vec3(-0.5f, -0.5f, 2.99f),
					   Vec3(-1.5f, -0.5f, 2.99f),
					   Vec3(-1.5f, 0.5f, 2.99f),
					   Vec3(-0.5f, 0.5f, 2.99f), &matEmissive);

	Sphere sphere0(Vec3(1.5f, -1.5f, -0.5f), 0.5f, &silver);
	Sphere sphere1(Vec3(0.5f, -0.5f,  -0.5f), 0.5f, &copper);
	Sphere sphere2(Vec3(-0.5f, 0.5f,  -0.5f), 0.5f, &gold);

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