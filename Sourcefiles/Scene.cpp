//Scene.cpp
#include "Scene.h"

const int MAX_LIGHTS = 10;
const int MAX_OBJS   = 10;

void  Scene::AddLight(Light* newLight)
{
	assert(m_numLights < MAX_LIGHTS && "tried to add too many lights! \n");

	m_lights[m_numLights++] = newLight;
}

void  Scene::AddObject(SceneObject* newObject)
{
	assert(m_numObjects < MAX_LIGHTS && "tried to add too many lights! \n");

	m_sceneObjects[m_numObjects++] = newObject;
}

Color Scene::TraceRay(const Ray& ray) const
{
	//find the lowest timeValue for any intersection
	float t = 1000.0f;
	SceneObject *sceneObj = NULL;

	for(int shape = 0; shape < m_numObjects; shape++)
	{
		float newT = m_sceneObjects[shape]->GetIntersection(ray); 
		
		if(newT<t && newT != NO_INTERSECTION)
		{
			t = newT;
			sceneObj = m_sceneObjects[shape];
		}
	}

	if(t == 1000.0f) 
	{
		t = NO_INTERSECTION;
	}

	return t == NO_INTERSECTION ? Color(0.0f,0.0f,0.0f) : GenerateColor(ray.GetOrigin() + t * ray.GetDirection(),sceneObj);
}

Color Scene::GenerateColor(const Vector3& point,const SceneObject* obj)const
{
	Color newColor(0.0f,0.0f,0.0f);

	for(int light = 0; light < m_numLights; light++)
	{
		Vector3 toLight = m_lights[light]->GetPosition() - point;
		toLight = toLight.Normalize();
		Vector3 normal = obj->GetSurfaceNormal(point);
		float dotProduct = toLight.DotProduct(normal);

		assert(dotProduct <= 1.0f && "dotProduct is over 1.0f!");

		newColor += obj->GetColor() * m_lights[light]->GetColor() *  max(dotProduct,0.0f);
	}

	return newColor;
}

void Scene::Render(const Camera& cam,ofstream& outStream,int imgSize)
{

	outStream <<"P3 "<< imgSize << " " << imgSize << " " << 255 << " \n";

	for(int y = 0; y < imgSize;y++)
	{
		for(int x = 0; x < imgSize;x++)
		{
			Ray   pixelRay = cam.GetRayForPixel(x,y,imgSize);
			Color col      = TraceRay(pixelRay);
			col = 255.0f * col;
			col.Clamp((float)0,(float)255);

			outStream<< (int)col[0] << " " << (int)col[1] << " " << (int)col[2] <<"\n";
		}
	}

}