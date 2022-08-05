#pragma once
#include "util/types.h"
#include <cmath>

class Camera
{
public:
	Camera();
	Camera(const Vec3& pos, const Vec3& dir, const Vec3& up);

	const Vec3& Position() const;
	const Vec3& Dir() const;
	const Vec3& Up() const;
	const Vec3& Right() const;
			  
	void LookAt(const Vec3& tgt);
private:
	void RecalculateVectors();

	Vec3 m_Position = Vec3(0.0, 0.0, 0.0);
	Vec3 m_Dir = Vec3(0.0, 1.0, 0.0);
	Vec3 m_Up = Vec3(0.0, 0.0, 1.0);
	Vec3 m_Right = Vec3(1.0, 0.0, 0.0);

public:
	static void SetPlanes(double nearPlane, double farPlane);
	static const double NearPlane();
	static const double FarPlane();

private:
	static double m_NearPlane;
	static double m_FarPlane;
};