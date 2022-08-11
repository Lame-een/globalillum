/// @file objects/sphere.h
#pragma once
#include "object.h"

/// @class Sphere
/// @brief Class describing a sphere.
class Sphere : public Object
{
public:
	Sphere(const BRDF* brdf = BRDF::Default());
	Sphere(const Vec3& pos, double radius, const BRDF* brdf = BRDF::Default());

	/// @brief Ray intersection checker function.
	/// @param[in] ray Ray to check against.
	/// @param[in] tMin Minimum ray length.
	/// @param[in] tMax Maximum ray length.
	/// @param[out] hitInfo Reference to the information about the hit.
	/// @return Returns true if the ray hit the sphere.
	bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) override;
	/// @brief Constructs a bounding box around the sphere.
    /// @param[out] outputBox The AABB of the sphere.
    /// @return Returns true if able to construct an AABB.
    bool BoundingBox(AABB& outputBox) const override;

	const Vec3 Position() const;
	const double Radius() const;
	/// @brief Getter for the squared radius of the sphere.
	/// @return Returns the squared radius.
	const double Radius2() const;
private:
	Vec3 m_Position = Vec3(0.0);
	double m_Radius = 1.0;
	double m_Radius2 = 1.0;
};