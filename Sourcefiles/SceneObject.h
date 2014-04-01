//sceneobject.h
#ifndef _SCENE_OBJECT_H
#define _SCENE_OBJECT_H

#include "Color.h"
#include "Ray.h"

const float NO_INTERSECTION = -1;

enum ShapeType {SPHERETYPE,PLANETYPE};


class SceneObject
{
	public:
		SceneObject(Color& col,ShapeType type,Vector3& norm_pos,float radius_dist):m_surfaceColor(col),m_type(type),m_normalOrPosition(norm_pos),
																 m_radiusOrDistance(radius_dist){};

		float			GetIntersection(const Ray& ray);
		const Vector3&  GetSurfaceNormal(const Vector3& point)const;
		const Color&	GetColor()const {return m_surfaceColor;}
	private:
		const Vector3&  GetSphereNormal(const Vector3& point)const;

		float			GetPlaneIntersection(const Ray& ray);
		float			GetSphereIntersection(const Ray& ray);

		Color		m_surfaceColor;
		ShapeType	m_type;
		float		m_radiusOrDistance;
		Vector3     m_normalOrPosition;
};

#endif