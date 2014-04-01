//Vector3.h - a 3d vector to be used in 3d graphics or physics calculations
#ifndef _VECTOR3_H
#define _VECTOR3_H
#include "Includes.h"
using namespace std;

class Vector3
{
	public:
		Vector3();
		Vector3(float a,float b, float c);

		//accessors
		const float operator[](int index) const;
		float&	    operator[](int index);

		//arithmetic ops
		Vector3 operator+(const Vector3& rhs)const;
		Vector3 operator-(const Vector3& rhs)const;
		Vector3 operator*(const Vector3& rhs)const;
		Vector3 operator/(const Vector3& rhs)const;
		Vector3 operator/(float rhs);

		//compund arithmetic ops
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3& operator*=(const Vector3& rhs);
		Vector3& operator/=(const Vector3& rhs);

		//unary operator
		Vector3 operator-();

		//vector specific ops
		float    DotProduct(const Vector3& rhs)const;
		float    Length()const;
		Vector3  CrossProduct(const Vector3& rhs)const;
		Vector3  Normalize();
	private:
		float m_elems[3];
};

Vector3  operator*(float scalar,const Vector3& vec);
Vector3  operator*(const Vector3& vec,float scalar);
ostream& operator<<(ostream& os,const Vector3& vec);

#endif