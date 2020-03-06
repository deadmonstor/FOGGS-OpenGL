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
	glutMotionFunc(GLUTCallbacks::mouseMove);

	InitObjects();
	InitLighting();

	glutMainLoop();

}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
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

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glMatrixMode(GL_MODELVIEW);
	//glutFullScreen();

}

void HelloGL::InitObjects()
{
	rotation = 0;
	curCamera = new Camera();
	curCamera->eye.z = 5.0f; curCamera->up.y = 1.0f;
	//curCamera->eye.x = 5.0f; curCamera->eye.y = 5.0f; curCamera->eye.z = -5.0f;

	Mesh* cubeMesh = MeshLoader::Load((char *)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);


	for (int i = 0; i < 200; i++)
	{
		//objects.push_back(new Pyramid(pyramidMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f));
	}

	srand(time(NULL) + 50);

	for (int i = 0; i < 100; i++)
	{
		objects.push_back(new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f));
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
	z += deltaMove * lz * 0.1f;
}

void HelloGL::Update()
{
	if (deltaMove)
		computePos(deltaMove);

	glLoadIdentity();
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
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
		case 's':  if (deltaMove == -0.5f) deltaMove = 0; break;
	}


	ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
}

void HelloGL::mouseButton(int button, int state, int x, int y)
{	
	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && button == GLUT_LEFT_BUTTON) {

		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {
			xOrigin = x;
		}
	}

	ImGui_ImplGLUT_MouseFunc(button, state, x, y);
}

void HelloGL::mouseMove(int x, int y)
{
	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && xOrigin >= 0)
	{
		deltaAngle = (x - xOrigin) * 0.002f;

		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}

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
				if (ImGui::BeginTabItem("Description"))
				{

					ImGui::InputText("Name", objects.at(selected)->name, IM_ARRAYSIZE(objects.at(selected)->name) );

					ImGui::InputFloat("x", &objects.at(selected)->_position.x, 0.0f, 0.0f, "%.3f");
					ImGui::InputFloat("y", &objects.at(selected)->_position.y, 0.0f, 0.0f, "%.3f");
					ImGui::InputFloat("z", &objects.at(selected)->_position.z, 0.0f, 0.0f, "%.3f");
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

	ShowMenu();
	ImGui::Render();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (SceneObject* n : objects)
	{
		glPushMatrix();
			n->Draw();
		glPopMatrix();
	}
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	glFlush();
	glutSwapBuffers();

}

HelloGL::~HelloGL(void)
{

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();

}
