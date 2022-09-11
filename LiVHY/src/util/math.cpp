#include "pch.h"
#include "math.h"

/// Quadratic equation solver with catastrophic cancelation avoidance
/// for more info see https://math.stackexchange.com/questions/866331
bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
	float D = b * b - 4.0f * a * c;
	if(D < 0.0f)
	{
		return false;	//no real solutions
	}
	else if(D == 0.0f)
	{
		x0 = x1 = -0.5f * b / a;
	}
	else
	{
		float q = (b > 0.0f) ? -0.5f * (b + sqrtf(D)) : -0.5f * (b - sqrtf(D));
		x0 = q / a;
		x1 = c / q;
	}
	if(x0 > x1) std::swap(x0, x1);

	return true;
}

float SchlicksApprox(const Vec3& incidentRay, const Vec3& normal, const float n2, const float n1)
{
	float R0 = std::pow((n1 - n2) / (n1 + n2), 2.0f);
	float cosine = abs(glm::dot(normal, incidentRay));

	return R0 + (1 - R0) * std::pow((1 - cosine), 5.0f);
}

float SchlicksApprox(const float cosine, float n2, float n1)
{
	float R0 = glm::pow((n1 - n2) / (n1 + n2), 2.0f);

	return R0 + (1.0f - R0) * std::pow((1 - cosine), 5.0f);
}

Vec3 RandomCosineDir()
{
	float r0 = lameutil::g_RandGen.getFloat();
	float r1 = lameutil::g_RandGen.getFloat();
	float z = std::sqrt(1.0f - r1);

	float phi = 2 * c_Pi * r0;
	float x = std::cos(phi) * std::sqrt(r1);
	float y = std::sin(phi) * std::sqrt(r1);

	return Vec3(x, y, z);
}

Vec3 RandomSpecularDir(float shininess)
{
	float r0 = lameutil::g_RandGen.getFloat();
	float r1 = lameutil::g_RandGen.getFloat();
	float z = std::pow(r1, 1.0f / (shininess + 1.0f));

	float phi = 2 * c_Pi * r0;
	float x = std::cos(phi) * std::sqrt(1.0f - z*z);
	float y = std::sin(phi) * std::sqrt(1.0f - z*z);

	return Vec3(x, y, z);
}

Vec3 PointInUnitSphere()
{
	Vec3 ret;
	do
	{
		// Sample direction in sphere
		ret.x = lameutil::g_RandGen.getFloat() * 2.0f - 1.0f;
		ret.y = lameutil::g_RandGen.getFloat() * 2.0f - 1.0f;
		ret.z = lameutil::g_RandGen.getFloat() * 2.0f - 1.0f;
	} while(ret.x * ret.x + ret.y * ret.y + ret.z * ret.z > 1.0f);
	return ret;
}

Vec2 PointInUnitCircle()	//this appreas faster than rejection?
{
	float theta = lameutil::g_RandGen.getFloat() * 2.0f * c_Pi;
	float r = std::sqrt(lameutil::g_RandGen.getFloat());
	return Vec2(r * std::cos(theta), r * std::sin(theta));
}

Vec3 PointInCone(float sqrRadius, float sqrDist)
{
	float r1 = lameutil::g_RandGen.getFloat();
	float r2 = lameutil::g_RandGen.getFloat();
	float z = 1.0f + r2 * (std::sqrt(1.0f - sqrRadius / sqrDist) - 1.0f);

	float phi = 2 * c_Pi * r1;
	float x = std::cos(phi) * std::sqrt(1.0f - z * z);
	float y = std::sin(phi) * std::sqrt(1.0f - z * z);

	return Vec3(x, y, z);
}


ONB::ONB(const Vec3& normal)
	: u(), v(), w(normal)
{
	//this shouldn't be done - breaking constness
	Vec3* vptr = (Vec3*)&v;	//BAD
	Vec3* uptr = (Vec3*)&u;	//BAD

	//branchless ONB construction - pixar paper
	float sign = std::copysign(1.0f, normal.z);
	const float a = -1.0f / (sign + normal.z);
	const float b = normal.x * normal.y * a;
	*vptr = Vec3(1.0f + sign * normal.x * normal.x * a, sign * b, -sign * normal.x);
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

Vec3 ONB::local(float a, float b, float c) const
{
	return a * u + b * v + c * w;
}

Vec3 ONB::local(const Vec3& a) const
{
	return a.x * u + a.y * v + a.z * w;
}
