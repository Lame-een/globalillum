#pragma once
#include "ray.h"
#include "types.h"

class Object;

/// @struct HitInfo
/// @brief Struct describing the Ray intersect.
//NOTE: optimisation check maybe don't include point in hit calculation but instead calculate it from ray and t when necessary
struct HitInfo
{
public:
	Ray ray;
	Vec3 point;
	Vec3 normal;
	const Object* object = nullptr;
	double t;
	Vec2 uv;
};