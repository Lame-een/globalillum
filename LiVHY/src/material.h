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
	virtual double ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const;

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
	double ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const override;

	RGB Color() const;
	void SetColor(const RGB& color);

private:
	RGB m_Color;
};

class Glossy : public Material
{
public:
	Glossy(const RGB& color, double gloss, double shininess);

	bool Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const override;
	double ScatterPDF(const Ray& incidentRay, const HitInfo& hitInfo, const Ray& scatterRay) const override;

	RGB Color() const;
	void SetColor(const RGB& color);

	double Shininess() const;
	void SetShininess(double shininess);

	double Gloss() const;
	void SetGloss(double gloss);

private:
	RGB m_Color;
	double m_Gloss;
	double m_Shininess;
};


class Specular : public Material
{
public:
	Specular(const RGB& color, double roughness);

	bool Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const override;

	double Roughness() const;
	void SetRoughness(double roughness);

	RGB Color() const;
	void SetColor(const RGB& color);

private:
	RGB m_Color;
	double m_Roughness;
};


class Transmissive : public Material
{
public:
	Transmissive(double ior);

	bool Scatter(const Ray& incidentRay, const HitInfo& hitInfo, ScatterInfo& scatterInfo) const override;

	double IOR() const;
	void SetIOR(double ior);

private:
	double m_IOR; //index of refraction
};


class Light : public Material
{
public:
	Light(RGB color, double intensity = 1.0);

	virtual RGB Emit(const Ray& incidentRay, const HitInfo& hitInfo) const override;

	RGB Color();
	void SetColor(const RGB& color);
private:
	RGB m_Color;
};
