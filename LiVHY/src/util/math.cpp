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

double SchlicksApprox(const Vec3& incidentRay, const Vec3& normal, const double n2, const double n1)
{
	double R0 = glm::pow((n1 - n2) / (n1 + n2), 2.0);
	double cosine = abs(glm::dot(normal, incidentRay));

	return R0 + (1 - R0) * glm::pow((1 - cosine), 5.0);
}

double SchlicksApprox(const double cosine, double n2, double n1)
{
	double R0 = glm::pow((n1 - n2) / (n1 + n2), 2.0);

	return R0 + (1 - R0) * glm::pow((1 - cosine), 5.0);
}

Vec3 RandomCosineDir()
{
	double r0 = lameutil::g_RandGen.getDouble();
	double r1 = lameutil::g_RandGen.getDouble();
	double z = sqrt(1 - r1);

	double phi = 2 * M_PI * r0;
	double x = cos(phi) * sqrt(r1);
	double y = sin(phi) * sqrt(r1);

	return Vec3(x, y, z);
}

Vec3 RandomSpecularDir(double shininess)
{
	double r0 = lameutil::g_RandGen.getDouble();
	double r1 = lameutil::g_RandGen.getDouble();
	double z = pow(r1, 1.0 / (shininess + 1));

	double phi = 2 * M_PI * r0;
	double x = cos(phi) * sqrt(1.0 - z*z);
	double y = sin(phi) * sqrt(1.0 - z*z);

	return Vec3(x, y, z);
}

Vec3 PointInUnitSphere()
{
	Vec3 ret;
	do
	{
		// Sample direction in sphere
		ret.x = lameutil::g_RandGen.getDouble() * 2.0 - 1.0;
		ret.y = lameutil::g_RandGen.getDouble() * 2.0 - 1.0;
		ret.z = lameutil::g_RandGen.getDouble() * 2.0 - 1.0;
	} while(ret.x * ret.x + ret.y * ret.y + ret.z * ret.z > 1.0);
	return ret;
}

Vec2 PointInUnitCircle()	//this appreas faster than rejection?
{
	double theta = lameutil::g_RandGen.getDouble() * 2 * M_PI;
	double r = sqrt(lameutil::g_RandGen.getDouble());
	return Vec2(r * cos(theta), r * sin(theta));
}

Vec3 PointInCone(double sqrRadius, double sqrDist)
{
	double r1 = lameutil::g_RandGen.getDouble();
	double r2 = lameutil::g_RandGen.getDouble();
	double z = 1 + r2 * (sqrt(1 - sqrRadius / sqrDist) - 1);

	double phi = 2 * M_PI * r1;
	double x = cos(phi) * sqrt(1 - z * z);
	double y = sin(phi) * sqrt(1 - z * z);

	return Vec3(x, y, z);
}


ONB::ONB(const Vec3& normal)
	: u(), v(), w(normal)
{
	//this shouldn't be done - breaking constness
	Vec3* vptr = (Vec3*)&v;	//BAD
	Vec3* uptr = (Vec3*)&u;	//BAD

	//branchless ONB construction - pixar paper
	double sign = copysign(1.0, normal.z);
	const double a = -1.0 / (sign + normal.z);
	const double b = normal.x * normal.y * a;
	*vptr = Vec3(1.0 + sign * normal.x * normal.x * a, sign * b, -sign * normal.x);
	*uptr = Vec3(b, sign + normal.y * normal.y * a, -normal.y);
}

Vec3 ONB::operator[](int i) const
{
	switch(i)
	{
	case 0:
		return u;
	case 1:
		return v;
	case 2:
		return w;
	default:
		assert(false && "Index out of bound.\n");
		return Vec3();
	}
}

Vec3 ONB::local(double a, double b, double c) const
{
	return a * u + b * v + c * w;
}

Vec3 ONB::local(const Vec3& a) const
{
	return a.x * u + a.y * v + a.z * w;
}
