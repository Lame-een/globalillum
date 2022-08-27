#pragma once
#include <thread>

inline const unsigned int c_ThreadCount = std::thread::hardware_concurrency();

//inline unecessary for constexpr
constexpr unsigned int c_MaxRaytracerDepth = 5;
constexpr unsigned int c_Samples = 10;
constexpr unsigned int c_LightSampleNum = 2;

constexpr unsigned int c_MaxMonteCarloDepth = 100;
constexpr unsigned int c_MaxPhotonDepth = 100;

constexpr double c_RayAbsorptionProbability = 0.01;

constexpr unsigned int c_GlobalPhotonCount = 2048;
constexpr unsigned int c_CausticPhotonCount = 16384;
