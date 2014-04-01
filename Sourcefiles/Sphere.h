//Sphere.h
#ifndef _SPHERE_H
#define _SPHERE_H
#include "SceneObject.h"

class Sphere : SceneObject
{
	public:
		Sphere(float radius,Vector3& position,Color& color): SceneObject(color),m_radius(radius),m_position(position){};

		float			GetRadius() const{return m_radius;}
		const Vector3&	GetPosition() const{return m_position;}

		const Vector3& GetSurfaceNormal(const Vector3& point)const;

		float GetIntersection(const Ray& ray)const;
	private:
		float   m_radius;
		Vector3 m_position;
};

#endif