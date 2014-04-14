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

		inline Ray GetRayForPixel(int x,int y,float ratio)const;

		const Vector3& GetOrigin()const {return m_position;}

	private:
		Vector3 m_position;
		Vector3 m_lookVector, m_rightVector,m_upVector;
		float m_fov,m_distance;
};

Ray Camera::GetRayForPixel(int x,int y,float ratio)const
{
	//assert(x >= 0 && y >= 0 && "x or y are less than 0!");
	//assert(x < imgSize && y < imgSize && "x or y are bigger than image size!");

	Vector3 pixelDir = m_distance * m_lookVector + (0.5f - (float)y * ratio) * m_upVector +
		             ((float)x * ratio - 0.5f) * m_rightVector;

	//Vector3 pixelDir = Vector3((float)x,(float)y,0.0f) - m_position;
	//pixelDir = Normalize(pixelDir);


	return Ray(pixelDir,m_position);
}

#endif