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

void Scene::AddMaterial(Material* newMaterial)
{
	assert(m_numMaterials < MAX_MATERIALS && "tried to add too many materials! \n");

	m_materials[m_numMaterials++] = newMaterial;
}

/*
TraceRay(const Ray& ray)
Args: A ray to test for intersections against
Return: A color of the intersected shape if any intersections, or solid black if not
Side Effects: None!
*/

Color Scene::TraceRay(const Ray& ray,int depth) const
{
	Color thisPixel(0.0f,0.0f,0.0f);

	SceneObject* obj = NULL;

	Vector3 origin    = ray.GetOrigin();
	Vector3 direction = ray.GetDirection();


	float t = FindNearest(origin,direction,&obj);

	if(!obj)
	{
		return thisPixel;
	}
	else
	{
		Vector3 intersectionPoint = origin + t * direction;
		Vector3 lightVectorDir;
		for(int light = 0; light < m_numLights; light++)
		{
			float coeff = CalcShade(m_lights[light],intersectionPoint,lightVectorDir);
			if(coeff > 0.0f)
			{
				int matIndex = obj->m_matIndex;
				float diffCoeff = m_materials[matIndex]->m_diffuse;
				float specCoeff = m_materials[matIndex]->m_specular;

				Vector3 normal = obj->GetSurfaceNormal(intersectionPoint);
				float dotProd   = DotProduct(lightVectorDir,normal);

				
				thisPixel +=  m_lights[light]->GetColor() * obj->GetColor() * diffCoeff  
								  * max(dotProd,0.0f);

				if(specCoeff > 0.1f)
				{
					Vector3 specReflect = lightVectorDir- 2.0f * dotProd * normal;

					thisPixel += m_lights[light]->GetColor() * Color(1.0f,1.0f,1.0f) * specCoeff
						* pow(DotProduct(direction,specReflect),20.0f);
				}
				
				float refIndex = m_materials[matIndex ]->m_reflection;

				if(depth > 1 && refIndex > 0.1f)
				{
					Vector3 newReflectRay = direction - 2.0f * DotProduct(direction,normal) * normal;
					thisPixel += refIndex * TraceRay(Ray(newReflectRay,intersectionPoint + newReflectRay * 0.001f),depth-1);
				}
			}
		}
	}

	return thisPixel;

}

float Scene::FindNearest(const Vector3& rayOrigin,const Vector3& rayDirection,SceneObject** obj)const
{
	//find the lowest timeValue for any intersection
	float t = 1000.0f;

	Vector3 surfaceNormal;
	Vector3 reflectDirection;
	Vector3 point;


	float rayDot			= DotProduct(rayDirection,rayDirection);
	float rayOriDot			= DotProduct(rayOrigin,rayOrigin);
	float rayOriDirDot		= DotProduct(rayDirection,rayOrigin);

	for(int shape = 0; shape < m_numObjects; shape++)
	{

		float newT = m_sceneObjects[shape]->GetIntersection(rayOrigin,rayDirection,rayDot,rayOriDot,rayOriDirDot); 
		
		if(newT<t && newT != NO_INTERSECTION)
		{
			t = newT;
			*obj = m_sceneObjects[shape];
		}
	}

	if(t == 1000.0f || t == NO_INTERSECTION) 
	{
		return 0.0f;
	}
	else
	{
		return t;
	}
}

float Scene::CalcShade(Light* light,const Vector3& intersectionPoint,Vector3& lightVectorDir)const
{
	SceneObject* obj = NULL;

	Vector3 toLightDir = Normalize(light->GetPosition() - intersectionPoint);
	lightVectorDir = toLightDir;

	FindNearest(intersectionPoint  + toLightDir * 0.0001f,toLightDir,&obj);
	
	if(obj) return 0.0f;

	return 1.0f;
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
	int imgSizeMinusOne = imgSize-1;
	float ratio = 1.0f/(float)(imgSize);


	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd;x++)
		{
			int offset     = imgBottom - (y * imgSize) + x; 
			Ray   pixelRay = m_camera->GetRayForPixel(x,y,ratio);
			Color col      = TraceRay(pixelRay,depth);

			col			   = 255.0f * col;
			col.Clamp(0.0f,255.0f);

			m_SceneMem[offset].b = col[0];
			m_SceneMem[offset].g = col[1];
			m_SceneMem[offset].r = col[2];

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