/// @file objects/pointLight.h
#pragma once
#include "light.h"
#include "scene.h"

/// @class PointLight
/// @brief Simplest light type.
class PointLight : public Light
{
public:
	PointLight();
	PointLight(const Vec3& pos, const RGB& color,
			   double intensity = 1.0);

	const double Area() const override;

	RGB DiffuseReflection(const HitInfo& hitInfo) const override;
	RGB SpecularReflection(const HitInfo& hitInfo) const override;
	RGB Reflection(const HitInfo& hitInfo) const override;

	void LightReflection(const Scene& scene, const HitInfo& hitInfo, RGB& color) const override;
private:
};