//Scene.h
#ifndef _SCENE_H
#define _SCENE_H
#include "Includes.h"
#include "Light.h"
#include "SceneObject.h"
#include "Camera.h"

struct rgbColorVal
{
	char r,g,b;
};

class Scene
{
	public:
		Scene(int imgSize):m_numLights(0),m_numObjects(0){ m_SceneMem = new rgbColorVal[imgSize*imgSize];}
		~Scene(){delete [] m_SceneMem;}

		void  AddLight(Light* newLight);
		void  AddObject(SceneObject* newObject);
		Color TraceRay(const Ray& ray,int depth = 0,int currentShape = -1) const;


		void Render(const Camera& cam,int xStart,int xEnd,int yStart,int yEnd,int imgSize);
		void Scene::WriteToTGAFile(ofstream& outFile,int imgSize);


	private:

		Color GenerateColor(const Vector3& point,const SceneObject* obj,const Vector3& normal)const;

		Light*			m_lights[10];
		SceneObject*	m_sceneObjects[10];

		rgbColorVal*    m_SceneMem;

		int				m_numLights;
		int				m_numObjects;
};


#endif