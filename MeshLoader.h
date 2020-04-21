#pragma once

#ifndef _MeshLoader
#define _MeshLoader

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include "GL\freeglut.h"

#ifndef _hStructs
#include "Structures.h"
#endif
using namespace std;

	class MeshLoader
	{
		public:
				Mesh* Load(char* path);
				static MeshLoader* Instance();
		
		private:
			vector<string> whiteSpaceRegex(string line);
			void LoadVertices(ifstream& inFile, Mesh& mesh);
			void LoadNormals(ifstream& inFile, Mesh& mesh);
			void LoadUVs(ifstream& inFile, Mesh& mesh);
			void LoadIndices(ifstream& inFile, Mesh& mesh);
			static MeshLoader* m_Instance;

	};

#endif // !_MeshLoader
