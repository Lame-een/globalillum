///@file util/math.h
/// This header contains math helper functions and math constants.

#pragma once
#include <utility>

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
/// @param n1 Index of Refraction of outside medium.
/// @param n2 Index of Refraction of inside medium.
/// @return 
double SchlicksApprox(const Vec3& incidentRay, const Vec3& normal, double n1 = 1.0, double n2 = 1.0);

/// @brief The main epsilon constant used for comparisons.
constexpr double c_Epsilon = 1e-6;
constexpr double c_DoubleEpsilon = 1e-16;
constexpr float c_FloatEpsilon = 1e-7f;