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
bool solveQuadratic(const double& a, const double& b, const double& c, double& x0, double& x1);

/// @brief Calculates the reflective coefficient using Schlick's approximation.
/// @param incidentRay Incoming ray.
/// @param normal Normal on surface.
/// @param n2 Index of Refraction of inside medium.
/// @param n1 Index of Refraction of outside medium - assumed to be air.
/// @return 
double SchlicksApprox(const Vec3& incidentRay, const Vec3& normal, double n2, double n1 = 1.0);

double SchlicksApprox(const double cosine, double n2, double n1 = 1.0);

Vec3 RandomCosineDir();
Vec3 RandomSpecularDir(double shininess);
Vec3 PointInUnitSphere();
Vec2 PointInUnitCircle();
Vec3 PointInCone(double radius, double sqrDist);

class ONB
{
public:
	ONB(const Vec3& normal);

	Vec3 operator[](int i) const;

	Vec3 local(double a, double b, double c) const;

	Vec3 local(const Vec3& a) const;
public:
	const Vec3 u = Vec3(0, 0, 0);
	const Vec3 v = Vec3(0, 0, 0);
	const Vec3 w;
};

/// @brief The main epsilon constant used for comparisons.
constexpr double c_Epsilon = 1e-6;
constexpr double c_DoubleEpsilon = 1e-16;
constexpr float c_FloatEpsilon = 1e-7f;