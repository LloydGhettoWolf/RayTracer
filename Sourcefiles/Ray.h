//Ray.h - 
#ifndef _RAY_H
#define _RAY_H

#include "Vector3.h"

class Ray
{
	public:
		Ray(const Vector3& dir,const Vector3& ori,bool normalizeDirection = true):m_direction(dir),m_origin(ori)
		{
			if(normalizeDirection)
			{
				m_direction = m_direction.Normalize();
			}
		}

		const Vector3& GetDirection()const {return m_direction;} 
		const Vector3& GetOrigin()const {return m_origin;}
	private:
		Vector3 m_origin, m_direction;
};

#endif
