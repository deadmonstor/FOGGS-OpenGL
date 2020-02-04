#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"


class HelloGL
{
public:

	HelloGL(int argc, char* argv[]);

	void Display();
	void DrawPolygon();

	~HelloGL(void);
};
