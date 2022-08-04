#pragma once
#include "types.h"

enum LightType{
	None,
	Point,
	Area
};

class Light
{
public:
	Light();

	const Vec3 Pos() const;
	const Vec3 Color() const;
	const double Intensity() const;

	void SetPos(Vec3 pos);
	void SetColor(Vec3 color);
	void SetIntensity(double intensity);

	const LightType type = LightType::None;

protected:
	Light(Vec3 pos, RGB color, double intensity, LightType type);
	Light(LightType type);
	
	Vec3 m_Pos = Vec3(1.0f,1.0f,1.0f);
	Vec3 m_Color = Vec3(1.0f,1.0f,1.0f);
	double m_Intensity = 1.0f;
};