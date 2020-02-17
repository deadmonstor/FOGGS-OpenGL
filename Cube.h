#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
	private:
		static Vertex* indexedVertices;
		static Color* indexedColors;
		static GLushort* indices;

		static int numVertices, numColors, numIndices;

		GLfloat _rotation = 0;
		Vector3 _position;

	public:
		Cube(float x, float y, float z);
		~Cube();

		static bool Load(char* path);

		void Draw();
		void Update();
};