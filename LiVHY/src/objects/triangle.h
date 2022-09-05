/// @file objects/triangle.h
#pragma once
#include "object.h"

/// @class Triangle
/// @brief Class describing a single triangle.
class Triangle : public Object
{
public:
	/// @brief Constructor which takes in seperate vertices, 
	///		   vertices should be in CCW order.
	/// @param a
	/// @param b
	/// @param c
	/// @param brdf Brdf applied to the triangle.
	Triangle(const Vec3& a, const Vec3& b, const Vec3& c, const Material* material = Material::Default(), bool cull = true, bool samplingTarget = false);
	/// @brief Constructor which takes in an array of vertices.
	/// @param arr Pointer to the verex array. Assumed to be of length 3.
	/// @param brdf Brdf applied to the triangle.
	Triangle(const Vec3* arr, const Material* material = Material::Default(), bool cull = true, bool samplingTarget = false);

	/// @brief Ray intersection checker function.
	/// @param[in] ray Ray to check against.
	/// @param[in] tMin Minimum ray length.
	/// @param[in] tMax Maximum ray length.
	/// @param[out] hitInfo Reference to the information about the hit.
	/// @return Returns true if the ray hit the triangle.
	bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) const override;
	/// @brief Constructs a bounding box around the triangle.
	/// @param[out] outputBox The AABB of the triangle.
	/// @return Returns true if able to construct an AABB.
	bool BoundingBox(AABB& outputBox) const override;

	Vec3 Random(Vec3 point) const override;
	double PdfValue(const Vec3& origin, const Vec3& dir) const override;

	const Vec3* Vertices() const;
	const Vec3& Vertex(size_t index) const;

	const Vec3& Normal() const;
	const double Area() const;

private:

	Vec3 m_Vertices[3];
	Vec3 m_Normal;
	double m_Area;
};