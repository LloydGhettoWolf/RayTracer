//Camera.h
#ifndef _CAMERA_H
#define _CAMERA_H
#include "Ray.h"

#define PI 3.1415926

#define CONV_CONSTANT (2.0f*PI)/360.0f 

#define DEG_TO_RAD(x) CONV_CONSTANT * x

class Camera
{
	public:
		Camera(Vector3& position,Vector3& lookAt,Vector3& up,float fov = 60.0f);

		Ray GetRayForPixel(int x,int y,int imgSize)const;

	private:
		Vector3 m_position;
		Vector3 m_lookVector, m_rightVector,m_upVector;
		float m_fov,m_distance;
};

#endif