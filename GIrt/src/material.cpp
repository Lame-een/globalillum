#include "pch.h"
#include "material.h"

Material::Material(bool isEmissive, bool isTransmissive)
	: m_Emissive(isEmissive), m_Transmissive(isTransmissive)
{
}

RGB Material::Emit(const Ray& incidentRay, const HitInfo& hitInfo) const
{
	return Colors::black;
}

bool Material::Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const
{
	return false;
}

double Material::ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const
{
	return 0.0;
}

const Material* Material::Default()
{
	return &s_DefaultMat;
}

bool Material::IsEmissive() const
{
	return m_Emissive;
}

bool Material::IsTransmissive() const
{
	return m_Transmissive;
}

Diffuse::Diffuse(const RGB& color)
	: m_Color(color)
{
}

bool Diffuse::Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const
{
	scatterInfo.isSpecular = false;
	scatterInfo.color = m_Color;
	scatterInfo.SetPdf(new CosinePDF(hitInfo.normal));
	return true;
}

double Diffuse::ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const
{
	double cosine = glm::dot(hitInfo.normal, scatterRay.Dir());
	return (cosine < 0) ? 0 : cosine * M_1_PI;
}

RGB Diffuse::Color() const
{
	return m_Color;
}
void Diffuse::SetColor(const RGB& color)
{
	m_Color = color;
}

Glossy::Glossy(const RGB& color, double gloss, double exp)
	: m_Color(color), m_Gloss(gloss), m_Shininess(exp)
{
}

bool Glossy::Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const
{
	scatterInfo.color = m_Color;
	scatterInfo.isSpecular = false;
	scatterInfo.SetPdf(new MixturePDF(new SpecularPDF(hitInfo.normal, m_Shininess), new CosinePDF(hitInfo.normal), true));
	return true;
}
double Glossy::ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const
{
	double cosNAlpha = pow(glm::dot(hitInfo.normal, scatterRay.Dir()), m_Shininess + 1);
	return cosNAlpha < 0 ? 0 : (m_Shininess + 1) * cosNAlpha * M_2_PI;
}

RGB Glossy::Color() const
{
	return m_Color;
}
void Glossy::SetColor(const RGB& color)
{
	m_Color = color;
}

double Glossy::Shininess() const
{
	return m_Shininess;
}
void Glossy::SetShininess(double shininess)
{
	m_Shininess = shininess;
}

double Glossy::Gloss() const
{
	return m_Gloss;
}

void Glossy::SetGloss(double gloss)
{
	m_Gloss = gloss;
}



Specular::Specular(const RGB& color, double roughness)
	: m_Color(color), m_Roughness(std::clamp(roughness, 0.0, 1.0))
{
}

bool Specular::Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const
{
	Vec3 reflected = glm::reflect(incidentRay.Dir(), hitInfo.normal)+ m_Roughness * PointInUnitSphere();
	scatterInfo.bounceRay.SetDir(reflected);
	scatterInfo.bounceRay.SetOrigin(hitInfo.point + reflected * c_Epsilon);
	scatterInfo.color = m_Color;
	scatterInfo.isSpecular = true;
	scatterInfo.SetPdf(nullptr);
	return true;
}

double Specular::Roughness() const
{
	return m_Roughness;
}
void Specular::SetRoughness(double roughness)
{
	m_Roughness = roughness;
}

RGB Specular::Color() const
{
	return m_Color;
}
void Specular::SetColor(const RGB& color)
{
	m_Color = color;
}



Transmissive::Transmissive(double ior)
	: Material(false, true), m_IOR(ior)
{
}

double reflectance(double cosine, double ref_idx)
{
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat)
{
	auto cos_theta = glm::min(dot(-uv, n), 1.0);
	Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	Vec3 r_out_parallel = -sqrt(abs(1.0 - glm::length2(r_out_perp))) * n;
	return r_out_perp + r_out_parallel;
}

bool Transmissive::Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const
{
	scatterInfo.isSpecular = true;
	scatterInfo.SetPdf(nullptr);
	scatterInfo.color = Colors::white;
	//scatterInfo.bounceRay.SetOrigin(hitInfo.point);

	Vec3 normal = hitInfo.normal;
	Vec3 view = incidentRay.Dir();
	double cosTheta = glm::dot(-view, normal);
	double eta;

	if(cosTheta < 0)
	{
		//leaving material
		eta = m_IOR;
		normal = -normal;
		cosTheta = -cosTheta;
	}
	else
	{
		//entering material
		eta = 1.0 / m_IOR;
	}


	double theta = acos(cosTheta);
	double sinPhi = eta * sin(theta);

	//total internal reflection check and Fresnell reflection check (choose randomly)
	if((sinPhi < -1.0) || (1.0 < sinPhi) || (SchlicksApprox(cosTheta, eta) > lameutil::g_RandGen.getDouble()))
	{
		// Return reflection direction
		Vec3 reflVec = glm::reflect(view, normal);
		scatterInfo.bounceRay.SetDir(reflVec);
		scatterInfo.bounceRay.SetOrigin(hitInfo.point + reflVec * c_Epsilon);
		return true;
	}

	Vec3 refrVec = glm::refract(view, normal, eta);
	scatterInfo.bounceRay.SetDir(refrVec);
	scatterInfo.bounceRay.SetOrigin(hitInfo.point + refrVec * c_Epsilon);
	return true;
}

double Transmissive::IOR() const
{
	return m_IOR;
}

void Transmissive::SetIOR(double ior)
{
	m_IOR = ior;
}



Light::Light(RGB color, double intensity)
	: Material(true), m_Color(color* intensity)
{
}

RGB Light::Emit(const Ray& incidentRay, const HitInfo& hitInfo) const
{
	return m_Color;
}

RGB Light::Color()
{
	return m_Color;
}
void Light::SetColor(const RGB& color)
{
	m_Color = color;
}

#ifdef _DEBUG
Material Material::s_DefaultMat = Diffuse(Colors::magenta);
#else
Material Material::s_DefaultMat = Diffuse(Colors::black);
#endif