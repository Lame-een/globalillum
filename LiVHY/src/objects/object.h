#pragma once
#include "util/types.h"
#include "util/ray.h"
#include "BRDF.h"

class Object
{
public:
	Object(const BRDF& brdf);
	virtual bool RayIntersect(const Ray& ray,
					  double& t, Vec3& normal) = 0;

	const BRDF& Brdf() const;
protected:
	BRDF m_Brdf;
};