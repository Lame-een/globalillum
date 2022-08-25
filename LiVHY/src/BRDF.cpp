#include "pch.h"
#include "BRDF.h"

/// @class BRDF
/// The class describes the properties of a BRDF.

BRDF::BRDF(const RGB& color, double shininess, double reflectivity,
		   double ior, double opacity, double emissivity)
	: m_Shininess(shininess), m_Reflectivity(reflectivity), m_IOR(ior), 
	m_Opacity(opacity), m_Emissivity(emissivity), m_Color(color), m_Emission(color * emissivity)
{
}

const RGB& BRDF::Color() const
{
	return m_Color;
}
void BRDF::SetColor(const RGB& rgb){
	m_Color = rgb;
	m_Emission = rgb * m_Emissivity;
}

const RGB& BRDF::Emission() const
{
	return m_Emission;
}


double BRDF::Opacity() const
{
	return m_Opacity;
}
double BRDF::IOR() const
{
	return m_IOR;
}
double BRDF::Shininess() const
{
	return m_Shininess;
}
double BRDF::Reflectivity() const
{
	return m_Reflectivity;
}
double BRDF::Emissivity() const
{
	return m_Emissivity;
}

void BRDF::SetOpacity(double opacity)
{
	m_Opacity = opacity;
}
void BRDF::SetIOR(double ior)
{
	m_IOR = ior;
}
void BRDF::SetShininess(double shininess)
{
	m_Shininess = shininess;
}
void BRDF::SetReflectivity(double reflectivity)
{
	m_Reflectivity = reflectivity;
}
void BRDF::SetEmissivity(double emissivity)
{
	m_Emissivity = emissivity;
	m_Emission = m_Color * emissivity;
}





const bool BRDF::IsDiffuse() const
{
	return (m_Opacity > 0.0 && m_Reflectivity < 1.0);
}
const bool BRDF::IsSpecular() const
{
	return (m_Shininess > 0.0);
}
const bool BRDF::IsMetallic() const
{
	return (m_Reflectivity > 0.0);
}
const bool BRDF::IsTransparent() const
{
	return (m_Opacity < 1.0f);
}
const bool BRDF::IsEmissive() const
{
	return (m_Emissivity > 0.0);
}


RGB BRDF::DiffuseLighting(const Vec3& rayDir, const Vec3& normal, RGB radiance) const
{
	double cosTheta = glm::dot(normal, rayDir);
	cosTheta = cosTheta < 0 ? 0 : cosTheta / M_PI;
    return cosTheta * (radiance * m_Color);
}



/// The default BRDF is defined depending on whether the
/// project is in release or debug mode.
/// If in _DEBUG it's defined as a diffuse magenta material.
/// Otherwise it's a diffuse black material.
const BRDF* BRDF::Default()
{
	return &s_DefaultBrdf;
}

#ifdef _DEBUG
BRDF BRDF::s_DefaultBrdf = BRDF(Colors::magenta, 1, 1, 1, 0);
#else
BRDF BRDF::s_DefaultBrdf = BRDF(Colors::black, 1, 0, 0, 0);
#endif