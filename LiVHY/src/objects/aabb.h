#pragma once
//axis aligned bounding box
//Andrew Kensler at Pixar

#include "util/types.h"
#include "util/ray.h"

class AABB
{
public:
	AABB();
	AABB(const Vec3& a, const Vec3& b);

	const Vec3& Min() const;
	const Vec3& Max() const;

	const void Set(const Vec3& min, const Vec3& max);

	bool Hit(const Ray& r, double tMin, double tMax) const;
	void Surround(const AABB& box);

private:
	Vec3 m_Min = Vec3(0);
	Vec3 m_Max = Vec3(0);
};