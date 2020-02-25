#include "HelloGL.h"

int main(int argc, char* argv[])
{
	HelloGL* game = new HelloGL(argc, argv);

	return 0;
}

HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));
	InitGL(argc, argv);
	InitObjects();

	glutMainLoop();

}

void HelloGL::InitGL(int argc, char* argv[])
{
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

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(1, 0);

	glMatrixMode(GL_MODELVIEW);

}

void HelloGL::InitObjects()
{
	rotation = 0;
	curCamera = new Camera();
	curCamera->eye.z = 5.0f; curCamera->up.y = 1.0f;
	//curCamera->eye.x = 5.0f; curCamera->eye.y = 5.0f; curCamera->eye.z = -5.0f;

	Mesh* cubeMesh = MeshLoader::Load((char *)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	for (int i = 0; i < 200; i++)
	{
		objects.push_back(new Pyramid(pyramidMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f));

	}

	srand(time(NULL) + 50);

	for (int i = 0; i < 200; i++)
	{
		objects.push_back(new Cube(cubeMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f));
	}

}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(curCamera->eye.x, curCamera->eye.y, curCamera->eye.z, curCamera->center.x, curCamera->center.y, curCamera->center.z, curCamera->up.x, curCamera->up.y, curCamera->up.z);
	
	for (SceneObject* n : objects)
		n->Update();

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (SceneObject* n : objects)
	{
		glPushMatrix();
			n->Draw();
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

HelloGL::~HelloGL(void)
{

}
