#pragma once
#include "types.h"
class Ray{
public:
	Ray(const Vec3& orig, const Vec3& dir);
	
	void Normalize();

	const Vec3& Origin() const;
	const Vec3& Dir() const;

private:
	Vec3 m_Origin;
	Vec3 m_Dir;
};