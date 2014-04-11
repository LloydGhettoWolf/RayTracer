//Scene.cpp
#include "Scene.h"


#define SPECULAR_ON

#define SHADOWS_ON



Scene::~Scene()
{
	for(int light = 0; light < m_numLights; light++)
		delete m_lights[light];

	for(int obj = 0; obj < m_numObjects; obj++)
		delete m_sceneObjects[obj];

	if(m_SceneMem)
		delete [] m_SceneMem;

	delete m_camera;
}

void  Scene::SetImageSize(int imgSize)
{
	m_imgSize = imgSize;
	m_SceneMem = new rgbColorVal[imgSize*imgSize]; 
	m_imgSizeSet = true;
}

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
	assert(m_numObjects < MAX_SHAPES && "tried to add too many objects! \n");

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

		//if(sceneObj->GetType() == PLANETYPE) depth++;

		return GenerateColor(point,sceneObj,surfaceNormal) + 
			sceneObj->m_material.reflection * TraceRay(newRay,depth-1,nextCurrentShape);
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
	Color spec(0.0f,0.0f,0.0f);
	Color diffuse(0.0f,0.0f,0.0f);

	float lightCoeff = 1.0f;

	for(int light = 0; light < m_numLights; light++)
	{
		Vector3 toLight = m_lights[light]->GetPosition() - point;
		toLight = Normalize(toLight);

		float t = 1000.0f;
		
#ifdef SHADOWS_ON

		for(int shape = 0; shape < m_numObjects; shape++)
		{

			float newT = m_sceneObjects[shape]->GetIntersection(Ray(toLight,point + toLight * 0.001f)); 
		
			if(newT<t && newT != NO_INTERSECTION)
			{
				lightCoeff = 0.5f;
			}
		}
#endif

float dotProduct = DotProduct(toLight,normal);

#ifdef SPECULAR_ON

	Vector3 reflectVector = toLight - 2.0f * dotProduct * normal;

	float specCoeff  = DotProduct(Normalize(point),reflectVector);
	spec    = obj->m_material.specular * Color(1.0f,1.0f,1.0f) *  pow(specCoeff,40.0f);

	//assert(dotProduct <= 1.0f && "dotProduct is over 1.0f!");

	diffuse = obj->m_material.diffuse  * obj->GetColor() * m_lights[light]->GetColor() *  max(dotProduct,0.0f);
#else
    diffuse =  obj->GetColor() * m_lights[light]->GetColor() *  max(dotProduct,0.0f);
#endif


		newColor += diffuse + spec;
	}

	
	return newColor * lightCoeff;

}

/*
Scene::Render(const Camera& cam,ofstream& outStream,int imgSize)
Args - a ref to a camera, an output file stream to write to and the imgSize both
horizontal and vertical 
Return - none
Side Effects - the output file is turned into a .ppm file of the raytraced image generated
*/
void Scene::Render(int xStart,int xEnd,int yStart,int yEnd,int imgSize,int depth)
{
	int imgBottom = imgSize * (imgSize-1);

	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd;x++)
		{
			int offset     = imgBottom - (y * imgSize) + x; 
			Ray   pixelRay = m_camera->GetRayForPixel(x,y,imgSize);
			Color col      = TraceRay(pixelRay,depth);

			col			   = 255.0f * col;
			col.Clamp((float)0,(float)255);

			m_SceneMem[offset].b = (char)col[0];
			m_SceneMem[offset].g = (char)col[1];
			m_SceneMem[offset].r = (char)col[2];

		}
	}

}

/*
Scene::WriteToTGAFile(ofstream& outfile,int imgSize)
Args - ref to an outfile stream and the imgsize - width and height are the same
Return vals - none
Side Effects - writes the image stored in scene mem to the outfile so that a .tga texture file is performed.
Fast! Writes out in about 6 milliseconds :)
*/

void Scene::WriteToTGAFile(ofstream& outFile,int imgSize)
{

   char headerFile[18] = {0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;

   headerFile[12] = imgSize			& 0xFF;
   headerFile[13] = (imgSize >> 8)	& 0xFF;
   headerFile[14] = imgSize			& 0xFF;
   headerFile[15] = (imgSize >> 8)	& 0xFF;
   headerFile[16] = 24;

   outFile.write(headerFile,18);

   outFile.write((char*)m_SceneMem,imgSize*imgSize * 3);


}