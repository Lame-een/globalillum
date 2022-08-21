#include "pch.h"
#include "tracerUtils.h"
//#include "glm/geometric.hpp"
//#include "lame/easyRandom.h"
//#include "glm/gtx/rotate_vector.hpp"

//return perfect reflective bounce
Vec3 ReflectiveBounce(Vec3 normal, const Vec3& view, double cosTheta)
{
	// Flip normal to incident side of surface
	if(cosTheta < 0)
	{
		normal = -normal;
		cosTheta *= -1.0;
	}

	Vec3 dn = normal * cosTheta;  // dot(normal, view)
	Vec3 refl = view + dn * 2.0;
	return glm::normalize(refl);
}

//return direction of a perfect transmissive bounce (or reflective if internal refraction happened)
Vec3 TransmissiveBounce(const HitInfo& hitInfo, double cosTheta)
{
	double eta;
	Vec3 normal = hitInfo.normal;
	//flip normal if angle is bigger than 90°
	if(cosTheta < 0)
	{
		// exit - assuming air ior 1.0
		eta = hitInfo.object->Brdf()->IOF() / 1.0;
		normal = -normal;
		cosTheta *= -1;
	}
	else
	{
		// entry
		eta = 1.0 / hitInfo.object->Brdf()->IOF();
	}

	double theta = acos(cosTheta);
	double sinPhi = eta * sin(theta);

	//total internal reflection
	if(sinPhi < -1.0 || 1.0 < sinPhi)
	{
		return ReflectiveBounce(normal, hitInfo.ray.Dir(), cosTheta);
	}

	//return refraction direction
	double phi = asin(sinPhi);
	Vec3 viewParallel = glm::normalize(hitInfo.ray.Dir() + normal * cosTheta);
	return glm::normalize(viewParallel * tan(phi) - normal);
}


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
	
	//if(1.0 - abs(normal[2]) < 0.1)
	//{
	//	perpVec = Vec3(normal[2], 0, -normal[0]);
	//}
	Vec3 ret = perpVec * sin(theta) + normal * cos(theta);

	//rotate around axis by phi
	ret = glm::normalize(glm::rotate(ret, phi, normal));
	return ret;
}