//Light.h
#ifndef _LIGHT_H
#define _LIGHT_H
#include "Vector3.h"
#include "Color.h"

class Light
{
	public:
		Light(Color& color,Vector3& position):m_color(color),m_position(position) {};

		const Color&   GetColor()const{return m_color;}
		const Vector3& GetPosition()const{return m_position;}

	private:
		Color   m_color;
		Vector3 m_position;
};

#endif