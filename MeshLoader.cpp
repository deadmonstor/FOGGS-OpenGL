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

	void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		vector<string> result;
		string line;

		getline(inFile, line);

		mesh.numColors = stoi(line);
		mesh.indexedColors = new Color[mesh.numColors];

		for (int i = 0; i < mesh.numColors; i++)
		{
			getline(inFile, line);

			result = whiteSpaceRegex(line);

			if (result.size() == 3)
			{
				mesh.indexedColors[i].r = stof(result[0]);
				mesh.indexedColors[i].g = stof(result[1]);
				mesh.indexedColors[i].b = stof(result[2]);
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
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadColours(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}
}