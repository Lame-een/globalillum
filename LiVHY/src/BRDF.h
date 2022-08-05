#pragma once
#include "util/types.h"

class BRDF
{
public:
	BRDF();
	BRDF(const RGB& color, double shininess, 
		 double iof, double opacity);
	BRDF(const RGB& diffuse, const RGB& specular, 
		 const RGB& emission, double shininess, double iof, 
		 double opacity);

  	const RGB& Diffuse() const;
  	const RGB& Specular() const;
  	const RGB& Emission() const;
	const double Opacity() const;
	const double IOF() const;
	const double Shininess() const;

	void SetDiffuse(const RGB& rgb);
	void SetSpecular(const RGB& rgb);
	void SetEmission(const RGB& rgb);

	void SetOpacity(double opacity);
	void SetIOF(double iof);
	void SetShininess(double shininess);

	const int IsDiffuse() const;
	const int IsGlossy() const;
	const int IsTransparent() const;
	const int IsEmissive() const;
	const int IsShiny() const;

private:
	double m_Shininess = 0.0;
	double m_IOF = 0.0;
	double m_Opacity = 1.0;

	RGB m_Diffuse = RGB(0.0);
	RGB m_Specular = RGB(0.0);
	RGB m_Emission = RGB(0.0);
};