#pragma once

#ifndef _Cube
 
#define _Cube

	#include <Windows.h>
	#include <gl/GL.h>
	#include <gl/GLU.h>
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <regex>
	#include "GL\freeglut.h"

	#ifndef _SceneObject
	#include "SceneObject.h"
	#endif

	#ifndef _hStructs
	#include "Structures.h"
	#endif

	class Cube : public SceneObject
	{
	private:
		GLfloat _rotation = 0;
		Vector3 _position;

	public:

		Cube(Mesh* mesh, float x, float y, float z);
		~Cube();

		void Draw();
		void Update();
	};

#endif // !_Cube