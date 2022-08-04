#include "pointLight.h"

PointLight::PointLight() : Light(LightType::Point)
{
}

PointLight::PointLight(Vec3 pos, Vec3 color,
					   double intensity)
	: Light(pos, color, intensity, LightType::Point)
{
}
