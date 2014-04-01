//Sphere.cpp
#include "Sphere.h"

const Vector3& Sphere::GetSurfaceNormal(const Vector3& point)const
{
	Vector3 vec = point - m_position;
	return vec.Normalize();
}

float Sphere::GetIntersection(const Ray& ray)const
{
	const Vector3& origin = ray.GetOrigin();
	const Vector3& dir    = ray.GetDirection();

	float a = dir.DotProduct(dir);
	float b = 2.0f * (origin.DotProduct(dir) - dir.DotProduct(m_position));
	float c = origin.DotProduct(origin) + m_position.DotProduct(m_position) - 2.0f * origin.DotProduct(m_position) - (m_radius * m_radius);

	float discriminant = (b*b) - 4.0f * a * c;

	if(discriminant < 0.0f) return NO_INTERSECTION;

	discriminant = sqrt(discriminant);

	float t1 = (-b + discriminant) / (2.0f * a);
	float t2 = (-b - discriminant) / (2.0f * a);

	return t1 < t2 ?  t1 : t2;
}