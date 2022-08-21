#include "pch.h"
#include "quad.h"

Quad::Quad(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, BRDF* brdf)
{
	m_Triangles.push_back(new Triangle(a,b,c,brdf));
	m_Triangles.push_back(new Triangle(c,d,a,brdf));
}

Quad::Quad(const Vec3* verts, BRDF* brdf)
{
	m_Triangles.push_back(new Triangle(verts[0],verts[1],verts[2],brdf));
	m_Triangles.push_back(new Triangle(verts[2],verts[3],verts[0],brdf));
}
