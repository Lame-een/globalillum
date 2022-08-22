#include "pch.h"
#include "math.h"

/// Quadratic equation solver with catastrophic cancelation avoidance
/// for more info see https://math.stackexchange.com/questions/866331
bool solveQuadratic(const double& a, const double& b, const double& c, double& x0, double& x1)
{
	double D = b * b - 4 * a * c;
	if(D < 0)
	{
		return false;	//no real solutions
	}
	else if(D == 0)
	{
		x0 = x1 = -0.5 * b / a;
	}
	else
	{
		double q = (b > 0) ? -0.5 * (b + sqrt(D)) : -0.5 * (b - sqrt(D));
		x0 = q / a;
		x1 = c / q;
	}
	if(x0 > x1) std::swap(x0, x1);

	return true;
}

double SchlicksApprox(const Vec3& incidentRay, const Vec3& normal, double n1, double n2)
{
	double R0 = glm::pow((n1 - n2) / (n1 + n2), 2.0);
	double alpha = glm::dot(normal, -incidentRay);

	return R0 + (1 - R0) * glm::pow((1 - alpha), 5.0);
}
