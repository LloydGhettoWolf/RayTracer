//Ray.h - 
#ifndef _RAY_H
#define _RAY_H

#include "Vector3.h"

class Ray
{
	public:
		Ray(const Vector3& dir,const Vector3& ori):m_direction(dir),m_origin(ori){ };

		const Vector3& GetDirection()const {return m_direction;} 
		const Vector3& GetOrigin()const {return m_origin;}
	private:
		Vector3 m_direction,m_origin;
};

#endif
