#include "camera.h"

#include "glm/geometric.hpp"

Camera::Camera()
{
}
Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
	: m_Position(pos), m_Dir(dir), m_Up(up)
{
	RecalculateVectors();
}

const glm::vec3 Camera::Position() const
{
	return m_Position;
}
const glm::vec3 Camera::Dir() const
{
	return m_Dir;
}
const glm::vec3 Camera::Up() const
{
	return m_Up;
}
const glm::vec3 Camera::Right() const
{
	return m_Right;
}

void Camera::LookAt(glm::vec3 tgt)
{
	m_Dir = glm::normalize(tgt - m_Position);
	m_Right = glm::normalize(glm::cross(m_Dir, glm::vec3(0.0f, 0.0f, 1.0f)));
	m_Up = glm::normalize(glm::cross(m_Right, m_Dir));
}

void Camera::RecalculateVectors()
{
	m_Dir = glm::normalize(m_Dir);
	m_Up = glm::normalize(m_Up);
	m_Right = glm::normalize(glm::cross(m_Dir, m_Up));
}


void Camera::SetPlanes(float nearPlane, float farPlane)
{
	m_NearPlane = nearPlane;
	m_FarPlane = farPlane;
}

const float Camera::NearPlane()
{
	return Camera::m_NearPlane;
}
const float Camera::FarPlane()
{
	return Camera::m_FarPlane;
}

float Camera::m_NearPlane = 0.00001f;
float Camera::m_FarPlane = 10000.0f;
