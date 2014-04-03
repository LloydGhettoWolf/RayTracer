//Scene.cpp
#include "Scene.h"

const int MAX_LIGHTS = 10;
const int MAX_OBJS   = 10;

/*
AddLight(Light* newLight)
Args:   A pointer to a light to add to the current list/array of lights
Return: Nothing/void
Side Effects: current number of lights incremented by one and light pointer added to list
*/
void  Scene::AddLight(Light* newLight)
{
	//assert(m_numLights < MAX_LIGHTS && "tried to add too many lights! \n");

	m_lights[m_numLights++] = newLight;
}

/*
AddObject(SceneObject* newLight)
Args:   A pointer to an object to add to the current list/array of sceneObjects
Return: Nothing/void
Side Effects: current number of sceneObjects incremented by one and sceneObject added to list
*/
void  Scene::AddObject(SceneObject* newObject)
{
	assert(m_numObjects < MAX_LIGHTS && "tried to add too many lights! \n");

	m_sceneObjects[m_numObjects++] = newObject;
}

/*
TraceRay(const Ray& ray)
Args: A ray to test for intersections against
Return: A color of the intersected shape if any intersections, or solid black if not
Side Effects: None!
*/
Color Scene::TraceRay(const Ray& ray,int depth,int currentShape) const
{

	//find the lowest timeValue for any intersection
	float t = 1000.0f;
	SceneObject *sceneObj = NULL;

	Vector3 surfaceNormal;
	Vector3 reflectDirection;
	Vector3 point;

	int nextCurrentShape = currentShape;

	for(int shape = 0; shape < m_numObjects; shape++)
	{
		if(shape == currentShape) continue;

		float newT = m_sceneObjects[shape]->GetIntersection(ray); 
		
		if(newT<t && newT != NO_INTERSECTION)
		{
			t = newT;
			sceneObj = m_sceneObjects[shape];
			nextCurrentShape = shape;
		}
	}

	if(t == 1000.0f || t == NO_INTERSECTION) 
	{
		return Color(0.0f,0.0f,0.0f);
	}
	else if(depth == 1)
	{
		point = ray.GetOrigin() + t * ray.GetDirection();
		surfaceNormal = sceneObj->GetSurfaceNormal(point);
		return GenerateColor(point,sceneObj,surfaceNormal);
	}
	else
	{
		//assert("it should never enter here!");
		point = ray.GetOrigin() + t * ray.GetDirection();
		surfaceNormal = sceneObj->GetSurfaceNormal(point);
		reflectDirection = Normalize(ray.GetDirection() - (2.0f * DotProduct(ray.GetDirection(),surfaceNormal))*surfaceNormal);

		Ray newRay = Ray(reflectDirection,point+reflectDirection * 0.001f);

		return GenerateColor(point,sceneObj,surfaceNormal) + 
			 sceneObj->GetReflectivity() * TraceRay(newRay,depth-1,nextCurrentShape);
	}

	 
}

/*
GenerateColor(const Vector3& point,const SceneObject* obj)const
Args: point - A Vector3 ref that contains the intersection point co ordinates
      obj - a pointer to a sceneObject to generate the color for
Return: A generated color from the lighting
Side Effects: None!
*/

Color Scene::GenerateColor(const Vector3& point,const SceneObject* obj,const Vector3& normal)const
{
	Color newColor(0.0f,0.0f,0.0f);

	for(int light = 0; light < m_numLights; light++)
	{
		Vector3 toLight = m_lights[light]->GetPosition() - point;
		toLight = Normalize(toLight);
		float dotProduct = DotProduct(toLight,normal);

		//assert(dotProduct <= 1.0f && "dotProduct is over 1.0f!");

		newColor += obj->GetColor() * m_lights[light]->GetColor() *  max(dotProduct,0.0f);
	}

	return newColor;
}

/*
Scene::Render(const Camera& cam,ofstream& outStream,int imgSize)
Args - a ref to a camera, an output file stream to write to and the imgSize both
horizontal and vertical 
Return - none
Side Effects - the output file is turned into a .ppm file of the raytraced image generated
*/
void Scene::Render(const Camera& cam,int xStart,int xEnd,int yStart,int yEnd,int imgSize)
{


	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd;x++)
		{
			int offset     = y * imgSize + x; 
			Ray   pixelRay = cam.GetRayForPixel(x,y,imgSize);
			Color col      = TraceRay(pixelRay,2);
			col			   = 255.0f * col;
			col.Clamp((float)0,(float)255);

			m_SceneMem[offset].r = (int)col[0];
			m_SceneMem[offset].g = (int)col[1];
			m_SceneMem[offset].b = (int)col[2];

		}
	}

}

void Scene::WriteToFile(ofstream& outFile,int imgSize)
{
	outFile <<"P3 "<< imgSize << " " << imgSize << " " << 255 << " \n";


	for(int y = 0; y < imgSize; y++)
	{
		for(int x = 0; x < imgSize;x++)
		{
			int offset     = y * imgSize + x; 
			outFile<< m_SceneMem[offset].r << " " << m_SceneMem[offset].g << " " << m_SceneMem[offset].b <<"\n";
		}
	}

}