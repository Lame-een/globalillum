#pragma once
#include "util/types.h"
#include "util/ray.h"
#include "BRDF.h"
#include "aabb.h"

class Object;

//NOTE: optimisation check maybe don't include point in hit calculation but instead calculate it from ray and t when necessary
struct HitInfo{
public:
	Vec3 point;
	Vec3 normal;
	Object* object = nullptr;
	double t;
	Vec2 uv;
};

class Object
{
public:
	Object();
	Object(const BRDF* brdf);

	virtual bool Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo) = 0;
    virtual bool BoundingBox(AABB& outputBox) const = 0;

	const BRDF* Brdf() const;
protected:
	const BRDF* m_Brdf = nullptr;
};