//sceneobject.h
#ifndef _SCENE_OBJECT_H
#define _SCENE_OBJECT_H

#include "Color.h"
#include "Ray.h"

const float NO_INTERSECTION = -1;

class SceneObject
{
	public:
		SceneObject(Color& col):m_surfaceColor(col) {};

		virtual float			GetIntersection(const Ray& ray)const = 0;
		virtual const Vector3&	GetSurfaceNormal(const Vector3& point)const = 0;
			    const Color&	GetColor()const {return m_surfaceColor;}
	private:
		Color	m_surfaceColor;
		Vector3 m_normal;
};

#endif