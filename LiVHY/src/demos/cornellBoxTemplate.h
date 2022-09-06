#pragma once
#include "demoIncludes.h"

inline void cornellBoxDiffuse()
{
	Viewport vp;
	Camera cam({0,-6,1}, {0,1,0}, {0,0,1});
	Image img(vp.Width(), vp.Height());

	Diffuse matUpDown(stringToRGB("#808080"));
	Diffuse matLeft(Colors::crimson);
	Diffuse matRight(Colors::blueviolet);
	Diffuse matBack(Colors::forestgreen);
	Diffuse matSphere0(Colors::lightblue);
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
				  Vec3(-2, 2, 3), &matBack);
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

	Sphere sphere0(Vec3(0.0, 0.0, 0.0), 1.0, &matSphere0);

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

	scene.ConstructBvh();

	rayTracer(vp, scene);
	return;
}