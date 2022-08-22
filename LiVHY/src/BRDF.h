/*! @file BRDF.h
*/
#pragma once
#include "util/types.h"
#include "util/ray.h"
#include "util/colors.h"
#include "glm/geometric.hpp"
#include "glm/common.hpp"

///@class BRDF
///@brief Bidirectional reflectance distribution function class.
class BRDF
{
public:
	/// @brief Single color constructor
	/// @param[in] color Color for all rays.
	/// @param[in] shininess Shininess of a material.
	/// @param[in] ior Index of Refraction of the material.
	/// @param[in] opacity Opacity of the diffuse material.
	/// @param[in] emissivity Brightness of emissive material.
	BRDF(const RGB& color, double shininess, 
		 double ior = 1.0, double opacity = 1.0, double emissivity = 0.0);

  	const RGB& Color() const;
	void SetColor(const RGB& rgb);

	const RGB& Emission() const;
	

	const double Opacity() const;
	const double IOR() const;
	const double Shininess() const;
	const double Emissivity() const;

	void SetOpacity(double opacity);
	void SetIOR(double ior);
	void SetShininess(double shininess);
	void SetEmissivity(double emissivity);


	const bool IsDiffuse() const;
	const bool IsSpecular() const;
	const bool IsTransparent() const;
	const bool IsEmissive() const;

	RGB DiffuseLighting(const Vec3& incidentDir, const Vec3& normal, const RGB& radiance) const;

	/// @brief The default BRDF.
	/// @return Pointer to a static default BRDF.
	static const BRDF* Default();

private:
	double m_Shininess = 1.0;
	double m_IOR = 1.0;
	double m_Opacity = 1.0;
	double m_Emissivity = 0.0;

	RGB m_Color = Colors::black;
	RGB m_Emission = Colors::black;

	static BRDF s_DefaultBrdf;

};