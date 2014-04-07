//main.cpp - main 
#include <boost\thread.hpp>
#include "Camera.h"
#include "Scene.h"
#include "Light.h"

#include "Camera.h"
using namespace std;

const int IMAGE_SIZE = 512;



int main()
{
	Scene myScene(IMAGE_SIZE);
	ofstream outFile;

	//for profiling
	LARGE_INTEGER t1,t2,frequency;
	SYSTEM_INFO sysInfo;
	double elapsedTime;

	GetSystemInfo(&sysInfo);

	cout <<"num of coures: "<<sysInfo.dwNumberOfProcessors<<endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);

	outFile.open("test.ppm");

	Material sphereMaterial;
	Material planeMaterial;

	sphereMaterial.diffuse = 0.2f;
	sphereMaterial.specular = 0.8f;
	sphereMaterial.reflection = 0.8f;

	planeMaterial.diffuse = 0.8f;
	planeMaterial.specular = 0.2f;
	planeMaterial.reflection = 0.5f;

	//create lights
	Light  myLight1(Color(0.8f,0.8f,0.8f),Vector3(-10.0f,10.0f,5.0f));
	Light  myLight2(Color(0.3f,0.3f,0.3f),Vector3(5.0f,3.0f,5.0f));

	//create objects
	//spheres
	SceneObject so1(Color(0.0f,1.0f,0.0f),SPHERETYPE,Vector3(-1.2f,0.5f,0.0f),0.5f,sphereMaterial);

	sphereMaterial.diffuse   = 0.4f;
	sphereMaterial.specular  = 0.6f;

	SceneObject so2(Color(1.0f,0.0f,0.0f),SPHERETYPE,Vector3(0.0f,0.5f,0.0f),0.5f,sphereMaterial);

	
	
	
	sphereMaterial.diffuse   = 0.7f;
	sphereMaterial.specular  = 0.3f;

	SceneObject so3(Color(0.0f,0.0f,1.0f),SPHERETYPE,Vector3(1.2f,0.5f,0.0f),0.5f,sphereMaterial);

	//planes
	SceneObject po1(Color(0.5f,0.0f,0.5f),PLANETYPE,Vector3(0.0f,1.0f,0.0f),0.0f,planeMaterial);

	//add them to the scene
	myScene.AddLight(&myLight1);
	myScene.AddLight(&myLight2);
	myScene.AddObject(&so1);
	myScene.AddObject(&so2);
	myScene.AddObject(&so3);
	myScene.AddObject(&po1);

	Camera myCam(Vector3(-1.5f,1.0f,3.0f),Vector3(-0.3f,0.5f,0.0f),Vector3(0.0f,1.0f,0.0f));

	boost::thread thread1(&Scene::Render,&myScene,myCam,0,IMAGE_SIZE/2,0,IMAGE_SIZE/2,IMAGE_SIZE);
	boost::thread thread2(&Scene::Render,&myScene,myCam,0,IMAGE_SIZE/2,IMAGE_SIZE/2,IMAGE_SIZE,IMAGE_SIZE);
	boost::thread thread3(&Scene::Render,&myScene,myCam,IMAGE_SIZE/2,IMAGE_SIZE,0,IMAGE_SIZE/2,IMAGE_SIZE);
	boost::thread thread4(&Scene::Render,&myScene,myCam,IMAGE_SIZE/2,IMAGE_SIZE,IMAGE_SIZE/2,IMAGE_SIZE,IMAGE_SIZE);

	//myScene.Render(myCam,0,256,0,256,512);
	//myScene.Render(myCam,0,256,256,512,512);
	//myScene.Render(myCam,256,512,0,256,512);
	//myScene.Render(myCam,256,512,256,512,512);

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();

	myScene.WriteToFile(outFile,IMAGE_SIZE);

	outFile.close();

	QueryPerformanceCounter(&t2);

	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0f/frequency.QuadPart;

	cout << "elapsed Time : "<< elapsedTime <<endl;

	return 0;
}

