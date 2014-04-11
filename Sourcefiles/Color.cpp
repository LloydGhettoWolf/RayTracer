//Color.cpp - implementation of vector class
#include "Color.h"


Color::Color()
{
	m_elems[0] = m_elems[1] = m_elems[2] = 0.0f;
}

Color::Color(float a,float b, float c)
{
	m_elems[0] = a;
	m_elems[1] = b;
	m_elems[2] = c;
}

	
const float Color::operator[](int index) const
{

	//assert(index >= 0 && index <= 2 && "trying to access elem out of range");

	return m_elems[index];
}

float&	Color::operator[](int index)
{

	//assert(index >= 0 && index <= 2 && "trying to access elem out of range");

	return m_elems[index];
}

//arithmetic ops
Color Color::operator+(const Color& rhs)const
{
	Color newColor(m_elems[0] + rhs[0],m_elems[1] + rhs[1],m_elems[2] + rhs[2]);
	return newColor;
}

Color Color::operator-(const Color& rhs)const
{
	Color newColor(m_elems[0] - rhs[0],m_elems[1] - rhs[1],m_elems[2] - rhs[2]);
	return newColor;
}

Color Color::operator*(const Color& rhs)const
{
	Color newColor(m_elems[0] * rhs[0],m_elems[1] * rhs[1],m_elems[2] * rhs[2]);
	return newColor;
}

Color Color::operator/(const Color& rhs)const
{
	Color newColor(m_elems[0] / rhs[0],m_elems[1] / rhs[1],m_elems[2] / rhs[2]);
	return newColor;
}

Color Color::operator/(float rhs)
{
	Color newColor(m_elems[0] / rhs,m_elems[1] / rhs,m_elems[2] / rhs);
	return newColor;
}

//compund arithmetic ops
Color& Color::operator+=(const Color& rhs)
{
	*this = *this + rhs;
	return *this;
}

Color& Color::operator-=(const Color& rhs)
{
	*this = *this - rhs;
	return *this;
}

Color& Color::operator*=(const Color& rhs)
{
	*this = *this * rhs;
	return *this;
}

Color& Color::operator/=(const Color& rhs)
{
	*this = *this / rhs;
	return *this;
}

void Color::Clamp(float min,float max)
{
	if(m_elems[0] < min) m_elems[0] = min;
	if(m_elems[0] > max) m_elems[0] = max;
	if(m_elems[1] < min) m_elems[1] = min;
	if(m_elems[1] > max) m_elems[1] = max;
	if(m_elems[2] < min) m_elems[2] = min;
	if(m_elems[2] > max) m_elems[2] = max;

}


Color operator*(float scalar,const Color& col)
{
	return Color(scalar*col[0],scalar*col[1],scalar*col[2]);
}

Color operator*(const Color& col,float scalar)
{
	return scalar * col;
}

ostream& operator<<(ostream& os,const Color& vec)
{
	return os <<" x: "<< vec[0] <<" y: "<< vec[1] <<" z: "<<vec[2]; 
}

istream& operator>>(istream& is,Color& col)
{
	char input;

	is >> input;

	if(input == '[')
	{
		
		is >> col[0] >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		is >> col[1] >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		is >> col[2] >> input;

		if(input != ']')
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