#include "pch.h"
#include "aabb.h"
//#include <utility>
//#include "glm/common.hpp"

AABB::AABB()
{
}

AABB::AABB(const Vec3& min, const Vec3& max)
	: m_Min(min), m_Max(max)
{}

const Vec3& AABB::Min() const
{
	return m_Min;
}

const Vec3& AABB::Max() const
{
	return m_Max;
}

const void AABB::Set(const Vec3& min, const Vec3& max)
{
    m_Min = min;
    m_Max = max;
}

//Andrew Kensler implementation of the ray intercept function
//TODO: check the Roman Winche (medium article) implementation
//      for a possible speed boost.
bool AABB::Hit(const Ray& ray, float tMin, float tMax) const
{
	for (int axis = 0; axis < 3; axis++) {
        float invD = 1.0f / ray.Dir()[axis];
        float t0 = (m_Min[axis] - ray.Origin()[axis]) * invD;
        float t1 = (m_Max[axis] - ray.Origin()[axis]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;
        if (tMax <= tMin)
            return false;
    }
    return true;
}

/// The function takes the input box and compares it to the current corners. 
/// If the calling box is smaller than the passed box set the minimum and
/// maximum corners to surround the passed box.
void AABB::Surround(const AABB& box){
    m_Min = glm::min(m_Min, box.Min());
    m_Max = glm::max(m_Max, box.Max());
}
