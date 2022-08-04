#pragma once
#include "glm/vec3.hpp"
#include <cmath>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);

	const glm::vec3 Position() const;
	const glm::vec3 Dir() const;
	const glm::vec3 Up() const;
	const glm::vec3 Right() const;

	void LookAt(glm::vec3 tgt);
private:
	void RecalculateVectors();

	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Dir = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);

public:
	static void SetPlanes(float nearPlane, float farPlane);
	static const float NearPlane();
	static const float FarPlane();

private:
	static float m_NearPlane;
	static float m_FarPlane;
};