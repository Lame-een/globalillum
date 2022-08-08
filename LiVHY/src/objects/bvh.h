#pragma once
#include <vector>
#include "hittableList.h"
#include "lame/easyRandom.h"

bool BoxCompare(int axis, Hittable* a, Hittable* b);

class BVHNode : public Hittable{
public:
	BVHNode(const HittableList& list);
	BVHNode(const std::vector<Hittable*>& hittables, size_t start, size_t end);

	bool Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo);
    bool BoundingBox(AABB& output_box) const;

	Hittable* Left();
	Hittable* Right();

private:
	Hittable* m_Left;
	Hittable* m_Right;
	AABB m_BoundingBox;

	lameutil::EasyRandom m_RandGenerator;
};