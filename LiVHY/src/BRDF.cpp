#include "pch.h"
#include "BRDF.h"

/// @class BRDF
/// The class describes the properties of a BRDF.

BRDF::BRDF(const RGB& color, double shininess,
		   double iof, double opacity, double emissivity)
	: m_Shininess(shininess), m_IOF(iof), m_Opacity(opacity), m_Emissivity(0.0),
	m_Color(color), m_Emission(color * emissivity)
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


const double BRDF::Opacity() const
{
	return m_Opacity;
}
const double BRDF::IOF() const
{
	return m_IOF;
}
const double BRDF::Shininess() const
{
	return m_Shininess;
}
const double BRDF::Emissivity() const
{
	return m_Emissivity;
}

void BRDF::SetOpacity(double opacity)
{
	m_Opacity = opacity;
}
void BRDF::SetIOF(double iof)
{
	m_IOF = iof;
}
void BRDF::SetShininess(double shininess)
{
	m_Shininess = shininess;
}
void BRDF::SetEmissivity(double emissivity)
{
	m_Emissivity = emissivity;
	m_Emission = m_Color * emissivity;
}





const bool BRDF::IsDiffuse() const
{
	return (m_Opacity > 0.0);
}
const bool BRDF::IsGlossy() const
{
	return (m_Shininess > 0.0);
}
const bool BRDF::IsTransparent() const
{
	return (m_Opacity < 1.0f);
}
const bool BRDF::IsEmissive() const
{
	return (m_Emissivity > 0.0);
}


RGB BRDF::DiffuseLighting(const Vec3& incidentDir, const Vec3& normal, const RGB& radiance) const
{
	double cosine = glm::max(0.0, glm::dot(-incidentDir, normal));

    return cosine * (radiance * m_Color);
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