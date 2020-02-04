#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

#define REFRESHRATE 16


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


class HelloGL
{
	public:

		HelloGL(int argc, char* argv[]);

		void Display();
		void DrawPolygon();
		void Update();
		void DrawCube();
		void DrawCubeArray();
		void DrawIndexedCube();

		void DrawCubeArrayAlt();
		void DrawIndexedCubeAlt();

		void Keyboard(unsigned char key, int x, int y);

		~HelloGL(void);

	private:
		float rotation;
		Camera* curCamera;

		static Vertex vertices[];
		static Color colors[];

		static Vertex indexedVertices[];
		static Color indexedColors[];
		static GLushort indices[];

};
