#pragma once
#include <utility>
//quadratic equation solver with catastrophic cancelation avoidance
//see https://math.stackexchange.com/questions/866331

bool solveQuadratic(const double& a, const double& b, const double& c, double& x0, double& x1);