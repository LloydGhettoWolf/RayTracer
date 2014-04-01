//SceneObject.cpp	
#include "SceneObject.h"

float			SceneObject::GetIntersection(const Ray& ray)
{
	switch(m_type)
	{
		case SPHERETYPE:
			return GetSphereIntersection(ray);
			break;
		case PLANETYPE:
			return GetPlaneIntersection(ray);
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
	return vec.Normalize();
}

float			SceneObject::GetPlaneIntersection(const Ray& ray)
{
	float val1 = -(ray.GetOrigin().DotProduct(m_normalOrPosition) + m_radiusOrDistance);
	float val2 = ray.GetDirection().DotProduct(m_normalOrPosition);
	float tVal = val1/val2;
	return tVal  > 0.0f ? tVal : NO_INTERSECTION; 
}

float			SceneObject::GetSphereIntersection(const Ray& ray)
{
	const Vector3& origin = ray.GetOrigin();
	const Vector3& dir    = ray.GetDirection();

	float a = dir.DotProduct(dir);
	float b = 2.0f * (origin.DotProduct(dir) - dir.DotProduct(m_normalOrPosition));
	float c = origin.DotProduct(origin) + m_normalOrPosition.DotProduct(m_normalOrPosition) 
		    - 2.0f * origin.DotProduct(m_normalOrPosition) - (m_radiusOrDistance * m_radiusOrDistance);

	float discriminant = (b*b) - 4.0f * a * c;

	if(discriminant < 0.0f) return NO_INTERSECTION;

	discriminant = sqrt(discriminant);

	float t1 = (-b + discriminant) / (2.0f * a);
	float t2 = (-b - discriminant) / (2.0f * a);

	return t1 < t2 ?  t1 : t2;
}