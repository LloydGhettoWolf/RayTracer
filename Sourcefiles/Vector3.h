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
		Vector3 operator/(const float rhs)const;

		//compund arithmetic ops
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3& operator*=(const Vector3& rhs);
		Vector3& operator/=(const Vector3& rhs);

		//unary operator
		//Vector3 operator-();

		float    Length()const;
		//Vector3  Project(const Vector3& otherVector)const;
	private:

#if defined(USE_INTRINSICS)
		__m128 m_elems;
#else
		float m_elems[3];
#endif
};

//unary operator
Vector3 operator-(const Vector3& vec);

//vector specific ops
float    DotProduct(const Vector3& lhs,const Vector3& rhs);
Vector3  CrossProduct(const Vector3& lhs,const Vector3& rhs);
Vector3  Project(const Vector3& vec1,const Vector3& vec2);
Vector3  Normalize(const Vector3& vec);
Vector3  operator*(float scalar,const Vector3& vec);
Vector3  operator*(const Vector3& vec,float scalar);
ostream& operator<<(ostream& os,const Vector3& vec);

#endif