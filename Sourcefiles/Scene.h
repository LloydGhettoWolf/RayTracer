//Scene.h
#ifndef _SCENE_H
#define _SCENE_H
#include "Includes.h"
#include "Light.h"
#include "SceneObject.h"
#include "Camera.h"

const int MAX_SHAPES = 30;
const int MAX_LIGHTS = 5;

struct rgbColorVal
{
	char r,g,b;
};

class Scene
{
	public:
		Scene():m_numLights(0),m_numObjects(0),m_camera(NULL),m_depthSet(false),m_imgSizeSet(false){ };
		~Scene();

		void  SetImageSize(int imgSize);
		void  SetDepth(int depth) {m_depth =depth; m_depthSet = true;}
		void  AddLight(Light* newLight);
		void  AddObject(SceneObject* newObject);
		void  AddCamera(Camera* cam) {m_camera = cam;}
		Color TraceRay(const Ray& ray,int depth = 0,int currentShape = -1) const;


		void Render(int xStart,int xEnd,int yStart,int yEnd,int imgSize,int depth);
		void Scene::WriteToTGAFile(ofstream& outFile,int imgSize);

		bool HasCamera()const {return m_camera != NULL;}
		bool IsDepthSet()const {return m_depthSet;}
		bool IsImageSizeSet()const {return m_imgSizeSet;}

		int GetNumLights()const{return m_numLights;}
		int GetNumObjects()const{return m_numObjects;}
		int GetDepth()const{return m_depth;}
		int GetImgSize()const{return m_imgSize;}

	private:

		Color GenerateColor(const Vector3& point,const SceneObject* obj,const Vector3& normal)const;

		Light*			m_lights[MAX_LIGHTS];
		SceneObject*	m_sceneObjects[MAX_SHAPES];

		Camera*			m_camera;

		rgbColorVal*    m_SceneMem;

		int				m_numLights;
		int				m_numObjects;

		int				m_imgSize;
		int				m_depth;
		bool			m_depthSet,m_imgSizeSet;
};


#endif