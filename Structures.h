#pragma once

#include "GL\freeglut.h"
#include <math.h>

#ifndef _hStructs
#define _hStructs

	struct Vector3
	{
		float x, y, z;

		Vector3() : x(0), y(0), z(0) {}

		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	};

	struct Vector4
	{
		float x, y, z, w;

		Vector4() : x(0), y(0), z(0), w(0) {}

		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	};

	class Camera
	{
		public:
			Vector3 eye, center, up;
	};

	struct Color
	{
		GLfloat r, g, b;
	};

	struct Vertex
	{
		GLfloat	x, y, z;
	};

	struct TexCoord
	{
		GLfloat u, v;
	};

	struct lighting
	{
		Vector4 ambient, diffuse, specular;
	};

	struct material
	{
		Vector4 ambient, diffuse, specular;
		GLfloat shininess;
	};

	struct Mesh
	{
		Vertex* indexedVertices;
		Vector3* indexedNormals;
		GLushort* indices;
		TexCoord* TexCoords;
		int numVertices, numNormals, numIndices, numTexCoords;
	};


#endif // !_hStructs