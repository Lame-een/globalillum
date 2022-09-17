/// @file util/ray.h
#pragma once
#include "types.h"

/// @class Ray
/// @brief Class defining a ray.
class Ray{
public:
	Ray();
	Ray(const Vec3& orig, const Vec3& dir);
	
	void Normalize();

	const Vec3& Origin() const;
	void SetOrigin(const Vec3& point);

	const Vec3& Dir() const;
	void SetDir(const Vec3& dir);

private:
	Vec3 m_Origin = Vec3(0.0);
	Vec3 m_Dir = Vec3(0.0);
};