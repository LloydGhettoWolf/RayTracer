//SceneObject.cpp	
#include "SceneObject.h"

float	SceneObject::GetIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,float rayDirDot,float rayOriDot,float rayDirOriDot)
{
	switch(m_type)
	{
		case SPHERETYPE:
			return GetSphereIntersection(rayOrigin,rayDirection,rayDirDot,rayOriDot,rayDirOriDot);
			break;
		case PLANETYPE:
			return GetPlaneIntersection(rayOrigin,rayDirection);
			break;
	}
}

const Vector3&  SceneObject::GetSurfaceNormal(const Vector3& point)const
{
	switch(m_type)
	{
		case SPHERETYPE:
			return GetSphereNormal(point);
			break;
		case PLANETYPE:
			return m_normalOrPosition;
			break;
	}
}


const Vector3&  SceneObject::GetSphereNormal(const Vector3& point)const
{
	Vector3 vec = point - m_normalOrPosition;
	//return point - m_normalOrPosition;
	return Normalize(vec);
}

float	SceneObject::GetPlaneIntersection(const Vector3& rayOrigin,const Vector3& rayDirection)
{
	float val1 = DotProduct(-rayOrigin,m_normalOrPosition) + m_radiusOrDistance;
	float val2 = DotProduct(rayDirection,m_normalOrPosition);
	float tVal = val1/val2;

	return tVal  > 0.0f ? tVal : NO_INTERSECTION; 
}

float	SceneObject::GetSphereIntersection(const Vector3& rayOrigin,const Vector3& rayDirection,float rayDirDot,float rayOrigDot,float rayOriDirDot)
{
	
	float b = 2.0f * (rayOriDirDot - DotProduct(rayDirection,m_normalOrPosition));
	float c = rayOrigDot + m_normalDot - 2.0f * DotProduct(rayOrigin,m_normalOrPosition)  - m_radiusSquared;

	
	//the value for a is raydirdot
	float discriminant = (b*b) - 4.0f * rayDirDot * c;

	if(discriminant < 0.0f) return NO_INTERSECTION;

	discriminant = sqrt(discriminant);

	if(-b+discriminant < 0.0f) return NO_INTERSECTION;

	float denom = 1.0f/(2.0f * rayDirDot);
	float t1 = (-b + discriminant) * denom;
	float t2 = (-b - discriminant) * denom;


	//if(t1 < t2 && t1 > 0.0f) return t1;

	//if(t2 < t1 && t2 > 0.0f) return t2;

	//return NO_INTERSECTION;

	return t1 < t2 ? t1 : t2; 

}
