//main.cpp - main 
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Light.h"
#include "Plane.h"

#include "Camera.h"
using namespace std;

const int IMAGE_SIZE = 256;



int main()
{
	Scene myScene;
	ofstream outFile;

	outFile.open("test.ppm");
	Plane  myPlane(Vector3(0.0f,1.0f,0.0f),0.0f,Color(0.5f,0.0f,0.5f));

	Light  myLight1(Color(0.8f,0.8f,0.8f),Vector3(-10.0f,10.0f,5.0f));
	Light  myLight2(Color(0.3f,0.3f,0.3f),Vector3(5.0f,3.0f,5.0f));

	Sphere mySphere1(0.5f,Vector3(-1.2f,0.5f,0.0f),Color(1.0f,0.0f,0.0f));
	Sphere mySphere2(0.5f,Vector3(0.0f,0.5f,0.0f),Color(0.0f,1.0f,0.0f));
	Sphere mySphere3(0.5f,Vector3(1.2f,0.5f,0.0f),Color(0.0f,0.0f,1.0f));

	myScene.AddObject((SceneObject*)&mySphere1);
	myScene.AddObject((SceneObject*)&mySphere2);
	myScene.AddObject((SceneObject*)&mySphere3);
	myScene.AddObject((SceneObject*)&myPlane);
	myScene.AddLight(&myLight1);
	myScene.AddLight(&myLight2);

	Camera myCam(Vector3(-1.5f,1.0f,3.0f),Vector3(-0.3f,0.5f,0.0f),Vector3(0.0f,1.0f,0.0f));

	myScene.Render(myCam,outFile,512);

	outFile.close();

	Ray camRay = myCam.GetRayForPixel(512/2,34,512);

	cout << "Ray Origin :" << camRay.GetOrigin()<<endl<<" Ray Direction:"<< camRay.GetDirection() <<endl;

	Color col = myScene.TraceRay(camRay);
	
	cout << "color:" << col <<endl;

	return 0;
}

