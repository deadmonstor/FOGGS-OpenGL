#pragma once
class HelloGL;

namespace GLUTCallbacks
{

	void Init(HelloGL* gl);
	void Timer(int preferredRefresh);
	void Display();

}
