//main.cpp - main 
#include "Camera.h"
#include "Scene.h"
#include "Light.h"

#include "Camera.h"
using namespace std;

const int IMAGE_SIZE = 256;



int main()
{
	Scene myScene;
	ofstream outFile;

	//for profiling
	LARGE_INTEGER t1,t2,frequency;
	double elapsedTime;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);

	outFile.open("test.ppm");

	//create lights
	Light  myLight1(Color(0.8f,0.8f,0.8f),Vector3(-10.0f,10.0f,5.0f));
	Light  myLight2(Color(0.3f,0.3f,0.3f),Vector3(5.0f,3.0f,5.0f));

	//create objects
	//spheres
	SceneObject so1(Color(0.0f,1.0f,0.0f),SPHERETYPE,Vector3(-1.2f,0.5f,0.0f),0.5f);
	SceneObject so2(Color(1.0f,0.0f,0.0f),SPHERETYPE,Vector3(0.0f,0.5f,0.0f),0.5f);
	SceneObject so3(Color(0.0f,0.0f,1.0f),SPHERETYPE,Vector3(1.2f,0.5f,0.0f),0.5f);
	
	//planes
	SceneObject po1(Color(0.5f,0.0f,0.5f),PLANETYPE,Vector3(0.0f,1.0f,0.0f),0.0f);

	//add them to the scene
	myScene.AddLight(&myLight1);
	myScene.AddLight(&myLight2);
	myScene.AddObject(&so1);
	myScene.AddObject(&so2);
	myScene.AddObject(&so3);
	myScene.AddObject(&po1);

	Camera myCam(Vector3(-1.5f,1.0f,3.0f),Vector3(-0.3f,0.5f,0.0f),Vector3(0.0f,1.0f,0.0f));

	myScene.Render(myCam,outFile,512);

	outFile.close();

	QueryPerformanceCounter(&t2);

	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0f/frequency.QuadPart;

	cout << "elapsed Time : "<< elapsedTime <<endl;

	return 0;
}

