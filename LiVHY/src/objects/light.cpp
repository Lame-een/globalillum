#include "pch.h"
#include "light.h"

Light::Light() {}
Light::Light(LightType type) : type(type)
{
}

Light::Light(const Vec3& pos, const RGB& color,
			 double intensity, LightType type)
	: m_Pos(pos), m_Color(color), m_Intensity(intensity),
	type(type)
{
}

const Vec3& Light::Pos() const
{
	return m_Pos;
}
const Vec3& Light::Color() const
{
	return m_Color;
}
const double Light::Intensity() const
{
	return m_Intensity;
}

void Light::SetPos(const Vec3& pos)
{
	m_Pos = pos;
}
void Light::SetColor(const Vec3& color)
{
	m_Color = color;
}
void Light::SetIntensity(double intensity)
{
	m_Intensity = intensity;
}

