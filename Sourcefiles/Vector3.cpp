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

	//assert(index >= 0 && index <= 2 && "trying to access elem out of range");
	return m_elems[index];
}

float&	    Vector3::operator[](int index)
{
	//assert(index >= 0 && index <= 2 && "trying to access elem out of range");
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


Vector3 Vector3::operator/(const float rhs)const
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



float    Vector3::Length() const
{
	return sqrt(DotProduct(*this,*this));
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

istream& operator>>(istream& is,Vector3& vec)
{
	char input;

	is >> input;

	if(input == '(')
	{
		
		is >> vec[0] >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		is >> vec[1] >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		is >> vec[2] >> input;

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

Vector3 operator-(const Vector3& vec)
{
	return Vector3(-vec[0],-vec[1],-vec[2]);
}


Vector3  Normalize(const Vector3& vec)
{	
	Vector3 newVec = vec/vec.Length();
	assert(newVec.Length() > 0.99f && newVec.Length() < 1.01f && "normalization function is wrong!");
	return newVec;
}

Vector3  CrossProduct(const Vector3& lhs,const Vector3& rhs)
{
	float elem1 = lhs[1] * rhs[2] - lhs[2] * rhs[1];
	float elem2 = -(lhs[0] * rhs[2] - lhs[2] * rhs[0]);
	float elem3 = lhs[0] * rhs[1] - lhs[1] * rhs[0];

	Vector3 newVec = Vector3(elem1,elem2,elem3);

	assert(DotProduct(newVec,lhs) > -0.01f && DotProduct(newVec,lhs) < 0.01f && "normalization function is wrong!");

	return newVec;
}


float   DotProduct(const Vector3& lhs,const Vector3& rhs)
{
	return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];

}