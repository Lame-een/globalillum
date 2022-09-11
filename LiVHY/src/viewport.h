/// @file viewport.h
#pragma once
#include <cmath>

/// @class Viewport
/// @brief Class representing the output viewport of the render.
class Viewport
{
public:
	Viewport();
	Viewport(int w, int h, float fov = M_PI / 3.0f);

	const int Width() const;
	const int Height() const;

	const float HFOV() const;
	const float VFOV() const;
	const float AspectRatio() const;

	void Resize(int w, int h);
	void SetFOV(float hfov);
private:
	void CalculateFOV();

	int m_Width = 256;
	int m_Height = 256;

	float m_HorizFOV = c_Pi / 3.0f;
	float m_VertFOV = c_Pi / 3.0f;
	float m_Aspect = 1.0f;
};