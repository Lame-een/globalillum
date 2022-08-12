/// @file objects/quad.h
#pragma once
#include "triangleMesh.h"

/// @class Quad
/// @brief A quad object consisting of 2 triangles
class Quad : public TriangleMesh
{
public:
	/// @brief Constructor taking in seperate vertices, 
	///        vertices should be in CCW order. 
	/// @param brdf Brdf applied to the quad.
	Quad(const Vec3& a,const Vec3& b,const Vec3& c, const Vec3& d, BRDF* brdf);
	/// @brief Constructor which takes in an array of vertices.
	/// @param verts Pointer to the verex array. Assumed to be of length 4.
	/// @param brdf Brdf applied to the quad.
	Quad(const Vec3* verts, BRDF* brdf);
};