///@file camera.h
#pragma once
#include <cmath>
#include "util/types.h"
#include "util/math.h"


///@class Camera
class Camera
{
public:
	///@brief Constructs a camera at the world origin.
	Camera();
	///@brief Constructs a camera at position, with direction
	///		  and an up vector.
	///@param[in] pos Position of the camera.
	///@param[in] dir Direction the camera is facing.
	///@param[in] up The up vector of the camera.
	Camera(const Vec3& pos, const Vec3& dir, const Vec3& up);

	const Vec3& Position() const;
	void SetPosition(const Vec3& pos);

	const Vec3& Dir() const;
	void SetDir(const Vec3& dir);

	const Vec3& Up() const;
	void SetUp(const Vec3& up);

	const Vec3& Right() const;
			  
	///@brief The function recalculates the view vectors
	///		   to target a specific point in space
	///@param[in] tgt Point to look at.
	void LookAt(const Vec3& tgt);
private:
	void RecalculateVectors();

	Vec3 m_Position = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 m_Dir = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 m_Up = Vec3(0.0f, 0.0f, 1.0f);
	Vec3 m_Right = Vec3(1.0f, 0.0f, 0.0f);

public:
	///@brief Set the clipping planes of the cammera
	///@param[in] nearPlane The minimum distance at which the 
	///@param[in] farPlane
	static void SetPlanes(float nearPlane, float farPlane);

	static float NearPlane();
	static float FarPlane();

private:
	static float m_NearPlane;
	static float m_FarPlane;
};