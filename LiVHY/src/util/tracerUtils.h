#pragma once
#include "types.h"
#include "objects/object.h"

Vec3 TransmissiveRefract(const HitInfo& hitInfo);

Vec3 SpecularSample(const Vec3& exact, double n, double cosTheta);

Vec3 DiffuseSample(Vec3 normal);

Vec3 PointInUnitSphere();