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
	curCamera = new Camera();
	curCamera->eye.z = 1.0f;
	curCamera->up.y = 1.0f; 

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");

	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);

	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(curCamera->eye.x, curCamera->eye.y, curCamera->eye.z, curCamera->center.x, curCamera->center.y, curCamera->center.z, curCamera->up.x, curCamera->up.y, curCamera->up.z);

	if (rotation >= 360.0f)
		rotation = 0.0f;

	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w': {
			curCamera->eye.y--;
			break;
		}

		case 'a': {
			curCamera->eye.x--;
			break;
		}

		case 's': {
			curCamera->eye.y++;
			break;
		}

		case 'd': {
			curCamera->eye.x++;
			break;
		}
	}
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
			glRotatef(rotation, 1.0f, 0.0f, 0.0f);
			glutWireTeapot(0.1);
		glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void HelloGL::DrawPolygon()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
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
