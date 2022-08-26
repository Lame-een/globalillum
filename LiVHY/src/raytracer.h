#pragma once
#include "camera.h"
#include "viewport.h"
#include "util/image.h"
#include "scene.h"

void DirectIllumination(const Scene& scene, const HitInfo& hitInfo, RGB& color);

RGB CastRay(const Scene& scene, const Ray& ray, int depth = 0);

RGB TraceRay(const Scene& scene, const HitInfo& hitInfo, const Ray& ray, int depth = 0);

void RayTracer(const Viewport& vp, const Scene& scene);