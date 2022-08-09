#pragma once
#include <vector>
#include "object.h"

class ObjectList : public Object{
public:
	ObjectList();

	void Add(Object* obj);
	std::vector<Object*>& List();
	const std::vector<Object*>& List() const;
	void Clear();

	bool Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo) override;
    bool BoundingBox(AABB& outputBox) const override;

private:
	std::vector<Object*> m_List;
};