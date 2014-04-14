//Camera.cpp
#include "Camera.h"


Camera::Camera(Vector3& position,Vector3& lookAt,Vector3& up,float fov):m_position(position),m_lookVector(lookAt-position),m_fov(fov)
{
	m_lookVector = Normalize(m_lookVector);

	m_rightVector = CrossProduct(m_lookVector,up);

	m_rightVector = Normalize(m_rightVector);

	m_upVector    = CrossProduct(m_rightVector,m_lookVector);

	m_upVector    = Normalize(m_upVector);


	m_fov = DEG_TO_RAD(m_fov);

	m_distance  = 0.5f/tan(m_fov/2.0f);

}

