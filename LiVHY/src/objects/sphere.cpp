#include "pch.h"
#include "sphere.h"
#include "camera.h"
//#include "util/math.h"
//#include "glm/geometric.hpp"

Sphere::Sphere(const Material* material, bool cull, bool samplingTarget)
	: Object(material, cull, samplingTarget)
{
}

Sphere::Sphere(const Vec3& pos, float radius, const Material* material, bool cull, bool samplingTarget)
	: Object(material, cull, samplingTarget), m_Position(pos), m_Radius(radius), m_Radius2(radius* radius)
{
}

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitInfo& hitInfo) const
{
	Vec3 L = ray.Origin() - m_Position;
	float a = glm::dot(ray.Dir(), ray.Dir());
	float b = 2.0f * glm::dot(ray.Dir(), L);
	float c = glm::dot(L, L) - m_Radius2;

	float t0, t1;
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

	hitInfo.uv = Vec2(-1.0f); //TEMP not implemented UV mapping
	hitInfo.ray = ray;
	hitInfo.normal = glm::normalize(L + hitInfo.t * ray.Dir());
	hitInfo.object = this;
	hitInfo.point = ray.Origin() + ray.Dir() * hitInfo.t;

	return true;
}
bool Sphere::BoundingBox(AABB& outputBox) const
{
	outputBox.Set(m_Position - Vec3(m_Radius), m_Position + Vec3(m_Radius));
	return true;
}

Vec3 Sphere::Random(Vec3 point) const
{
	Vec3 dir = m_Position - point;
	ONB uvw(dir);
	return uvw.local(PointInCone(m_Radius2, glm::length2(dir)));
}

float Sphere::PdfValue(const Vec3& origin, const Vec3& dir) const
{
	HitInfo hitInfo;
	if(!this->Hit(Ray(origin, dir), Camera::NearPlane(), Camera::FarPlane(), hitInfo))
		return 0.0f;

	float maxCosTheta = std::sqrt(1 - m_Radius2 / glm::length2(m_Position - origin));
	float omega = 2.0f * c_Pi * (1.0f - maxCosTheta);

	return 1.0f / omega;
}

const Vec3 Sphere::Position() const
{
	return m_Position;
}

const float Sphere::Radius() const
{
	return m_Radius;
}

const float Sphere::Radius2() const
{
	return m_Radius2;
}
