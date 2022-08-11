/// @file objects/pointLight.h
#pragma once
#include "light.h"

/// @class PointLight
/// @brief Simplest light type.
class PointLight : public Light
{
public:
	PointLight();
	PointLight(const Vec3& pos, const RGB& color, 
			   double intensity = 1.0);

private:
};