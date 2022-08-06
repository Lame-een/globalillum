#pragma once
#include "util/types.h"
#include "BRDF.h"

class Object
{
public:
	Object(const BRDF& brdf);
	virtual bool RayIntersect(const Vec3& p, const Vec3& dir,
					  double& t, Vec3& normal) = 0;

	const BRDF& Brdf() const;
protected:
	BRDF m_Brdf;
};