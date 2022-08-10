#include "BRDF.h"

BRDF::BRDF() {}
BRDF::BRDF(const RGB& color, double shininess,
		   double iof, double opacity)
	: m_Shininess(shininess), m_IOF(iof), m_Opacity(opacity),
	m_Diffuse(color), m_Specular(color), m_Emission(0.0)
{
}
BRDF::BRDF(const RGB& diffuse, const RGB& specular, 
		   const RGB& emission, double shininess, 
		   double iof, double opacity)
	: m_Shininess(shininess), m_IOF(iof), m_Opacity(opacity),
	m_Diffuse(diffuse), m_Specular(specular), m_Emission(emission)
{
}

const RGB& BRDF::Diffuse() const
{
	return m_Diffuse;
}
const RGB& BRDF::Specular() const
{
	return m_Specular;
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

void BRDF::SetDiffuse(const RGB& rgb)
{
	m_Diffuse = rgb;
}
void BRDF::SetSpecular(const RGB& rgb)
{
	m_Specular = rgb;
}
void BRDF::SetEmission(const RGB& rgb)
{
	m_Emission = rgb;
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

const int BRDF::IsDiffuse() const
{
	return ((m_Diffuse.r > 0.0) | (m_Diffuse.g > 0.0) | (m_Diffuse.b > 0.0));
}
const int BRDF::IsGlossy() const
{
	return ((m_Specular.r > 0.0) | (m_Specular.g > 0.0) | (m_Specular.b > 0.0));
}
const int BRDF::IsTransparent() const
{
	return (m_Opacity < 1.0f);
}
const int BRDF::IsEmissive() const
{
	return ((m_Emission.r > 0.0) | (m_Emission.g > 0.0) | (m_Emission.b > 0.0));
}
const int BRDF::IsShiny() const
{
	return (m_Shininess > 0.0);
}

const BRDF* BRDF::Default()
{
	return &s_DefaultBrdf;
}

BRDF BRDF::s_DefaultBrdf = BRDF(Colors::magenta, 0, 0, 1);