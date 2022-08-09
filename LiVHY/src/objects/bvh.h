#pragma once
#include <vector>
#include "objectList.h"
#include "lame/easyRandom.h"

bool BoxCompare(int axis, Object* a, Object* b);

class BVHNode : public Object{
public:
	BVHNode(const ObjectList& list);
	BVHNode(const std::vector<Object*>& Objects, size_t start, size_t end);
	~BVHNode();

	bool Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo);
    bool BoundingBox(AABB& output_box) const;

	Object* Left();
	Object* Right();

private:
	Object* m_Left;
	Object* m_Right;
	AABB m_BoundingBox;

	lameutil::EasyRandom m_RandGenerator;
};