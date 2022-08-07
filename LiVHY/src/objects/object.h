#pragma once
#include "util/types.h"
#include "util/ray.h"
#include "BRDF.h"

class Object
{
public:
	Object(BRDF* brdf);
	virtual bool RayIntersect(const Ray& ray,
					  double& t, Vec3& normal) = 0;

	BRDF* Brdf() const;
protected:
	BRDF* m_Brdf;
};