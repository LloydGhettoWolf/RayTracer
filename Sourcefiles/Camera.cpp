//Camera.cpp
#include "Camera.h"


Camera::Camera(Vector3& position,Vector3& lookAt,Vector3& up,float fov):m_position(position),m_lookVector(lookAt-position),m_fov(fov)
{
	m_lookVector = m_lookVector.Normalize();

	m_rightVector = m_lookVector.CrossProduct(up);

	m_rightVector = m_rightVector.Normalize();

	m_upVector    = m_rightVector.CrossProduct(m_lookVector);

	m_upVector    = m_upVector.Normalize();

	m_fov = DEG_TO_RAD(m_fov);

	m_distance  = 0.5f/tan(m_fov/2.0f);

}

Ray Camera::GetRayForPixel(int x,int y,int imgSize)const
{
	assert(x >= 0 && y >= 0 && "x or y are less than 0!");
	assert(x < imgSize && y < imgSize && "x or y are bigger than image size!");

	Vector3 pixelDir = m_distance * m_lookVector + (0.5f - (float)y/(float)(imgSize-1)) * m_upVector +
		               ((float)x/(float)(imgSize-1) - 0.5f) * m_rightVector;

	return Ray(pixelDir,m_position);
}