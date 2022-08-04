#pragma once
#include <cmath>

class Viewport
{
public:
	Viewport();
	Viewport(int w, int h, double fov = M_PI / 3);

	const int Width() const;
	const int Height() const;

	const double HFOV() const;
	const double VFOV() const;

	void Resize(int w, int h);
	void SetFOV(double hfov);
private:
	void inline CalculateFOV();

	int m_Width = 256;
	int m_Height = 256;

	
	double m_HorizFOV = M_PI / 3;
	double m_VertFOV = M_PI / 3;
};