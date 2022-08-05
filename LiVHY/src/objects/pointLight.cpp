#include "pointLight.h"

PointLight::PointLight() : Light(LightType::Point)
{
}

PointLight::PointLight(const Vec3& pos, const RGB& color,
					   double intensity)
	: Light(pos, color, intensity, LightType::Point)
{
}
