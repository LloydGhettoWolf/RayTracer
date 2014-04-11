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
	return Normalize(vec);
}

float			SceneObject::GetPlaneIntersection(const Ray& ray)
{

	float val1 = DotProduct(-ray.GetOrigin(),m_normalOrPosition) + m_radiusOrDistance;
	float val2 = DotProduct(ray.GetDirection(),m_normalOrPosition);
	float tVal = val1/val2;

	return tVal  > 0.0f ? tVal : NO_INTERSECTION; 
}

float			SceneObject::GetSphereIntersection(const Ray& ray)
{
	const Vector3& origin = ray.GetOrigin();
	const Vector3& dir    = ray.GetDirection();


	//early out test - if the center projected on the ray is bigger than the radius then opt out
	//float d = origin.DotProduct(m_normalOrPosition);

	//if(d < m_radiusOrDistance) return NO_INTERSECTION;

	float a = DotProduct(dir,dir);
	float b = 2.0f * (DotProduct(origin,dir) - DotProduct(dir,m_normalOrPosition));
	float c = DotProduct(origin,origin) + DotProduct(m_normalOrPosition,m_normalOrPosition) 
		    - 2.0f * DotProduct(origin,m_normalOrPosition) - (m_radiusOrDistance * m_radiusOrDistance);


	float discriminant = (b*b) - 4.0f * a * c;

	if(discriminant < 0.0f) return NO_INTERSECTION;

	discriminant = sqrt(discriminant);

	float t1 = (-b + discriminant) / (2.0f * a);
	float t2 = (-b - discriminant) / (2.0f * a);


	if(t1 < t2 && t1 > 0.0f) return t1;

	if(t2 < t1 && t2 > 0.0f) return t2;

	return NO_INTERSECTION;

}

istream& operator >>(istream& is,Material& mat)
{
	char input;

	is >> input;

	if(input == '(')
	{
		
		is >> mat.diffuse >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		is >> mat.reflection >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		is >> mat.refraction >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		is >> mat.specular >> input;

		if(input != ')')
		{
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else
	{
		is.clear(ios_base::failbit);
		return is;
	}

	return is;
}