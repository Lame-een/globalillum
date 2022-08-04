#pragma once
#include <cmath>

class Viewport
{
public:
	Viewport();
	Viewport(int w, int h, float fov = M_PI / 3);

	const int Width() const;
	const int Height() const;

	const float HFOV() const;
	const float VFOV() const;

	void Resize(int w, int h);
	void SetFOV(float hfov);
private:
	void inline CalculateFOV();

	int m_Width = 256;
	int m_Height = 256;

	
	float m_HorizFOV = M_PI / 3;
	float m_VertFOV = M_PI / 3;
};