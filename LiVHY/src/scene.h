#pragma once
#include <vector>
#include "util/types.h"
#include "util/colors.h"
#include "objects/light.h"
#include "objects/object.h"
#include "util/ray.h"

class Scene{
public:
	Scene();

	bool Intersects(const Ray& ray, Object*& hitObject, double& dist, Vec3& normal);

	std::vector<Object*> Objects();
	std::vector<Light*> Lights();

	void AddObject(Object* obj);
	void AddLight(Light* light);

	const RGB& Background();
	void SetBackground(const RGB& rgb);
private:
	RGB m_BackgroundColor = Colors::black;

	std::vector<Object*> m_Objects;
	std::vector<Light*> m_Lights;
};