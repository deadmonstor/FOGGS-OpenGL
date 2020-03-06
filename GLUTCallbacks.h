#pragma once
class HelloGL;
#include "GL\freeglut.h"
#include <iostream>

namespace GLUTCallbacks
{

	void Init(HelloGL* gl);
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void Display();
	void mouseButton(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void releaseKeyboard(unsigned char key, int x, int y);
}
