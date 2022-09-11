/// @file objects/aabb.h
#pragma once
//axis aligned bounding box
//Andrew Kensler at Pixar

//todo potentionally use the Roman Winche implementation for extra speed

#include "util/types.h"
#include "util/ray.h"

/// @class AABB
/// @brief Axis-Aligned Boundary Box class
class AABB
{
public:
	AABB();
	/// @param[in] min Minimum value corner of the axis aligned box.
	/// @param[in] max Maximum value corner of the axis aligned box.
	AABB(const Vec3& min, const Vec3& max);

	const Vec3& Min() const;
	const Vec3& Max() const;

	/// @brief Set the minimum and maximum corners of the axis aligned box.
	/// @param[in] min Minimum value corner of the axis aligned box.
	/// @param[in] max Maximum value corner of the axis aligned box.
	/// @return void
	const void Set(const Vec3& min, const Vec3& max);

	/// @brief Ray intersection checker function.
	/// @param[in] r The cast ray.
	/// @param[in] tMin Minimum ray length.
	/// @param[in] tMax Maximum ray length.
	/// @return Returns true if the ray hits the boundary box.
	bool Hit(const Ray& r, float tMin, float tMax) const;
	/// @brief The calling AABB surrounds the passed box.
	/// @param[in] box Box which should be surrounded.
	void Surround(const AABB& box);

private:
	Vec3 m_Min = Vec3(0.0f);
	Vec3 m_Max = Vec3(0.0f);
};