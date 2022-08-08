#pragma once
#include <vector>
#include "util/types.h"
#include "util/colors.h"
#include "objects/light.h"
#include "objects/object.h"
#include "util/ray.h"

class Scene : public Hittable{
public:
	Scene();

	bool Hit(const Ray& ray, const double& near, const double& far, HitInfo& hitInfo) override;
    bool BoundingBox(AABB& output_box) const override;

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