#include "pch.h"
#include "object.h"


Object::Object(bool cull, bool samplingTarget)
	: m_Cull(cull), m_SamplingTarget(samplingTarget)
{
}

Object::Object(const Material* mat, bool cull, bool samplingTarget)
	: m_Mat(mat), m_Cull(cull), m_SamplingTarget(samplingTarget)
{
}


bool Object::Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) const
{
	return true;
}

bool Object::BoundingBox(AABB& outputBox) const
{
	return true;
}

Vec3 Object::Random(Vec3 point) const
{
	return Vec3(1, 0, 0);
}

double Object::PdfValue(const Vec3& origin, const Vec3& dir) const
{
	return 0.0;
}

bool Object::IsSamplingTarget() const
{
	return m_SamplingTarget;
}

const Material* Object::GetMaterial() const
{
	return m_Mat;
}