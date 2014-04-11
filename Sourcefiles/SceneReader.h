//SceneReader.h
#ifndef _SCENE_READER_H
#define _SCENE_READER_H

#include "Scene.h"
#include <string>
#include <sstream>
#include <istream>
#include <map>

using namespace std;

enum ErrorType{SPHERE,PLANE,CAMERA,LIGHT};

class SceneReader
{
	public:
		SceneReader(Scene* scenePtr):m_scenePtr(scenePtr){InitReaderFuncs();}
		~SceneReader(){};

		void InitReaderFuncs();

		SceneObject* ReadSphere(istream& strStream);
		SceneObject* ReadPlane(istream&  strStream);

		Light*   ReadLight(istream& strStream);
		Camera*  ReadCamera(istream& strStream);

		bool ReadSceneDescriptionFile(istream& strStream);

		void FormatErrorMessageAndCheck(string& error,int codeLine);

	private:

		typedef SceneObject* (SceneReader::*SceneObjectReader) (istream& strStream);

		map<string,SceneObjectReader> m_readerFuncs;

		Scene* m_scenePtr;

};

#endif