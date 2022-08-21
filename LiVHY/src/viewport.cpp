#include "pch.h"
#include "viewport.h"

/// @class Viewport
/// The class by default constructs a 256x256 image with
/// a pi/3 horizontal FOV.

Viewport::Viewport()
{
}

Viewport::Viewport(int w, int h, double fov) : m_Width(w), m_Height(h), m_HorizFOV(fov), m_Aspect(1.0 * w / h)
{
	CalculateFOV();
}

const int Viewport::Width() const
{
	return m_Width;
}
const int Viewport::Height() const
{
	return m_Height;
}

const double Viewport::HFOV() const
{
	return m_HorizFOV;
}
const double Viewport::VFOV() const
{
	return m_VertFOV;
}

const double Viewport::AspectRatio() const
{
	return m_Aspect;
}

void Viewport::Resize(int w, int h)
{
	m_Width = w;
	m_Height = h;
}

void Viewport::SetFOV(double hfov)
{
	m_HorizFOV = hfov;
	CalculateFOV();
}

void Viewport::CalculateFOV()
{

	m_VertFOV = 2.0 * atan(tan(m_HorizFOV / 2.0) * m_Height / m_Width);
}