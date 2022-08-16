#pragma once
#include "camera.h"
#include "viewport.h"
#include "util/image.h"
#include "scene.h"

void ComputeIllumination(const Scene& scene, const HitInfo& hitInfo, const Light* light, double cosTheta, RGB& color);

void DirectIllumination(const Scene& scene, const HitInfo& hitInfo, double cosTheta, RGB& color);

Vec3 ReflectiveBounce(Vec3 normal, const Vec3& view, double cosTheta);

Vec3 TransmissiveBounce(const HitInfo& hitInfo, double cosTheta);

void TransmissiveIllumination(const Scene& scene, const HitInfo& hitInfo, double cosTheta, double transCoeff, RGB& color);

void TraceRay(const Scene& scene, const Ray& ray, const HitInfo& hitInfo, RGB& color);

void RayTracer(const Camera& cam, const Viewport& vp, const Scene& scene);