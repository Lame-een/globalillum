#pragma once
#include "camera.h"
#include "viewport.h"
#include "util/image.h"
#include "scene.h"

void ComputeIllumination(const Scene& scene, const HitInfo& hitInfo, const Light* light, double cosTheta, RGB& color);

void DirectIllumination(const Scene& scene, const HitInfo& hitInfo, double cosTheta, RGB& color);
//void IndirectIllumination();

void TraceRay(const Scene& scene, const Ray& ray, const HitInfo& hitInfo, RGB& color);

void RayTracer(const Camera& cam, const Viewport& vp, const Scene& scene);