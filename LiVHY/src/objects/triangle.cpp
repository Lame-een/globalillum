#include "triangle.h"
#include "glm/geometric.hpp"
#include "util/math.h"

Triangle::Triangle(const Vec3& a, const Vec3& b, const Vec3& c, const BRDF* brdf)
	: Object(brdf)
{
	m_Vertices[0] = a;
	m_Vertices[1] = b;
	m_Vertices[2] = c;

	m_Normal = glm::normalize(glm::cross(b - a, c - a));
}
Triangle::Triangle(const Vec3* arr, const BRDF* brdf)
	: Object(brdf)
{
	m_Vertices[0] = arr[0];
	m_Vertices[1] = arr[1];
	m_Vertices[2] = arr[2];

	m_Normal = glm::normalize(glm::cross(arr[1] - arr[0], arr[2] - arr[0]));
}

bool Triangle::Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo)
{
	Vec3 ab = m_Vertices[1] - m_Vertices[0];
	Vec3 ac = m_Vertices[2] - m_Vertices[0];
	Vec3 pvec = glm::cross(ray.Dir(), ac);
	double det = glm::dot(ab, pvec);

	if(det < c_DoubleEpsilon) return false; //either hitting backface or parallel to the triangle

	double invDet = 1 / det;

	Vec3 tvec = ray.Origin() - m_Vertices[0];
	double& u = hitInfo.uv[0];
	u = glm::dot(tvec, pvec) * invDet;
	if(u < 0 || u > 1) return false;

	Vec3 qvec = glm::cross(tvec, ab);
	double& v = hitInfo.uv[1];
	v = glm::dot(ray.Dir(), qvec) * invDet;
	if(v < 0 || u + v > 1) return false;

	hitInfo.t = glm::dot(ac, qvec) * invDet;
	hitInfo.normal = m_Normal;
	hitInfo.object = this;
	hitInfo.point = ray.Origin() + ray.Dir()*hitInfo.t;

	return true;
}

bool Triangle::BoundingBox(AABB& outputBox) const
{
	Vec3 min = glm::min(glm::min(m_Vertices[0], m_Vertices[1]), m_Vertices[2]);
	Vec3 max = glm::max(glm::max(m_Vertices[0], m_Vertices[1]), m_Vertices[2]);
	for(int axis = 0; axis < 3; axis++)
	{
		if(max[axis] - min[axis] < c_Epsilon)
		{
			max[axis] += c_Epsilon;
			min[axis] -= c_Epsilon;
		}
	}
	outputBox.Set(min, max);
	return true;
}

void Triangle::SetVertex(const Vec3& point, size_t index)
{
	assert(index < 3 && "Index out of bounds.");

	m_Vertices[index] = point;
}

const Vec3* Triangle::Vertices() const
{
	return m_Vertices;
}

const Vec3& Triangle::Vertex(size_t index) const
{
	assert(index < 3 && "Index out of bounds.");

	return m_Vertices[index];
}

const Vec3& Triangle::Normal() const
{
	return m_Normal;
}
