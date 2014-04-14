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
		SceneObject(ShapeType type,Vector3& norm_pos,float radius_dist,Color& col,Material& material,const Vector3& rayOri):
		  m_surfaceColor(col),m_type(type),m_normalOrPosition(norm_pos),m_radiusOrDistance(radius_dist),m_material(material),
		  m_radiusSquared(radius_dist*radius_dist),m_normalDot(DotProduct(norm_pos,norm_pos)),
		  m_rayOriNormalDot(DotProduct(rayOri,norm_pos)){};


		float			GetIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,float rayDirDot,float rayOriDot,
										float rayOriDirDot,bool primary = false);
		const Vector3&  GetSurfaceNormal(const Vector3& point)const;
		const Color&	GetColor()const {return m_surfaceColor;}
		ShapeType       GetType()const {return m_type;}


		Material m_material;

	private:
		const Vector3&  GetSphereNormal(const Vector3& point)const;

		float			GetPlaneIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,bool primary);
		float			GetSphereIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,float rayDot,
			                                  float rayOriDot,float rayOriDirDot,bool primary);

		Color		m_surfaceColor;
		ShapeType	m_type;
		float		m_radiusOrDistance;
		Vector3     m_normalOrPosition;
		float       m_radiusSquared;
		float		m_normalDot;
		float       m_rayOriNormalDot;

};


#endif