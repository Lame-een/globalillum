#include "pch.h"
#include "object.h"

Object::Object() {}

Object::Object(const BRDF* brdf)
	: m_Brdf(brdf)
{
}

const BRDF* Object::Brdf() const
{
	return m_Brdf;
}