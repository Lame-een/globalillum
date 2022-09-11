#include "pch.h"
#include "triangle.h"
#include "camera.h"
//#include "glm/geometric.hpp"
//#include "util/math.h"

Triangle::Triangle(const Vec3& a, const Vec3& b, const Vec3& c, const Material* material, bool cull, bool samplingTarget)
	: Object(material, cull, samplingTarget)
{
	m_Vertices[0] = a;
	m_Vertices[1] = b;
	m_Vertices[2] = c;

	m_Normal = glm::normalize(glm::cross(b - a, c - a));
	m_Area = glm::length(glm::cross(b - a, c - a)) / 2;
#ifdef PRINT_NORMALS
	std::cout << glm::to_string((a + b + c) / 3.0) << glm::to_string(m_Normal) << std::endl;
#endif
}
Triangle::Triangle(const Vec3* arr, const Material* material, bool cull, bool samplingTarget)
	: Object(material, cull, samplingTarget)
{
	m_Vertices[0] = arr[0];
	m_Vertices[1] = arr[1];
	m_Vertices[2] = arr[2];

	m_Normal = glm::normalize(glm::cross(arr[1] - arr[0], arr[2] - arr[0]));
	m_Area = glm::dot(arr[1] - arr[0], arr[2] - arr[0]);
}

bool Triangle::Hit(const Ray& ray, float tMin, float tMax, HitInfo& hitInfo) const
{
	Vec3 ab = m_Vertices[1] - m_Vertices[0];
	Vec3 ac = m_Vertices[2] - m_Vertices[0];
	Vec3 pvec = glm::cross(ray.Dir(), ac);
	float det = glm::dot(ab, pvec);

	if(m_Cull)
	{
		if((det < c_Epsilon))
		{
			return false; //backface culling
		}
	}
	else
	{
		if(abs(det) < c_Epsilon)
		{
			return false; //parallel to the triangle
		}
	}

	float invDet = 1 / det;

	Vec3 tvec = ray.Origin() - m_Vertices[0];
	float& u = hitInfo.uv[0];
	u = glm::dot(tvec, pvec) * invDet;
	if(u < -c_Epsilon || u > 1 + c_Epsilon) return false;	//added epsilon to reduce gaps in meshes

	Vec3 qvec = glm::cross(tvec, ab);
	float& v = hitInfo.uv[1];
	v = glm::dot(ray.Dir(), qvec) * invDet;
	if(v < -c_Epsilon || u + v > 1 + c_Epsilon) return false;

	hitInfo.ray = ray;
	hitInfo.t = glm::dot(ac, qvec) * invDet;
	if(hitInfo.t < tMin) return false;

	hitInfo.normal = m_Normal;
	hitInfo.object = this;
	hitInfo.point = ray.Origin() + ray.Dir() * hitInfo.t;

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

Vec3 Triangle::Random(Vec3 point) const
{
	float r0 = lameutil::g_RandGen.getFloat();
	float r1 = lameutil::g_RandGen.getFloat();

	if(r0 + r1 >= 1)
	{
		r0 = 1 - r0;
		r1 = 1 - r1;
	}

	Vec3 ab = m_Vertices[1] - m_Vertices[0];
	Vec3 ac = m_Vertices[2] - m_Vertices[0];
	Vec3 samplePoint = r0 * ab + r1 * ac + m_Vertices[0];
	return samplePoint - point;
}

float Triangle::PdfValue(const Vec3& origin, const Vec3& dir) const
{
	HitInfo hitInfo;
	if(!this->Hit(Ray(origin, dir), Camera::NearPlane(), Camera::FarPlane(), hitInfo))
		return 0.0f;

	//float dist2 = hitInfo.t * hitInfo.t * glm::length2(dir);
	//float cosine = glm::abs(glm::dot(dir, hitInfo.normal)) / glm::length(dir);
	float dist2 = hitInfo.t * hitInfo.t;
	float cosine = glm::abs(glm::dot(dir, hitInfo.normal));

	return dist2 / (cosine * m_Area);
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

const float Triangle::Area() const
{
	return m_Area;
}