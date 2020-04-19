#include "HelloGL.h"

int main(int argc, char* argv[])
{
	HelloGL* game = new HelloGL(argc, argv);

	return 0;
}

GLfloat xpos, ypos;

HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));
	InitGL(argc, argv);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGLUT_Init();
	ImGui_ImplGLUT_InstallFuncs();
	ImGui_ImplOpenGL2_Init();

	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::releaseKeyboard);

	glutMouseFunc(GLUTCallbacks::mouseButton);
	glutPassiveMotionFunc(GLUTCallbacks::mouseMove);

	glutSetCursor(GLUT_CURSOR_NONE);
	//glutIdleFunc(GLUTCallbacks::Display);

	InitObjects();
	InitLighting();

	glutMainLoop();

}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Simple OpenGL Program");

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 1920, 1080);
	gluPerspective(45,float(1920) / float(1080), 0.1f, 10000.0f);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glMatrixMode(GL_MODELVIEW);
	//glutFullScreen();

}

void HelloGL::InitObjects()
{
	rotation = 0;
	curCamera = new Camera();
	curCamera->eye.z = 5.0f; curCamera->up.y = 1.0f;
	//curCamera->eye.x = 5.0f; curCamera->eye.y = 5.0f; curCamera->eye.z = -5.0f;

	Mesh* cubeMesh = MeshLoader::Load((char *)"objects/cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"objects/pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);


	for (int i = 0; i < 10; i++)
	{
		objects.push_back(new Pyramid(pyramidMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, objects.size()));
	}

	srand(time(NULL) + 50);

	for (int i = 0; i < 100; i++)
	{
		objects.push_back(new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f, objects.size()));
	}

}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new lighting();
	_lightData->ambient.x = 0.2;
	_lightData->ambient.y = 0.2;
	_lightData->ambient.z = 0.2;
	_lightData->ambient.w = 1.0;
	_lightData->diffuse.x = 0.8;
	_lightData->diffuse.y = 0.8;
	_lightData->diffuse.z = 0.8;
	_lightData->diffuse.w = 1.0;
	_lightData->specular.x = 0.2;
	_lightData->specular.y = 0.2;
	_lightData->specular.z = 0.2;
	_lightData->specular.w = 1.0;

}

void HelloGL::computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	y += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void HelloGL::Update()
{
	if (deltaMove)
		computePos(deltaMove);

	glLoadIdentity();

	gluLookAt(x, y, z,
		x + lx, y - ly, z + lz,
		0.0f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	for (SceneObject* n : objects)
		n->Update();

	glutPostRedisplay();
}

bool showMenu = true;

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
		
		switch (key) {
			case 'w': deltaMove = 0.5f; break;
			case 's': deltaMove = -0.5f; break;
			case 'x': showMenu = !showMenu; break;
		}

	}

	ImGui_ImplGLUT_KeyboardFunc(key, x, y);
}

void HelloGL::releaseKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w': if (deltaMove == 0.5f) deltaMove = 0; break;
		case 's': if (deltaMove == -0.5f) deltaMove = 0; break;
	}


	ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
}

void HelloGL::mouseButton(int button, int state, int x, int y)
{	
	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		shouldGetPixel = true;
	}

	ImGui_ImplGLUT_MouseFunc(button, state, x, y);
}

bool warping = false;
int test1 = 0;
int test2 = 0;
void HelloGL::mouseMove(int x, int y)
{

	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && !warping)
	{

		int useX = test1 + x;
		int useY = test2 + y;

		deltaAngle = (useX - angle) * 0.002f;

		lx = sin(deltaAngle);
		lz = -cos(deltaAngle);

		deltaAngle = (useY * 0.002f);
		ly = deltaAngle;

		
		// Rewrite this because it works because look at it. 2am here
		if (x == 0) {
			warping = true;
			test1 -= 1919 / 2;
			glutWarpPointer(1920 / 2, y);
		}
		if (x == 1919) {
			warping = true;
			test1 += 1919 / 2;
			glutWarpPointer(1920 / 2, y);
		}
		if (y == 0) {
			warping = true;
			test2 -= 1079 / 2;
			glutWarpPointer(x, 1080 / 2);
		}
		if (y == 1079) {
			warping = true;
			test2 += 1079 / 2;
			glutWarpPointer(x, 1080 / 2);
		}

	}
	else if (warping) 
	{
		warping = false;
	}

	HWND hwnd = GetForegroundWindow();
	RECT rect;
	GetClientRect(hwnd, &rect);

	POINT ul;
	ul.x = rect.left;
	ul.y = rect.top;

	POINT lr;
	lr.x = rect.right;
	lr.y = rect.bottom;

	MapWindowPoints(hwnd, nullptr, &ul, 1);
	MapWindowPoints(hwnd, nullptr, &lr, 1);

	rect.left = ul.x;
	rect.top = ul.y;

	rect.right = lr.x;
	rect.bottom = lr.y;

	ClipCursor(&rect);

	ImGui_ImplGLUT_MotionFunc(x, y);
}

