#include "Cube.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

Vertex* Cube::indexedVertices = nullptr;
Color* Cube::indexedColors = nullptr;
GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;

using namespace std;

Cube::Cube(float x, float y, float z)
{

	_position = Vector3(x, y, z);

}

void Cube::Update()
{
	//_rotation += 0.1f;
}

void Cube::Draw()
{

	if (indexedVertices != nullptr && indexedColors != nullptr && indices != nullptr)
	{
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
		glColorPointer(3, GL_FLOAT, 0, indexedColors);

		glPushMatrix();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

vector<string> whiteSpaceRegex(string line)
{

	regex ws_re("(\ )+");
	vector<string> result{
		sregex_token_iterator(line.begin(), line.end(), ws_re, -1), {}
	};


	return result;
}

bool Cube::Load(char* path)
{
	ifstream inFile;
	inFile.open(path);

	if (!inFile.good())
	{
		cerr << "Can't open text file " << path << endl;
		return false;
	}

	vector<string> result;
	string line;
	getline(inFile, line);

	numVertices = stoi(line);
	indexedVertices = new Vertex[numVertices];

	for (int i = 0; i < numVertices; i++)
	{
		getline(inFile, line);

		result = whiteSpaceRegex(line);

		if (result.size() == 3)
		{
			indexedVertices[i].x = stof(result[0]);
			indexedVertices[i].y = stof(result[1]);
			indexedVertices[i].z = stof(result[2]);
		}

	}

	getline(inFile, line);

	numColors = stoi(line);
	indexedColors = new Color[numColors];

	for (int i = 0; i < numColors; i++)
	{
		getline(inFile, line);

		result = whiteSpaceRegex(line);

		if (result.size() == 3)
		{
			indexedColors[i].r = stof(result[0]);
			indexedColors[i].g = stof(result[1]);
			indexedColors[i].b = stof(result[2]);
		}

	}


	getline(inFile, line);

	numIndices = stoi(line);
	indices = new GLushort[numIndices];

	for (int i = 0; i < numIndices; i += 3)
	{
		getline(inFile, line);

		result = whiteSpaceRegex(line);

		if (result.size() == 3)
		{
			indices[i] = stoi(result[0]);
			indices[i + 1] = stoi(result[1]);
			indices[i + 2] = stoi(result[2]);
		}

	}

	inFile.close();

	return true;
}


Cube::~Cube()
{

}