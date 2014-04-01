//Plane.h
#ifndef _PLANE_H
#define _PLANE_H
#include "SceneObject.h"


class Plane : SceneObject
{
	public:
		Plane(Vector3& norm,float dist,Color& color): SceneObject(color),m_normal(norm),m_distance(dist){};

		float		   GetDistance() const{return m_distance;}
		const Vector3& GetNormal() const{return m_normal;}
		const Vector3& GetSurfaceNormal(const Vector3& point) const {return m_normal;}

		float          GetIntersection(const Ray& ray) const
		{
			float val1 = -(ray.GetOrigin().DotProduct(m_normal) + m_distance);
			float val2 = ray.GetDirection().DotProduct(m_normal);
			float tVal = val1/val2;
			return tVal  > 0.0f ? tVal : NO_INTERSECTION; 
		}

	private:
		float   m_distance;
		Vector3 m_normal;
};

#endif