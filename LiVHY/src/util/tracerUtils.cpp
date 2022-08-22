#include "pch.h"
#include "tracerUtils.h"
//#include "glm/geometric.hpp"
//#include "lame/easyRandom.h"
//#include "glm/gtx/rotate_vector.hpp"


//importance sampling to return a vector offset from a perfect bounce
Vec3 SpecularImportanceSample(const Vec3& exact, double n, double cosTheta)
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

	/*
	if (1.0 - abs(exact[2]) < 0.1) {
	  perpVec = glm::normalize(Vec3(exact[2], 0, -exact[0]));
	}
	*/

	//return vector should be perturbed by alpha from the exact
	Vec3 ret = perpVec * sin(alpha) + exact * cos(alpha);

	//rotate around axis by phi
	ret = glm::normalize(glm::rotate(ret, phi, exact));
	return ret;
}


//return a vector sampled from a weighted hemisphere around a normal
Vec3 DiffuseImportanceSample(Vec3 normal)
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