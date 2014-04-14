//sceneobject.h
#ifndef _SCENE_OBJECT_H
#define _SCENE_OBJECT_H

#include "Color.h"
#include "Ray.h"

const float NO_INTERSECTION = 0.0f;

enum ShapeType {SPHERETYPE,PLANETYPE};

struct Material
{
	float specular;
	float diffuse;
	float reflection;
	float refraction;
};

istream& operator >>(istream& in,Material& mat);

class SceneObject
{
	public:
		SceneObject(ShapeType type,Vector3& norm_pos,float radius_dist,Color& col,Material& material):
		  m_surfaceColor(col),m_type(type),m_normalOrPosition(norm_pos),m_radiusOrDistance(radius_dist),m_material(material),
			  m_radiusSquared(radius_dist*radius_dist),m_normalDot(DotProduct(norm_pos,norm_pos)){};


		float			GetIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,float rayDirDot,float rayOriDot,
										float rayOriDirDot);
		const Vector3&  GetSurfaceNormal(const Vector3& point)const;
		const Color&	GetColor()const {return m_surfaceColor;}
		ShapeType       GetType()const {return m_type;}

		static void SetOriginDot(float dot){m_originDot = dot;}

		Material m_material;

	private:
		const Vector3&  GetSphereNormal(const Vector3& point)const;

		float			GetPlaneIntersection(const Vector3& rayOrigin,const Vector3& rayDirection);
		float			GetSphereIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,float rayDot,float rayOriDot,float rayOriDirDot);

		Color		m_surfaceColor;
		ShapeType	m_type;
		float		m_radiusOrDistance;
		Vector3     m_normalOrPosition;
		float       m_radiusSquared;
		float		m_normalDot;

		static float m_originDot;
};


#endif