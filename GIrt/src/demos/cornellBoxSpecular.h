#pragma once
#include "demoIncludes.h"

inline void cornellBoxSpecular()
{
	Viewport vp;
	Camera cam({0,-6,1}, {0,1,0}, {0,0,1});
	Image img(vp.Width(), vp.Height());

	Diffuse matUpDown(StringToRGB("#808080"));
	Diffuse matLeft(Colors::crimson);
	Diffuse matRight(Colors::blueviolet);
	Specular matSpecular0(Colors::lightgray, 0.01);
	Specular matSpecular1(Colors::lightgray, 0.5);
	Light matEmissive(Colors::white, 10);

	Quad floor(Vec3(-2, -2, -1),
			   Vec3(2, -2, -1),
			   Vec3(2, 2, -1),
			   Vec3(-2, 2, -1), &matUpDown);
	Quad ceiling(Vec3(-2, -2, 3),
				 Vec3(-2, 2, 3),
				 Vec3(2, 2, 3),
				 Vec3(2, -2, 3), &matUpDown);
	Quad leftWall(Vec3(-2, -2, -1),
				  Vec3(-2, 2, -1),
				  Vec3(-2, 2, 3),
				  Vec3(-2, -2, 3), &matLeft);
	Quad backWall(Vec3(-2, 2, -1),
				  Vec3(2, 2, -1),
				  Vec3(2, 2, 3),
				  Vec3(-2, 2, 3), &matSpecular0);
	Quad rightWall(Vec3(2, 2, -1),
				   Vec3(2, -2, -1),
				   Vec3(2, -2, 3),
				   Vec3(2, 2, 3), &matRight);
	Quad emissiveQuad0(Vec3(-0.5, -0.5, 2.99),
					   Vec3(-1.5, -0.5, 2.99),
					   Vec3(-1.5, 0.5, 2.99),
					   Vec3(-0.5, 0.5, 2.99), &matEmissive);
	Quad emissiveQuad1(Vec3(1.5, -0.5, 2.99),
					   Vec3(0.5, -0.5, 2.99),
					   Vec3(0.5, 0.5, 2.99),
					   Vec3(1.5, 0.5, 2.99), &matEmissive);

	Sphere sphere0(Vec3(1.0, -1.0, -0.5), 0.5, &matSpecular1);

	TriangleMesh box(std::vector<Vec3>{
		Vec3(-1.70711, 0.0, -1),
			Vec3(-1.0, -0.707107, -1),
			Vec3(-0.292893, 0.0, -1),
			Vec3(-1.0, 0.707107, -1),
			Vec3(-1.70711, 0.0, 1),
			Vec3(-1.0, -0.707107, 1),
			Vec3(-0.292893, 0.0, 1),
			Vec3(-1.0, 0.707107, 1),
	}, std::vector<Vec3i>{
		Vec3i(2, 1, 0),
			Vec3i(0, 3, 2),
			Vec3i(0, 1, 5),
			Vec3i(5, 4, 0),
			Vec3i(1, 2, 6),
			Vec3i(6, 5, 1),
			Vec3i(3, 0, 4),
			Vec3i(4, 7, 3),
			Vec3i(4, 5, 6),
			Vec3i(6, 7, 4),
			Vec3i(2, 3, 7),
			Vec3i(7, 6, 2)
	}, &matSpecular0);

	Scene scene;
	scene.SetCamera(&cam);

	scene.AddObject(&floor);
	scene.AddObject(&ceiling);
	scene.AddObject(&leftWall);
	scene.AddObject(&rightWall);
	scene.AddObject(&backWall);
	scene.AddObject(&emissiveQuad0);
	scene.AddObject(&emissiveQuad1);
	scene.AddObject(&sphere0);
	scene.AddObject(&box);

	scene.ConstructBvh();

	RayTracer(vp, scene);
	return;
}