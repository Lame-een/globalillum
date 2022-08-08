#include "aabb.h"
#include <utility>
#include "glm/common.hpp"

AABB::AABB()
{
}

AABB::AABB(const Vec3& a, const Vec3& b)
	: m_Min(a), m_Max(b)
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

bool AABB::Hit(const Ray& ray, double tMin, double tMax) const
{
	for (int axis = 0; axis < 3; axis++) {
        double invD = 1.0f / ray.Dir()[axis];
        double t0 = (m_Min[axis] - ray.Origin()[axis]) * invD;
        double t1 = (m_Max[axis] - ray.Origin()[axis]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;
        if (tMax <= tMin)
            return false;
    }
    return true;
}

void AABB::Surround(const AABB& box){
    m_Min = glm::min(m_Min, box.Min());
    m_Max = glm::max(m_Max, box.Max());
}
