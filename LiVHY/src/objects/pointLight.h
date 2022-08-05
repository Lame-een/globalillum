#pragma once
#include "light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(const Vec3& pos, const RGB& color, 
			   double intensity);

private:
};