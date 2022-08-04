#include "areaLight.h"
AreaLight::AreaLight() : Light(LightType::Area)
{
}

AreaLight::AreaLight(Vec3 pos, Vec2 rect, RGB color, float intensity)
	: Light(pos, color, intensity, LightType::Area)
{
	m_Rect = rect;
}