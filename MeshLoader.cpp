#include "MeshLoader.h"
using namespace std;

namespace MeshLoader
{
	vector<string> whiteSpaceRegex(string line)
	{

		regex ws_re("(\ )+");
		vector<string> result{
			sregex_token_iterator(line.begin(), line.end(), ws_re, -1), {}
		};


		return result;
	}

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{

		vector<string> result;
		string line;
		getline(inFile, line);

		mesh.numVertices = stoi(line);
		mesh.indexedVertices = new Vertex[mesh.numVertices];

		for (int i = 0; i < mesh.numVertices; i++)
		{
			getline(inFile, line);

			result = whiteSpaceRegex(line);

			if (result.size() == 3)
			{
				mesh.indexedVertices[i].x = stof(result[0]);
				mesh.indexedVertices[i].y = stof(result[1]);
				mesh.indexedVertices[i].z = stof(result[2]);
			}

		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		vector<string> result;
		string line;

		getline(inFile, line);

		mesh.numNormals = stoi(line);
		mesh.indexedNormals = new Vector3[mesh.numNormals];

		for (int i = 0; i < mesh.numNormals; i++)
		{
			getline(inFile, line);

			result = whiteSpaceRegex(line);

			if (result.size() == 3)
			{
				mesh.indexedNormals[i].x = stof(result[0]);
				mesh.indexedNormals[i].y = stof(result[1]);
				mesh.indexedNormals[i].z = stof(result[2]);
			}

		}
	}

	void LoadUVs(ifstream& inFile, Mesh& mesh)
	{
		vector<string> result;
		string line;

		getline(inFile, line);

		mesh.numTexCoords = stoi(line);
		mesh.TexCoords = new TexCoord[mesh.numTexCoords];

		for (int i = 0; i < mesh.numTexCoords; i++)
		{
			getline(inFile, line);

			result = whiteSpaceRegex(line);

			if (result.size() == 2)
			{
				mesh.TexCoords[i].u = stof(result[0]);
				mesh.TexCoords[i].v = stof(result[1]);
			}

		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{

		vector<string> result;
		string line;
		getline(inFile, line);

		mesh.numIndices = stoi(line);
		mesh.indices = new GLushort[mesh.numIndices];

		for (int i = 0; i < mesh.numIndices; i += 3)
		{
			getline(inFile, line);

			result = whiteSpaceRegex(line);

			if (result.size() == 3)
			{

				mesh.indices[i] = stoi(result[0]);
				mesh.indices[i + 1] = stoi(result[1]);
				mesh.indices[i + 2] = stoi(result[2]);
			}

		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			delete mesh;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadUVs(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}
}