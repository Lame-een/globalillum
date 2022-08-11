/*! @file BRDF.h
*/
#pragma once
#include "util/types.h"
#include "util/colors.h"

///@class BRDF
///@brief Bidirectional reflectance distribution function class.
class BRDF
{
public:
	/// @brief Single color constructor
	/// @param[in] color Color for all rays.
	/// @param[in] shininess Shininess of a material.
	/// @param[in] iof Index of Refraction of the material.
	/// @param[in] opacity Opacity of the diffuse material.
	BRDF(const RGB& color, double shininess, 
		 double iof, double opacity);
	/// @brief Seperate color constructor
	/// @param[in] diffuse Diffuse color.
	/// @param[in] specular Specular color.
	/// @param[in] emission Emission color.
	/// @param[in] shininess Shininess of a material.
	/// @param[in] iof Index of Refraction of the material.
	/// @param[in] opacity Opacity of the diffuse material.
	BRDF(const RGB& diffuse, const RGB& specular, 
		 const RGB& emission, double shininess, double iof, 
		 double opacity);

  	const RGB& Diffuse() const;
	void SetDiffuse(const RGB& rgb);

  	const RGB& Specular() const;
	void SetSpecular(const RGB& rgb);
  	
	const RGB& Emission() const;
	void SetEmission(const RGB& rgb);
	
	const double Opacity() const;
	void SetOpacity(double opacity);
	
	const double IOF() const;
	void SetIOF(double iof);
	
	const double Shininess() const;
	void SetShininess(double shininess);



	const bool IsDiffuse() const;
	const bool IsGlossy() const;
	const bool IsTransparent() const;
	const bool IsEmissive() const;
	const bool IsShiny() const;

	/// @brief The default BRDF.
	/// @return Pointer to a static default BRDF.
	static const BRDF* Default();

private:
	double m_Shininess = 0.0;
	double m_IOF = 0.0;
	double m_Opacity = 1.0;


	static BRDF s_DefaultBrdf;

	RGB m_Diffuse;
	RGB m_Specular;
	RGB m_Emission;
};