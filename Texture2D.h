#pragma once

#ifndef _Texture2D

#define _Texture2D

	#include "GL\freeglut.h"
	#include <iostream>
	#include <fstream>

	class Texture2D
	{
	private:
		GLuint _ID; //Texture ID
		int _width, _height;

	public:
		Texture2D();
		~Texture2D();

		bool Load(char* path, int width, int height);

		GLuint GetID() const { return _ID; }
		int GetWidth() const { return _width; }
		int GetHeight() const { return _height; }
	};

#endif