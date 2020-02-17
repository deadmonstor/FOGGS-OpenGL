#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Cube.h"
#include <vector>

#define REFRESHRATE 16

class HelloGL
{
	public:

		HelloGL(int argc, char* argv[]);

		void Display();
		void Update();

		void Keyboard(unsigned char key, int x, int y);

		~HelloGL(void);

	private:
		float rotation;
		Camera* curCamera;
		std::vector<Cube*> cubes;

};
