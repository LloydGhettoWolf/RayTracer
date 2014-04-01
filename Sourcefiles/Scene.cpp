//Scene.cpp
#include "Scene.h"


typedef vector<SceneObject*>::const_iterator constShapeItr;
typedef vector<Light*>::const_iterator constLightItr;

Color Scene::TraceRay(const Ray& ray) const
{
	//find the lowest timeValue for any intersection
	float t = 1000.0f;
	SceneObject *sceneObj = NULL;

	for(constShapeItr sItr = m_objects.begin(); sItr != m_objects.end(); sItr++)
	{
		float newT = (*sItr)->GetIntersection(ray); 
		
		if(newT<t && newT != NO_INTERSECTION)
		{
			t = newT;
			sceneObj = *sItr;
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

	for(constLightItr lItr = m_lights.begin(); lItr != m_lights.end(); lItr++)
	{
		Vector3 toLight = (*lItr)->GetPosition() - point;
		toLight = toLight.Normalize();
		Vector3 normal = obj->GetSurfaceNormal(point);
		float dotProduct = toLight.DotProduct(normal);

		assert(dotProduct <= 1.0f && "dotProduct is over 1.0f!");

		newColor += obj->GetColor() * (*lItr)->GetColor() *  max(dotProduct,0.0f);
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