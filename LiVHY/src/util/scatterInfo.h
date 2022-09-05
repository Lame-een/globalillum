#pragma once
#include "colors.h"
#include "ray.h"

class PDF;

class ScatterInfo
{
public:
	~ScatterInfo()
	{
		delete m_pdf;
	}

	Ray bounceRay;
	bool isSpecular;
	RGB color;

	const PDF* Pdf() const
	{
		return m_pdf;
	}
	void SetPdf(PDF* ptr) //deletes the set pointer
	{
		delete m_pdf;
		m_pdf = ptr;
	}
private:
	const PDF* m_pdf = nullptr;
};