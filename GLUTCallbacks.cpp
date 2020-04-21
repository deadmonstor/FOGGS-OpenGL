
#include "GLUTCallbacks.h"
#include "mainGame.h"

namespace GLUTCallbacks
{
	namespace
	{
		mainGame* mainGames = nullptr;
	}

	void Init(mainGame* gl)
	{
		mainGames = gl;
	}

	void Display()
	{
		if (mainGames != nullptr)
		{
			mainGames->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);

		mainGames->Update();

		updateTime = (glutGet(GLUT_ELAPSED_TIME) - updateTime);

		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		mainGames->Keyboard(key , x , y);
	}

	void mouseButton(int button, int state, int x, int y) 
	{
		mainGames->mouseButton(button, state, x, y);
	}

	void mouseMove(int x, int y)
	{
		mainGames->mouseMove(x, y);
	}

	void releaseKeyboard(unsigned char key, int x, int y)
	{
		mainGames->releaseKeyboard(key, x, y);
	}
}
