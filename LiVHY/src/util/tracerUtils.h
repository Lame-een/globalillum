#pragma once
#include "types.h"
#include "objects/object.h"

inline int c_MaxRaytracerDepth = 2;
inline int c_Samples = 640;
inline int c_DiffuseSampleNum = 4;
inline int c_TransmissiveSampleNum = 4;
inline int c_SpecularSampleNum = 4;

Vec3 SpecularImportanceSample(const Vec3& exact, double n, double cosTheta);

Vec3 DiffuseImportanceSample(Vec3 normal);