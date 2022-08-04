#include "viewport.h"
Viewport::Viewport()
{
}

Viewport::Viewport(int w, int h, float fov) : m_Width(w), m_Height(h), m_HorizFOV(fov)
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
	return m_Width;
}
const float Viewport::VFOV() const
{
	return m_Height;
}

void Viewport::Resize(int w, int h)
{
	m_Width = w;
	m_Height = h;
}

void Viewport::SetFOV(float hfov){
	m_HorizFOV = hfov;
	CalculateFOV();
}

void Viewport::CalculateFOV(){
	
	m_VertFOV = 2.0f * atanf(tanf(m_HorizFOV/2.0f) * m_Height/m_Width);
}