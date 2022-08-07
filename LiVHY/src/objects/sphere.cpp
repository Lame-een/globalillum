#include "sphere.h"
#include "util/math.h"
#include "glm/geometric.hpp"

Sphere::Sphere(BRDF* brdf)
	: Object(brdf)
{
}

Sphere::Sphere(const Vec3& pos, double radius, BRDF* brdf)
	: Object(brdf), m_Position(pos), m_Radius(radius), m_Radius2(radius* radius)
{
}

bool Sphere::RayIntersect(const Ray& ray,
						  double& t, Vec3& normal)
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

	if(t0 < 0)
	{
		if(t1 < 0)
		{
			return false;  //both t0 and t1 are negative
		}
		else
		{
			t = t1;
		}
	}
	else
	{
		t = t0;
	}

	normal = glm::normalize(L + t*ray.Dir());

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
