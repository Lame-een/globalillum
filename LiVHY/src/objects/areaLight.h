#pragma once
#include "light.h"

class AreaLight : public Light
{
public:
	AreaLight();
	AreaLight(const Vec3& pos, const Vec2& rect, 
			  const RGB& color, double intensity);
private:
	Vec2 m_Rect = Vec2(1.0, 1.0);
};