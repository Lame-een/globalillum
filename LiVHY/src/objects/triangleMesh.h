#pragma once
#include <vector>
#include "triangle.h"

class TriangleMesh : public Object
{
public:
	TriangleMesh(const BRDF* brdf = BRDF::Default());
	TriangleMesh(const std::vector<Vec3>& vertices, const std::vector<Vec3i> faces, const BRDF* brdf = BRDF::Default());
	~TriangleMesh();
	
	const std::vector<Object*>& Triangles() const;

	bool Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo) override;
    bool BoundingBox(AABB& outputBox) const override;

	//const std::vector<Vec3> Vertices();
	//const std::vector<Vec3i> Faces();
private:

	std::vector<Object*> m_Triangles;

	//std::vector<Vec3> m_Vertices;	//will be used for OpenGL?
	//std::vector<Vec3i> m_Faces;
};
