#include "object.h"

Object::Object(BRDF* brdf)
	: m_Brdf(brdf)
{
}

BRDF* Object::Brdf() const
{
	return m_Brdf;
}