//Camera.h
#ifndef _CAMERA_H
#define _CAMERA_H
#include "Ray.h"

#define PI 3.1415926f

#define CONV_CONSTANT (2.0f*PI)/360.0f 

#define DEG_TO_RAD(x) CONV_CONSTANT * x

class Camera
{
	public:
		Camera(Vector3& position,Vector3& lookAt,Vector3& up,float fov = 60.0f);

		inline Ray GetRayForPixel(float x,float y,float ratio)const;

		const Vector3& GetOrigin()const {return m_position;}

		const Vector3& GetLook()const {return m_lookVector;}

	private:
		Vector3 m_position;
		Vector3 m_lookVector, m_rightVector,m_upVector;
		float m_fov,m_distance;
};

Ray Camera::GetRayForPixel(float x,float y,float ratio)const
{

	Vector3 pixelDir = m_distance * m_lookVector + (0.5f - y * ratio) * m_upVector +
		             (x * ratio - 0.5f) * m_rightVector;


	return Ray(pixelDir,m_position);
}

#endif