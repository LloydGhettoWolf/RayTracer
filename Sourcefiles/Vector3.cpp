//Vector3.cpp - implementation of vector class
#include "Vector3.h"


Vector3::Vector3()
{
	m_elems[0] = m_elems[1] = m_elems[2] = 0.0f;
}

Vector3::Vector3(float a,float b, float c)
{
	m_elems[0] = a;
	m_elems[1] = b;
	m_elems[2] = c;
}

	
const float Vector3::operator[](int index) const
{
	assert(index >= 0 && index <= 2 && "trying to access elem out of range");
	return m_elems[index];
}

float&	    Vector3::operator[](int index)
{
	assert(index >= 0 && index <= 2 && "trying to access elem out of range");
	return m_elems[index];
}

//arithmetic ops
Vector3 Vector3::operator+(const Vector3& rhs)const
{
	return Vector3(m_elems[0] + rhs[0],m_elems[1] + rhs[1],m_elems[2] + rhs[2]);
}

Vector3 Vector3::operator-(const Vector3& rhs)const
{
	return Vector3(m_elems[0] - rhs[0],m_elems[1] - rhs[1],m_elems[2] - rhs[2]);
}

Vector3 Vector3::operator*(const Vector3& rhs)const
{
	return Vector3(m_elems[0] * rhs[0],m_elems[1] * rhs[1],m_elems[2] * rhs[2]);
}

Vector3 Vector3::operator/(const Vector3& rhs)const
{
	return Vector3(m_elems[0] / rhs[0],m_elems[1] / rhs[1],m_elems[2] / rhs[2]);
}

Vector3 Vector3::operator/(float rhs)
{
	return Vector3(m_elems[0] / rhs,m_elems[1] / rhs,m_elems[2] / rhs);
}

//compund arithmetic ops
Vector3& Vector3::operator+=(const Vector3& rhs)
{
	*this = *this + rhs;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	*this = *this - rhs;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& rhs)
{
	*this = *this * rhs;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& rhs)
{
	*this = *this / rhs;
	return *this;
}

Vector3 Vector3::operator-()
{
	return Vector3(-m_elems[0],-m_elems[1],-m_elems[2]);
}

//vector specific ops
float    Vector3::DotProduct(const Vector3& rhs)const
{
	return m_elems[0] * rhs[0] + m_elems[1] * rhs[1] + m_elems[2] * rhs[2];
}

float    Vector3::Length() const
{
	return sqrt((*this).DotProduct(*this));
}

Vector3  Vector3::CrossProduct(const Vector3& rhs)const
{
	float elem1 = m_elems[1] * rhs[2] - m_elems[2] * rhs[1];
	float elem2 = -(m_elems[0] * rhs[2] - m_elems[2] * rhs[0]);
	float elem3 = m_elems[0] * rhs[1] - m_elems[1] * rhs[0];

	return Vector3(elem1,elem2,elem3);
}

Vector3  Vector3::Normalize()
{
	float length = (*this).Length();
	return *this / length;
}

Vector3 operator*(float scalar,const Vector3& vec)
{
	return Vector3(scalar*vec[0],scalar*vec[1],scalar*vec[2]);
}

Vector3 operator*(const Vector3& vec,float scalar)
{
	return scalar * vec;
}

ostream& operator<<(ostream& os,const Vector3& vec)
{
	return os <<" x: "<< vec[0] <<" y: "<< vec[1] <<" z: "<<vec[2]; 
}