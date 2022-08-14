/// @file objects/light.h
#pragma once
#include "util/types.h"
#include "util/math.h"
#include "BRDF.h"
#include "object.h"
#include "glm/gtx/norm.hpp"

/// @brief Type of the Light.
enum LightType
{
	None,
	Point,
	Area
};

/// @class Light 
/// @brief Class defining a light.
class Light
{
public:
	Light();

	const Vec3& Pos() const;
	const Vec3& Color() const;
	const double Intensity() const;

	void SetPos(const Vec3& pos);
	void SetColor(const Vec3& color);
	void SetIntensity(double intensity);

	/// @brief Type of the light - set by derived classes.
	const LightType type = LightType::None;

	//virtual RGB Reflection(const HitInfo& hitInfo) const = 0;
	virtual RGB DiffuseReflection(const HitInfo& hitInfo) const = 0;
	virtual RGB SpecularReflection(const HitInfo& hitInfo) const = 0;

protected:
	Light(const Vec3& pos, const RGB& color, double intensity, LightType type);
	Light(LightType type);

	Vec3 m_Pos = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 m_Color = Vec3(1.0f, 1.0f, 1.0f);
	double m_Intensity = 1.0f;
};