void HelloGL::ShowMenu()
{
	if (showMenu)
	{

		const float DISTANCE = 10.0f;
		static int corner = 1;
		ImGuiIO& io = ImGui::GetIO();
		if (corner != -1)
		{
			ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
			ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		}
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		if (ImGui::Begin("Overlay", &showMenu, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("Mouse Position");
			ImGui::Separator();
			if (ImGui::IsMousePosValid())
				ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
			else
				ImGui::Text("Mouse Position: <invalid>");
		}
		ImGui::End();


		ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Edit objects", &showMenu, ImGuiWindowFlags_MenuBar))
		{
			// left
			static int selected = 0;
			ImGui::BeginChild("left pane", ImVec2(150, 0), true);
			for (int i = 0; i < objects.size(); i++)
			{
				char label[128];
				char* curName = objects.at(i)->name;
				bool isEmpty = strlen(curName) == 0;

				sprintf_s(label, "Object: %s", isEmpty ? std::to_string(i).c_str() : curName);
				if (ImGui::Selectable(label, selected == i))
					selected = i;
			}
			ImGui::EndChild();
			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
			ImGui::Separator();
			if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
			{
				if (objects.size() != 0 && ImGui::BeginTabItem("Description"))
				{

					ImGui::InputText("Name", objects.at(selected)->name, IM_ARRAYSIZE(objects.at(selected)->name) );

					ImGui::InputFloat("x", &objects.at(selected)->_position.x, 0.0f, 0.0f, "%.3f");
					ImGui::InputFloat("y", &objects.at(selected)->_position.y, 0.0f, 0.0f, "%.3f");
					ImGui::InputFloat("z", &objects.at(selected)->_position.z, 0.0f, 0.0f, "%.3f");

					ImGui::Text("ID %i", objects.at(selected)->id);

					ImGui::InputInt("R", &objects.at(selected)->r);
					ImGui::InputInt("G", &objects.at(selected)->g);
					ImGui::InputInt("B", &objects.at(selected)->b);
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::EndChild();
			if (ImGui::Button("Revert")) {}
			ImGui::SameLine();
			if (ImGui::Button("Save")) {}
			ImGui::EndGroup();
		}
		ImGui::End();
	}
}

void HelloGL::Display()
{

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (SceneObject* n : objects)
	{
		glPushMatrix();
			n->DrawBasic();
		glPopMatrix();
	}

	ShowMenu();
	ImGui::Render();

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	glFlush();
	glutSwapBuffers();

	if (shouldGetPixel)
	{
		GLdouble window_width = glutGet(GLUT_WINDOW_WIDTH);
		GLdouble window_height = glutGet(GLUT_WINDOW_HEIGHT);

		GLubyte color[4];

		glReadPixels(window_width / 2, window_height / 2 , 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);

		int pickedID =
			color[0] +
			color[1] * 256 +
			color[2] * 256 * 256;

		printf("Clicked on pixel %f, %f, R: %i G: %i B: %i, ID: %i\n",
			xpos, ypos, color[0], color[1], color[2], pickedID);

		for (int i = 0; i < objects.size(); i++)
		{
			SceneObject* n = objects.at(i);

			if (n->id == pickedID)
			{
				objects.erase(objects.begin() + i);
				delete n;
				break;
			}
		}

		shouldGetPixel = false;
	}

}

HelloGL::~HelloGL(void)
{

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();

}
