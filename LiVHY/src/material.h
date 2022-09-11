#pragma once
#include "util/types.h"
#include "util/ray.h"
#include "lame/easyRandom.h"
#include "pdf.h"
#include "util/scatterInfo.h"
#include "util/hitInfo.h"

class Material
{
public:
	Material(bool isEmissive = false, bool isTransmissive = false);
	virtual RGB Emit(const Ray& incidentRay, const HitInfo& hitInfo) const;

	virtual bool Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const;
	virtual float ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const;

	static const Material* Default();

	bool IsEmissive() const;
	bool IsTransmissive() const;

private:
	bool m_Emissive;
	bool m_Transmissive;

	static Material s_DefaultMat;
};

class Diffuse : public Material
{
public:
	Diffuse(const RGB& color);

	bool Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const override;
	float ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const override;

	RGB Color() const;
	void SetColor(const RGB& color);

private:
	RGB m_Color;
};

class Glossy : public Material
{
public:
	Glossy(const RGB& color, float gloss, float shininess);

	bool Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const override;
	float ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const override;

	RGB Color() const;
	void SetColor(const RGB& color);

	float Shininess() const;
	void SetShininess(float shininess);

	float Gloss() const;
	void SetGloss(float gloss);

private:
	RGB m_Color;
	float m_Gloss;
	float m_Shininess;
};


class Specular : public Material
{
public:
	Specular(const RGB& color, float roughness);

	bool Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const override;

	float Roughness() const;
	void SetRoughness(float roughness);

	RGB Color() const;
	void SetColor(const RGB& color);

private:
	RGB m_Color;
	float m_Roughness;
};


class Transmissive : public Material
{
public:
	Transmissive(float ior);

	bool Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const override;

	float IOR() const;
	void SetIOR(float ior);

private:
	float m_IOR; //index of refraction
};


class Light : public Material
{
public:
	Light(RGB color, float intensity = 1.0f);

	virtual RGB Emit(const Ray& incidentRay, const HitInfo& hitInfo) const override;

	RGB Color();
	void SetColor(const RGB& color);
private:
	RGB m_Color;
};
