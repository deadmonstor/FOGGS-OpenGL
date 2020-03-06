
#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);

		helloGL->Update();

		updateTime = (glutGet(GLUT_ELAPSED_TIME) - updateTime);

		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key , x , y);
	}

	void mouseButton(int button, int state, int x, int y) 
	{
		helloGL->mouseButton(button, state, x, y);
	}

	void mouseMove(int x, int y)
	{
		helloGL->mouseMove(x, y);
	}

	void releaseKeyboard(unsigned char key, int x, int y)
	{
		helloGL->releaseKeyboard(key, x, y);
	}
}
