#include "camera.h"
#include "glm/geometric.hpp"

Camera::Camera()
{
}
Camera::Camera(const Vec3& pos, const Vec3& dir, const Vec3& up)
	: m_Position(pos), m_Dir(dir), m_Up(up)
{
	RecalculateVectors();
}

const Vec3& Camera::Position() const
{
	return m_Position;
}
void Camera::SetPosition(const Vec3& pos)
{
	m_Position = pos;
}
const Vec3& Camera::Dir() const
{
	return m_Dir;
}
void Camera::SetDir(const Vec3& dir)
{
	m_Dir = dir;
}
const Vec3& Camera::Up() const
{
	return m_Up;
}
void Camera::SetUp(const Vec3& up)
{
	m_Up = up;
}
const Vec3& Camera::Right() const
{
	return m_Right;
}

void Camera::LookAt(const Vec3& tgt)
{
	m_Dir = glm::normalize(tgt - m_Position);
	m_Right = glm::normalize(glm::cross(m_Dir, Vec3(0.0, 0.0, 1.0)));
	m_Up = glm::normalize(glm::cross(m_Right, m_Dir));
}

///The function considers the current position of the
///camera and the target point to calculate the
///other vectors accordingly to look at the point.
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

double Camera::NearPlane()
{
	return Camera::m_NearPlane;
}
double Camera::FarPlane()
{
	return Camera::m_FarPlane;
}

double Camera::m_NearPlane = c_Epsilon;
double Camera::m_FarPlane = 10000.0;