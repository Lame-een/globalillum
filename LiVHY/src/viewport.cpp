#include "pch.h"
#include "viewport.h"

/// @class Viewport
/// The class by default constructs a 256x256 image with
/// a pi/3 horizontal FOV.

Viewport::Viewport()
	: m_Width(Settings::imgWidth), m_Height(Settings::imgHeight), m_HorizFOV(Settings::fov), m_Aspect(1.0f * m_Width / m_Height)
{
}

Viewport::Viewport(int w, int h, float fov) 
	: m_Width(w), m_Height(h), m_HorizFOV(fov), m_Aspect(1.0f * w / h)
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

const float Viewport::HFOV() const
{
	return m_HorizFOV;
}
const float Viewport::VFOV() const
{
	return m_VertFOV;
}

const float Viewport::AspectRatio() const
{
	return m_Aspect;
}

void Viewport::Resize(int w, int h)
{
	m_Width = w;
	m_Height = h;
}

void Viewport::SetFOV(float hfov)
{
	m_HorizFOV = hfov;
	CalculateFOV();
}

void Viewport::CalculateFOV()
{

	m_VertFOV = 2.0f * atan(tan(m_HorizFOV / 2.0f) * m_Height / m_Width);
}