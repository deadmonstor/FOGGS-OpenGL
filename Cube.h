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

	#ifndef _Texture2D
	#include "Texture2D.h"
	#endif

	class Cube : public SceneObject
	{
	private:
		Texture2D* _texture;
		material* _material;

	public:

		Cube(Mesh* mesh, Texture2D* _texture, float x, float y, float z, int _id);
		~Cube();

		void Draw();
		void Update();
	};

#endif // !_Cube