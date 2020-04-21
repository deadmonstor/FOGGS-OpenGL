#pragma once

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL\freeglut.h"
#include "GLUTCallbacks.h"

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"

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

class mainGame
{
	public:

		mainGame(int argc, char* argv[]);

		void Display();
		void Update();

		void Keyboard(unsigned char key, int x, int y);
		void releaseKeyboard(unsigned char key, int x, int y);

		~mainGame(void);

		void InitObjects();
		void InitLighting();
		void InitGL(int argc, char* argv[]);

		void mouseButton(int button, int state, int x, int y);
		void mouseMove(int x, int y);
		void computePos(float deltaMove);

		void ShowMenu();
		void timerCheck();
		bool test;

	private:
		float rotation;
		Camera* curCamera;
		Vector3 cameraPos = Vector3(0.0f, 0.0f, 0.0f);

		float angle = 0.0f;
		float lx = 0.0f, ly = 0.0f, lz = -1.0f;
		float x = 0.0f, y = 0.0f, z = 5.0f;

		float deltaAngle = 0.0f;
		float deltaMove = 0;
		int xOrigin = -1;
		int yOrigin = -1;

		std::vector<SceneObject*> objects;

		Vector4* _lightPosition;
		lighting* _lightData;

		bool shouldGetPixel;

		int objectToShootID = 0;

};
