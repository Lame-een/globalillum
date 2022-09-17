#pragma once
#pragma once
#include "demoIncludes.h"

inline void cornellBoxWindow()
{
	Viewport vp;
	Camera cam({0,-6,1}, {0,1,0}, {0,0,1});
	Image img(vp.Width(), vp.Height());

	Diffuse matUpDown(StringToRGB("#808080"));
	Diffuse matLeft(Colors::crimson);
	Diffuse matRight(Colors::lightblue);
	Diffuse matBack(Colors::forestgreen);
	Diffuse matSphere0(Colors::navy);
	Diffuse matBox0(Colors::darkred);

	Quad floor(Vec3(-2, -8, -1),
			   Vec3(2, -8, -1),
			   Vec3(2, 2, -1),
			   Vec3(-2, 2, -1), &matUpDown);
	Quad ceiling(Vec3(-2, -8, 3),
				 Vec3(-2, 2, 3),
				 Vec3(2, 2, 3),
				 Vec3(2, -8, 3), &matUpDown);
	Quad leftWall(Vec3(-2, -8, -1),
				  Vec3(-2, 2, -1),
				  Vec3(-2, 2, 3),
				  Vec3(-2, -8, 3), &matLeft);
	Quad backWall(Vec3(-2, 2, -1),
				  Vec3(2, 2, -1),
				  Vec3(2, 2, 3),
				  Vec3(-2, 2, 3), &matBack);
	Quad frontWall(Vec3(2, 2, 3),
				   Vec3(-2, 2, -1),
				  Vec3(2, 2, -1),
				  Vec3(-2, 2, 3), &matBack);

	Sphere sphere0(Vec3(1.0, -1.5, -0.5), 0.5, &matSphere0);
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
	}, &matBox0);

	TriangleMesh rightWindowWall(std::vector<Vec3>{
		Vec3(2,2,-1),		//0
		Vec3(2,-1.4,-1),	//1
		Vec3(2,-1.4,0.333),	//2
		Vec3(2,0.4,0.333),	//3
		Vec3(2,2,0.333),	//4
		Vec3(2,0.4,1.666),	//5
		Vec3(2,2,1.666),	//6
		Vec3(2,-1.4,1.666),	//7
		Vec3(2,-1.4,3),		//8
		Vec3(2,2,3),		//9
		Vec3(2,-8,-1),		//10
		Vec3(2,-8,3)		//11
	}, std::vector<Vec3i>{
		Vec3i(0,1,2),
		Vec3i(0,2,4),
		Vec3i(4,3,5),
		Vec3i(4,5,6),
		Vec3i(6,7,8),
		Vec3i(6,8,9),
		Vec3i(1,10,11),
		Vec3i(1,11,8)
	}, &matRight);


	Scene scene;
	scene.SetCamera(&cam);

	scene.AddObject(&floor);
	scene.AddObject(&ceiling);
	scene.AddObject(&leftWall);
	scene.AddObject(&rightWindowWall);
	scene.AddObject(&backWall);
	scene.AddObject(&sphere0);
	scene.AddObject(&box);

	scene.ConstructBvh();

	RayTracer(vp, scene);
	return;
}