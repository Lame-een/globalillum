#pragma once
#include "types.h"
#include "objects/object.h"

inline int c_MaxRaytracerDepth = 3;
inline int c_Samples = 10;
inline int c_LightSampleNum = 5;

Vec3 SpecularImportanceSample(const Vec3& exact, double n, double cosTheta);

Vec3 DiffuseImportanceSample(Vec3 normal);