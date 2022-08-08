#pragma once
#include "util/types.h"
#include "util/ray.h"
#include "BRDF.h"
#include "hittable.h"

class Object : public Hittable
{
public:
	Object();
	Object(BRDF* brdf);

	BRDF* Brdf() const;
protected:
	BRDF* m_Brdf = nullptr;
};