#include "math.h"

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