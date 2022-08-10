#pragma once
#include "object.h"

class Sphere : public Object
{
public:
	Sphere(const BRDF* brdf = BRDF::Default());
	Sphere(const Vec3& pos, double radius, const BRDF* brdf = BRDF::Default());

	bool Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo) override;
    bool BoundingBox(AABB& output_box) const override;

	const Vec3 Position() const;
	const double Radius() const;
	const double Radius2() const;
private:
	Vec3 m_Position = Vec3(0.0);
	double m_Radius = 1.0;
	double m_Radius2 = 1.0;
};