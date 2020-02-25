#pragma once

#include "GL\freeglut.h"

#ifndef _hStructs
#define _hStructs

	struct Vector3
	{
		float x, y, z;

		Vector3() : x(0), y(0), z(0) {}

		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	};

	struct Camera
	{
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

	struct Mesh
	{
		Vertex* indexedVertices;
		Color* indexedColors;
		GLushort* indices;
		TexCoord* TexCoords;
		int numVertices, numColors, numIndices, numTexCoords;
	};


#endif // !_hStructs