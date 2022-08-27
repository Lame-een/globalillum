#include "pch.h"
#include "tracerUtils.h"
//#include "glm/geometric.hpp"
//#include "lame/easyRandom.h"
//#include "glm/gtx/rotate_vector.hpp"

Vec3 TransmissiveRefract(const HitInfo& hitInfo)
{
	const double airIOR = 1.0;
	Vec3 normal = hitInfo.normal; //copy normal
	Vec3 view = -hitInfo.ray.Dir();
	double eta;
	double cosTheta = glm::dot(view, normal);

	if(cosTheta < 0)
	{
		//leaving material
		eta = hitInfo.object->Brdf()->IOR() / airIOR;
		normal = -normal; //flipping normal
		cosTheta = -cosTheta;
	}
	else
	{
		//entering material
		eta = airIOR / hitInfo.object->Brdf()->IOR();
	}

	double theta = acos(cosTheta);
	double sinPhi = eta * sin(theta);

	//total internal reflection check
	if(sinPhi < -1.0 || 1.0 < sinPhi)
	{
		// Return reflection direction
		return glm::reflect(view, normal);
	}

	// Otherwise return refraction direction
	double phi = asin(sinPhi);
	Vec3 viewParallel = glm::normalize(view + normal * cosTheta);

	return glm::normalize(viewParallel * tan(phi) - normal);
}

//return a vector offset from a perfect bounce
Vec3 SpecularSample(const Vec3& exact, double n, double cosTheta)
{
	//get the max value for alpha 
	//computed from: 2/pi * (angle between surface and exact) = 2/pi * (pi/2 - acos(N*V))
	//               = 1 - 2/pi * cos(|cos_theta|)
	double maxAngle = (1.0 - acos(abs(cosTheta)) * 2.0 / M_PI);

	//find axis perturbation values from brdf (Lafortune & Williams, 1994)
	double alpha = acos(pow((lameutil::g_RandGen.getDouble()), 1.0 / (n + 1.0))) * maxAngle;
	double phi = 2 * M_PI * lameutil::g_RandGen.getDouble();

	//vector perpendicular to the bounce
	Vec3 perpVec = glm::normalize(Vec3(exact[1], -exact[0], 0));
	if(1.0 - abs(exact[2]) < 0.1)
	{
		perpVec = glm::normalize(Vec3(exact[2], 0, -exact[0]));
	}

	//return vector should be perturbed by alpha from the exact
	Vec3 ret = perpVec * sin(alpha) + exact * cos(alpha);

	//rotate around axis by phi
	ret = glm::normalize(glm::rotate(ret, phi, exact));
	return ret;
}


//return a vector sampled from a weighted hemisphere around a normal
Vec3 DiffuseSample(Vec3 normal)
{
	double theta = acos(sqrt(lameutil::g_RandGen.getDouble()));
	double phi = 2 * M_PI * lameutil::g_RandGen.getDouble();

	//vector perpendicular to the surface
	Vec3 perpVec = glm::normalize(Vec3(normal[1], -normal[0], 0));

	if(1.0 - abs(normal[2]) < 0.1)
	{
		perpVec = Vec3(normal[2], 0, -normal[0]);
	}
	Vec3 ret = perpVec * sin(theta) + normal * cos(theta);

	//rotate around axis by phi
	ret = glm::normalize(glm::rotate(ret, phi, normal));
	return ret;
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