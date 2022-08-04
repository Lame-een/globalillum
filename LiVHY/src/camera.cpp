#include "camera.h"

#include "glm/geometric.hpp"

Camera::Camera()
{
}
Camera::Camera(Vec3 pos, Vec3 dir, Vec3 up)
	: m_Position(pos), m_Dir(dir), m_Up(up)
{
	RecalculateVectors();
}

const Vec3 Camera::Position() const
{
	return m_Position;
}
const Vec3 Camera::Dir() const
{
	return m_Dir;
}
const Vec3 Camera::Up() const
{
	return m_Up;
}
const Vec3 Camera::Right() const
{
	return m_Right;
}

void Camera::LookAt(Vec3 tgt)
{
	m_Dir = glm::normalize(tgt - m_Position);
	m_Right = glm::normalize(glm::cross(m_Dir, Vec3(0.0, 0.0, 1.0)));
	m_Up = glm::normalize(glm::cross(m_Right, m_Dir));
}

void Camera::RecalculateVectors()
{
	m_Dir = glm::normalize(m_Dir);
	m_Up = glm::normalize(m_Up);
	m_Right = glm::normalize(glm::cross(m_Dir, m_Up));
}


void Camera::SetPlanes(double nearPlane, double farPlane)
{
	m_NearPlane = nearPlane;
	m_FarPlane = farPlane;
}

const double Camera::NearPlane()
{
	return Camera::m_NearPlane;
}
const double Camera::FarPlane()
{
	return Camera::m_FarPlane;
}

double Camera::m_NearPlane = 0.00001;
double Camera::m_FarPlane = 10000.0;
