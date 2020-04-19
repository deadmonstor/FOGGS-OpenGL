#pragma once

#ifndef _Pyramid
 
#define _Pyramid

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

	#ifndef _Texture2D
	#include "Texture2D.h"
	#endif

	#ifndef _hStructs
	#include "Structures.h"
	#endif

	class Pyramid : public SceneObject
	{
	private:
		Texture2D* _texture;

	public:

		Pyramid(Mesh* mesh, Texture2D* text, float x, float y, float z, int _id);
		~Pyramid();

		void Draw() override;
		void Update() override;
	};

#endif // !_Cube