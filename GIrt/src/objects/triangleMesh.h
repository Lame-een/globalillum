/// @file objects/triangleMesh.h
#pragma once
#include <vector>
#include "triangle.h"
#include <string>

/// @class TriangleMesh
/// @brief Class describing a mesh object.
class TriangleMesh : public Object
{
public:
	//TriangleMesh();
	/// @brief Constructs all the triangles described by the vertices and faces.
	/// @param vertices Vertices of the triangles.
	/// @param faces Faces of the triangles.
	/// @param brdf Brdf applied to the triangle.
	//TODO: add check if data in faces is correct
	TriangleMesh(const std::vector<Vec3>& vertices, const std::vector<Vec3i> faces, const Material* material = Material::Default(), bool cull = true, bool samplingTarget = false);
	~TriangleMesh();
	
	const std::vector<Object*>& Triangles() const;
	
	/// @deprecated This function should not be used as it checks every triangle.
	///				Use Hit implemented in BVHNode.
	bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) const override;
	/// @deprecated Not of practical use. Use BoundingBox in combination with BVHNode.
    bool BoundingBox(AABB& outputBox) const override;

	//const std::vector<Vec3> Vertices();
	//const std::vector<Vec3i> Faces();
protected:
	TriangleMesh(const Material* material = Material::Default(), bool cull = true, bool samplingTarget = false);

	std::vector<Object*> m_Triangles;

	//std::vector<Vec3> m_Vertices;	//will be used for OpenGL?
	//std::vector<Vec3i> m_Faces;
};
