#include "HelloGL.h"
#include "GLUTCallbacks.h"

int main(int argc, char* argv[])
{
	HelloGL* game = new HelloGL(argc, argv);

	return 0;
}

HelloGL::HelloGL(int argc, char* argv[])
{

	rotation = 0;

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutCreateWindow("Simple OpenGL Program");
	glutInitWindowSize(800, 800);
	glutDisplayFunc(GLUTCallbacks::Display);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glutMainLoop();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
		DrawPolygon();
	glFlush();
}

void HelloGL::Update()
{
	rotation += 0.5f;

	if (rotation >= 360.0f)
		rotation = 0.0f;

	glutPostRedisplay();
}

void HelloGL::DrawPolygon()
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.75, 0.5);
		glVertex2f(0.75, 0.5);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);
		glEnd();
	}

	glPopMatrix();
}


HelloGL::~HelloGL(void)
{

}
