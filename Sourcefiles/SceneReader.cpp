//SceneReader.cpp
#include "SceneReader.h"
#include <algorithm>


void SceneReader::InitReaderFuncs()
{
	m_readerFuncs["sphere"] = &SceneReader::ReadSphere;
	m_readerFuncs["plane"]  = &SceneReader::ReadPlane; 
}

SceneObject* SceneReader::ReadSphere(istream& strStream)
{
	Vector3  pos;
	Vector3  rayOri;
	float    radius;  
	Color    col;		   
	Material mat;        

	strStream >> pos >> radius >> col >> mat >> rayOri;

	SceneObject* obj = new SceneObject(SPHERETYPE,pos,radius,col,mat,rayOri);
	return obj;
}

SceneObject* SceneReader::ReadPlane(istream&  strStream)
{
	Vector3  normal;
	Vector3  rayOri;
	float    distance;
	Color    col;
	Material mat;

	strStream >> normal >> distance >> col >> mat >> rayOri;

	if(strStream.rdstate() & ios_base::failbit)
	{
		return NULL;
	}

	SceneObject* obj = new SceneObject(PLANETYPE,normal,distance,col,mat,rayOri);
	return obj;
}

Light*   SceneReader::ReadLight(istream& strStream)
{
	Color    col;
	Vector3  position;

	strStream >> position >> col;

	if(strStream.rdstate() & ios_base::failbit)
	{
		return NULL;
	}

	Light* light = new Light(col,position);
	return light;
}

Camera*  SceneReader::ReadCamera(istream& strStream)
{
	Vector3  position;
	Vector3  lookAt;
	Vector3  up;

	strStream >> position >> lookAt >> up;

	if(strStream.rdstate() & ios_base::failbit)
	{
		return NULL;
	}

	Camera* cam = new Camera(position,lookAt,up);
	return cam;
}

bool SceneReader::ReadSceneDescriptionFile(istream& inStream)
{
	int lineNum = 1;

	while(inStream)
	{
		string word;
		inStream >> word;
		lineNum++;

		transform(word.begin(),word.end(),word.begin(),::tolower);

		if(m_readerFuncs[word])
		{
			SceneObject* obj = (this->*m_readerFuncs[word])(inStream); 
			
			if(obj== NULL)
			{
				FormatErrorMessageAndCheck(word,lineNum);
				return false;
			}

			m_scenePtr->AddObject(obj);
		}
		else if(word == "camera")
		{
			Camera* cam = ReadCamera(inStream);

			if(cam== NULL)
			{
				FormatErrorMessageAndCheck(word,lineNum);
				return false;
			}

			m_scenePtr->AddCamera(cam);
		}
		else if(word == "light")
		{
			Light* light = ReadLight(inStream);

			if(light== NULL)
			{
				FormatErrorMessageAndCheck(word,lineNum);
				return false;
			}

			m_scenePtr->AddLight(light);
		}
		else if(word == "imagesize")
		{
			int imgSize = 0;
			inStream >> imgSize;
			m_scenePtr->SetImageSize(imgSize);
		}
		else if(word == "depth")
		{
			int depth = 0;
			inStream >> depth;
			m_scenePtr->SetDepth(depth);
		}
		else if(word != "" && word[0] != '#' && word[0] != ' ')
		{
			cout <<"unknown command at line "<< lineNum << endl;
		}
	}

	return true;
}

inline void SceneReader::FormatErrorMessageAndCheck(string& error,int codeLine)
{
	cerr <<"Incorrect "<< error << " description in the file at line" << codeLine << " !"<<endl;	
}