#pragma once
#include "types.h"
#include "objects/object.h"

Vec3 SpecularImportanceSample(const Vec3& exact, double n, double cosTheta);

Vec3 DiffuseImportanceSample(Vec3 normal);

Vec3 PointInUnitSphere();