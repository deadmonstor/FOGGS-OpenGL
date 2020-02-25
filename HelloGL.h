#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL\freeglut.h"
#include "GLUTCallbacks.h"

#ifndef _Texture2D
#include "Texture2D.h"
#endif

#ifndef _Cube
#include "Cube.h"
#endif

#ifndef _Pyramid
#include "pyramid.h"
#endif

#ifndef _MeshLoader
#include "MeshLoader.h"
#endif

#ifndef _SceneObject
#include "SceneObject.h"
#endif

#ifndef _hStructs
#include "Structures.h"
#endif

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

		void InitObjects();
		void InitGL(int argc, char* argv[]);

	private:
		float rotation;
		Camera* curCamera;
		std::vector<SceneObject*> objects;

};
