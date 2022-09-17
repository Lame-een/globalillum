#include "pch.h"
#include "quad.h"

Quad::Quad(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, Material* material, bool cull, bool samplingTarget)
	: TriangleMesh(material, cull, samplingTarget)
{
	m_Triangles.push_back(new Triangle(a, b, c, material, cull));
	m_Triangles.push_back(new Triangle(c, d, a, material, cull));
}

Quad::Quad(const Vec3* verts, Material* material, bool cull, bool samplingTarget)
	: TriangleMesh(material, cull, samplingTarget)
{
	m_Triangles.push_back(new Triangle(verts[0], verts[1], verts[2], material, cull));
	m_Triangles.push_back(new Triangle(verts[2], verts[3], verts[0], material, cull));
}
