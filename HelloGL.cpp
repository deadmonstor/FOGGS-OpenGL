#include "HelloGL.h"
#include "GLUTCallbacks.h"

int main(int argc, char* argv[])
{
	HelloGL* game = new HelloGL(argc, argv);

	return 0;
}

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutCreateWindow("Simple OpenGL Program");
	glutInitWindowSize(800, 800);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
		DrawPolygon();
	glFlush();
}

void HelloGL::DrawPolygon()
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.75, 0.5);
		glVertex2f(0.75, 0.5);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);
		glEnd();
	}
}


HelloGL::~HelloGL(void)
{

}
