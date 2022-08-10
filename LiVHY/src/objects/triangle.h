#pragma once
#include "object.h"

class Triangle : public Object{
public:
	Triangle(const Vec3& a, const Vec3& b, const Vec3& c, const BRDF* brdf = BRDF::Default());
	Triangle(const Vec3* arr, const BRDF* brdf = BRDF::Default());

	bool Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo) override;
    bool BoundingBox(AABB& outputBox) const override;

	void SetVertex(const Vec3& point, size_t index);
	const Vec3* Vertices() const;
	const Vec3& Vertex(size_t index) const;

	const Vec3& Normal() const;

private:
	Vec3 m_Vertices[3];
	Vec3 m_Normal;
};