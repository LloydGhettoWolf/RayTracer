//sceneobject.h
#ifndef _SCENE_OBJECT_H
#define _SCENE_OBJECT_H

#include "Color.h"
#include "Ray.h"

const float NO_INTERSECTION = 0.0f;

enum ShapeType {SPHERETYPE,PLANETYPE};

class Material
{
public:

	Material(float spec,float diff,float reflect,float refract):m_specular(spec),m_diffuse(diff),m_reflection(reflect),
																m_refraction(refract){};

	float m_specular;
	float m_diffuse;
	float m_reflection;
	float m_refraction;
};



class SceneObject
{
	public:
		SceneObject(ShapeType type,Vector3& norm_pos,float radius_dist,Color& col,int matIndex):
		  m_surfaceColor(col),m_type(type),m_normalOrPosition(norm_pos),m_radiusOrDistance(radius_dist),m_matIndex(matIndex),
			  m_radiusSquared(radius_dist*radius_dist),m_normalDot(DotProduct(norm_pos,norm_pos)){};


		float			GetIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,float rayDirDot,float rayOriDot,
										float rayOriDirDot);
		const Vector3&  GetSurfaceNormal(const Vector3& point)const;
		const Color&	GetColor()const {return m_surfaceColor;}
		ShapeType       GetType()const {return m_type;}
		int				m_matIndex;

	private:
		const Vector3&  GetSphereNormal(const Vector3& point)const;

		float			GetPlaneIntersection(const Vector3& rayOrigin,const Vector3& rayDirection);
		float			GetSphereIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,float rayDot,
			                                  float rayOriDot,float rayOriDirDot);

		Color		m_surfaceColor;
		Vector3     m_normalOrPosition;
		float		m_radiusOrDistance;
		float       m_radiusSquared;
		float		m_normalDot;
		ShapeType	m_type;
		
};


#endif