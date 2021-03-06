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
	float    radius;  
	Color    col;		   
	int      matIndex;       

	strStream >> pos >> radius >> col >> matIndex;

	SceneObject* obj = new SceneObject(SPHERETYPE,pos,radius,col,matIndex-1);
	return obj;
}

SceneObject* SceneReader::ReadPlane(istream&  strStream)
{
	Vector3  normal;
	float    distance;
	Color    col;
	int      matIndex;

	strStream >> normal >> distance >> col >> matIndex;

	if(strStream.rdstate() & ios_base::failbit)
	{
		return NULL;
	}

	SceneObject* obj = new SceneObject(PLANETYPE,normal,distance,col,matIndex-1);
	return obj;
}

Light*   SceneReader::ReadLight(istream& strStream)
{
	Color    col;
	Vector3  position;
	bool type;

	strStream >> position >> col >> type;

	if(strStream.rdstate() & ios_base::failbit)
	{
		return NULL;
	}

	Light* light = new Light(col,position,type);
	return light;
}

Material* SceneReader::ReadMaterial(istream& is)
{
	char input;
	float diff,reflect,refract,spec;

	is >> input;

	if(input == '(')
	{
		
		is >> diff >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return NULL;
		}

		is >> reflect >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return NULL;
		}

		is >> refract >> input;

		if(input != ',')
		{
			is.clear(ios_base::failbit);
			return NULL;
		}

		is >> spec >> input;

		if(input != ')')
		{
			is.clear(ios_base::failbit);
			return NULL;
		}
	}
	else
	{
		is.clear(ios_base::failbit);
		return NULL;
	}

	if(is.rdstate() & ios_base::failbit)
	{
		return NULL;
	}

	Material* mat = new Material(spec,diff,reflect,refract);
	return mat;
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
		else if(word == "material")
		{
			Material* mat = ReadMaterial(inStream);

			if(mat == NULL)
			{
				FormatErrorMessageAndCheck(word,lineNum);
				return false;
			}

			m_scenePtr->AddMaterial(mat);
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