#pragma once
#include "camera.h"
#include "viewport.h"
#include "util/image.h"
#include "scene.h"
#include "pdf.h"

RGB TraceRay(const Scene& scene, const Ray& ray, int depth = 0);

void RayTracer(const Viewport& vp, const Scene& scene);