#pragma once
#include "camera.h"
#include "viewport.h"
#include "util/image.h"
#include "scene.h"
#include "pdf.h"

RGB traceRay(const Scene& scene, const Ray& ray, int depth = 0);

void rayTracer(const Viewport& vp, const Scene& scene);