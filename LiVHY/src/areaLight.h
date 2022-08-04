#pragma once
#include "light.h"
#include "types.h"

class AreaLight : public Light
{
public:
	AreaLight();
	AreaLight(Vec3 pos, Vec2 rect, RGB color, float intensity);
private:
	Vec2 m_Rect = Vec2(1.0, 1.0);
};