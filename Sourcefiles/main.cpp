//main.cpp - main 
#include <boost\thread.hpp>
#include "Camera.h"
#include "Scene.h"
#include "Light.h"
#include "SceneReader.h"
#include "Camera.h"
using namespace std;



int main()
{

	//for profiling
	LARGE_INTEGER t1,t2,t3,t4,frequency;
	SYSTEM_INFO sysInfo;
	double elapsedTime;

	GetSystemInfo(&sysInfo);

	cout <<"num of coures: "<<sysInfo.dwNumberOfProcessors<<endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);

	Scene myScene;
	SceneReader reader(&myScene);
	ofstream outFile;
	ifstream sceneDescription;

	sceneDescription.open("description.txt");


	if(!reader.ReadSceneDescriptionFile(sceneDescription))
	{
		sceneDescription.close();
		cerr << "cant process the scene" <<endl;
		return 1;
	}

	sceneDescription.close();



	if(!myScene.HasCamera())
	{
		cerr<<"no camera set!"<<endl;
		return 1;
	}

	if(myScene.GetNumLights() == 0)
	{
		cerr<<"no lights set!"<<endl;
		return 1;
	}

	if(myScene.GetNumObjects() == 0)
	{
		cerr<<"no objects set!"<<endl;
		return 1;
	}

	if(!myScene.IsDepthSet())
	{
		cerr <<"depth not set!"<<endl;
		return 1;
	}

	if(!myScene.IsImageSizeSet())
	{
		cerr <<"imageSize not set!"<<endl;
		return 1;
	}

	QueryPerformanceCounter(&t2);

	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0f/frequency.QuadPart;

	cout << "elapsed Time reading : "<< elapsedTime <<endl;
	

	

	

	int imageSize = myScene.GetImgSize();
	int depth = myScene.GetDepth();

	

	boost::thread thread1(&Scene::Render,&myScene,0,imageSize/2,0,imageSize/2,imageSize,depth);
	boost::thread thread2(&Scene::Render,&myScene,0,imageSize/2,imageSize/2,imageSize,imageSize,depth);
	boost::thread thread3(&Scene::Render,&myScene,imageSize/2,imageSize,0,imageSize/2,imageSize,depth);
	boost::thread thread4(&Scene::Render,&myScene,imageSize/2,imageSize,imageSize/2,imageSize,imageSize,depth);


	//myScene.Render(myCam,0,256,0,256,512);
	//myScene.Render(myCam,0,256,256,512,512);
	//myScene.Render(myCam,256,512,0,256,512);
	//myScene.Render(myCam,256,512,256,512,512);

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();

	QueryPerformanceCounter(&t3);

	elapsedTime = (t3.QuadPart - t2.QuadPart) * 1000.0f/frequency.QuadPart;

	cout << "elapsed Time rendering : "<< elapsedTime <<endl;

	outFile.open("test.tga",ofstream::binary);

	myScene.WriteToTGAFile(outFile,imageSize);

	outFile.close();

	QueryPerformanceCounter(&t4);

	elapsedTime = (t4.QuadPart - t3.QuadPart) * 1000.0f/frequency.QuadPart;

	cout << "elapsed Time writing : "<< elapsedTime <<endl;

	elapsedTime = (t4.QuadPart - t1.QuadPart) * 1000.0f/frequency.QuadPart;

	cout << "total : "<< elapsedTime <<endl;

	return 0;
}

