/// @file objects/object.h
#pragma once
#include "util/types.h"
#include "util/ray.h"
#include "BRDF.h"
#include "aabb.h"

class Object;


/// @struct HitInfo
/// @brief Struct describing the Ray intersect.
//NOTE: optimisation check maybe don't include point in hit calculation but instead calculate it from ray and t when necessary
struct HitInfo{
public:
	Ray ray;
	Vec3 point;
	Vec3 normal;
	Object* object = nullptr;
	double t;
	Vec2 uv;
};

/// @class Object
/// @brief Base class for all objects.
class Object
{
public:
	Object();
	Object(const BRDF* brdf);

	/// @brief Ray intersection checker function.
	/// @param[in] ray Ray to check against.
	/// @param[in] tMin Minimum ray length.
	/// @param[in] tMax Maximum ray length.
	/// @param[out] hitInfo Reference to the information about the hit.
	/// @return Returns true if the ray hit the object.
	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo){return true;}
	/// @brief Constructs a bounding box around the object.
    /// @param[out] outputBox The AABB of the object.
    /// @return Returns true if able to construct an AABB.
	virtual bool BoundingBox(AABB& outputBox) const{return true;}

	const BRDF* Brdf() const;
protected:
	const BRDF* m_Brdf = nullptr;
};