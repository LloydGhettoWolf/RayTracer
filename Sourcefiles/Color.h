//color.h - a color class to be used like a vector except with clamping ops on the values between 1.0f and 0.0f

#ifndef _COLOR_H
#define _COLOR_H
#include "Includes.h"
using namespace std;

class Color
{
	public:
		Color();
		Color(float a,float b, float c);

		//accessors
		const float operator[](int index) const;
		float&	    operator[](int index);

		//arithmetic ops
		Color operator+(const Color& rhs)const;
		Color operator-(const Color& rhs)const;
		Color operator*(const Color& rhs)const;
		Color operator/(const Color& rhs)const;
		Color operator/(float rhs);

		//compund arithmetic ops
		Color& operator+=(const Color& rhs);
		Color& operator-=(const Color& rhs);
		Color& operator*=(const Color& rhs);
		Color& operator/=(const Color& rhs);

		//color specific op
		void Clamp(float min,float max);

	private:
		float m_elems[3];
};

Color operator*(float scalar,const Color& col);
Color operator*(const Color& col,float scalar);
ostream& operator<<(ostream& os,const Color& col);

#endif