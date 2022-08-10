#include "sphere.h"
#include "util/math.h"
#include "glm/geometric.hpp"

Sphere::Sphere(const BRDF* brdf)
	: Object(brdf)
{
}

Sphere::Sphere(const Vec3& pos, double radius, const BRDF* brdf)
	: Object(brdf), m_Position(pos), m_Radius(radius), m_Radius2(radius* radius)
{
}

bool Sphere::Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo)
{
	Vec3 L = ray.Origin() - m_Position;
	double a = glm::dot(ray.Dir(), ray.Dir());
	double b = 2 * glm::dot(ray.Dir(), L);
	double c = glm::dot(L, L) - m_Radius2;

	double t0, t1;
	if(!solveQuadratic(a, b, c, t0, t1))
	{
		return false;
	}

	if(t0 < tMin || t0 > tMax)
	{
		if(t1 < tMin || t0 > tMax)
		{
			return false;  //both t0 and t1 aren't visible
		}
		else
		{
			hitInfo.t = t1;
		}
	}
	else
	{
		hitInfo.t = t0;
	}

	hitInfo.normal = glm::normalize(L + hitInfo.t*ray.Dir());
	hitInfo.object = this;
	hitInfo.point = ray.Origin() + ray.Dir() * hitInfo.t;

	return true;
}
bool Sphere::BoundingBox(AABB& outputBox) const
{
	outputBox.Set(m_Position - Vec3(m_Radius), m_Position + Vec3(m_Radius));
	return true;
}

const Vec3 Sphere::Position() const
{
	return m_Position;
}

const double Sphere::Radius() const
{
	return m_Radius;
}

const double Sphere::Radius2() const
{
	return m_Radius2;
}
