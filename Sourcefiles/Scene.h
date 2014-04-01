//Scene.h
#ifndef _SCENE_H
#define _SCENE_H
#include "Includes.h"
#include "Light.h"
#include "SceneObject.h"
#include "Camera.h"


class Scene
{
	public:
		Scene():m_numLights(0),m_numObjects(0){};


		void  AddLight(Light* newLight);
		void  AddObject(SceneObject* newObject);
		Color TraceRay(const Ray& ray) const;

		void Render(const Camera& cam,ofstream& outStream,int imgSize);


	private:
		Color GenerateColor(const Vector3& point,const SceneObject* obj)const;

		Light*			m_lights[10];
		SceneObject*	m_sceneObjects[10];

		int				m_numLights;
		int				m_numObjects;
};


#endif