//Scene.h
#ifndef _SCENE_H
#define _SCENE_H
#include "Includes.h"
#include "Light.h"
#include "SceneObject.h"
#include "Camera.h"

typedef vector<SceneObject*>::iterator shapeItr;
typedef vector<Light*>::iterator lightItr;

class Scene
{
	public:
		Scene(){};

		~Scene()
		{
			
		}

		void  AddLight(Light* newLight)			{m_lights.push_back(newLight);}
		void  AddObject(SceneObject* newObject)	{m_objects.push_back(newObject);}
		Color TraceRay(const Ray& ray) const;

		void Render(const Camera& cam,ofstream& outStream,int imgSize);


	private:
		Color GenerateColor(const Vector3& point,const SceneObject* obj)const;

		std::vector<Light*>			m_lights;
		std::vector<SceneObject*>	m_objects;
};


#endif