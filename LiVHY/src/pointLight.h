#pragma once
#include "light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(Vec3 pos, RGB color, double intensity);

private:
};