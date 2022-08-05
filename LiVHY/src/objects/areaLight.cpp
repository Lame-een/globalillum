#include "areaLight.h"
AreaLight::AreaLight() : Light(LightType::Area)
{
}

AreaLight::AreaLight(const Vec3& pos, const Vec2& rect,
					 const RGB& color, double intensity)
	: Light(pos, color, intensity, LightType::Area)
{
	m_Rect = rect;
}