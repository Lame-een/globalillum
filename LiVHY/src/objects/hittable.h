#pragma once
#include "util/types.h"
#include "aabb.h"

class Object;	//forward declaration to avoid circular dependency


//NOTE: optimisation check maybe don't include point in hit calculation but instead calculate it from ray and t when necessary
struct HitInfo{
public:
	Vec3 point;
	Vec3 normal;
	Object* object = nullptr;
	double t;
	Vec2 uv;
};

class Hittable{
public:
	virtual bool Hit(const Ray& ray, const double& near, const double& far, HitInfo& hitInfo) = 0;
    virtual bool BoundingBox(AABB& output_box) const = 0;
};