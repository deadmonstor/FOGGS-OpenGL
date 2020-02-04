#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

#define REFRESHRATE 16

class HelloGL
{
	public:

		HelloGL(int argc, char* argv[]);

		void Display();
		void DrawPolygon();
		void Update();

		void Keyboard(unsigned char key, int x, int y);

		~HelloGL(void);

	private:
		float rotation;

};
