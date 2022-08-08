#pragma once
#include <vector>
#include "aabb.h"
#include "hittable.h"

class HittableList : public Hittable{
public:
	HittableList();

	void Add(Hittable* obj);
	std::vector<Hittable*>& List();
	void Clear();

	bool Hit(const Ray& ray, const double& near, const double& far, HitInfo& hitInfo) override;
    bool BoundingBox(AABB& outputBox) const override;

private:
	std::vector<Hittable*> m_List;
};