///@file util/math.h
/// This header contains math helper functions and math constants.

#pragma once
#include <utility>
#include "util/types.h"

/// @brief Quadratic equation solver function.
/// @param[in] a The quadratic coefficient.
/// @param[in] b The linear coefficient.
/// @param[in] c The free term.
/// @param[out] x0 The first solution of the equation.
/// @param[out] x1 The second solution of the equation.
/// @return Returns true if the equation has a real solution.
bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1);

/// @brief Calculates the reflective coefficient using Schlick's approximation.
/// @param incidentRay Incoming ray.
/// @param normal Normal on surface.
/// @param n2 Index of Refraction of inside medium.
/// @param n1 Index of Refraction of outside medium - assumed to be air.
/// @return 
float SchlicksApprox(const Vec3& incidentRay, const Vec3& normal, float n2, float n1 = 1.0);

float SchlicksApprox(const float cosine, float n2, float n1 = 1.0f);

Vec3 RandomCosineDir();
Vec3 RandomSpecularDir(float shininess);
Vec3 PointInUnitSphere();
Vec2 PointInUnitCircle();
Vec3 PointInCone(float radius, float sqrDist);

class ONB
{
public:
	ONB(const Vec3& normal);

	Vec3 operator[](int i) const;

	Vec3 local(float a, float b, float c) const;

	Vec3 local(const Vec3& a) const;
public:
	const Vec3 u = Vec3(0.0f, 0.0f, 0.0f);
	const Vec3 v = Vec3(0.0f, 0.0f, 0.0f);
	const Vec3 w;
};

/// @brief The main epsilon constant used for comparisons.
constexpr float c_Epsilon = 1e-6f;
constexpr float c_2_Pi = (float)M_2_PI;
constexpr float c_1_Pi = (float)M_1_PI;
constexpr float c_Pi = (float)M_PI;