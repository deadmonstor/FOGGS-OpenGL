#include "mainGame.h"


int main(int argc, char* argv[])
{
	mainGame* game = new mainGame(argc, argv);

	return 0;
}

GLfloat xpos, ypos;

mainGame::mainGame(int argc, char* argv[])
{
	srand(time(NULL));
	InitGL(argc, argv);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	const ImGuiIO& io = ImGui::GetIO();

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

	InitObjects();
	InitLighting();

	glutMainLoop();

}
mainGame* uwu;
static void tests(int s)
{
	mainGame* game = static_cast<mainGame*>(uwu);
	game->test = true;
	glutTimerFunc(4000, tests, 0);
}

void mainGame::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0 , 0);
	glutCreateWindow("Joshua Mobley's Game");

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	uwu = this;
	glutTimerFunc(10000, tests, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 1920, 1080);
	gluPerspective(45, float(1920) / float(1080), 0.1f, 10000.0f);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glMatrixMode(GL_MODELVIEW);
	glutFullScreen();

}

void mainGame::InitObjects()
{ 
	rotation = 0;
	curCamera = new Camera();
	curCamera->eye.z = 5.0f; curCamera->up.y = 1.0f;

	Mesh* cubeMesh = MeshLoader::Instance()->Load((char *)"objects/cube.txt");
	Mesh* pyramidMesh = MeshLoader::Instance()->Load((char*)"objects/pyramid.txt");

	Texture2D* pyramidTexture = new Texture2D();
	pyramidTexture->Load((char*)"images/stars.raw", 512, 512);


	for (int i = 0; i < 10; i++)
	{
		objects.push_back(new Pyramid(pyramidMesh, pyramidTexture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, (rand() % 1000) / 10.0f, objects.size()));
	}


	Texture2D* cubeTexture = new Texture2D();
	cubeTexture->Load((char*)"images/Penguins.raw", 512, 512);

	srand(time(NULL) + 50);

	for (int i = 0; i < 100; i++)
	{
		objects.push_back(new Cube(cubeMesh, cubeTexture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, (rand() % 2000) / 10.0f, objects.size()));
	}

}

void mainGame::InitLighting()
{
	if (_lightPosition) delete _lightPosition;
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	if (_lightData) delete _lightData;
	_lightData = new lighting();
	_lightData->ambient.x = 0.7;
	_lightData->ambient.y = 0.7;
	_lightData->ambient.z = 0.7;
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

void mainGame::computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	y += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void mainGame::timerCheck()
{
	if (test)
	{
		objectToShootID = objectToShootID++;
		test = false;
	}
}

void mainGame::Update()
{
	if (deltaMove)
		computePos(deltaMove);

	glLoadIdentity();

	gluLookAt(x, y, z,
		x + lx, y - ly, z + lz,
		0.0f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	for (SceneObject* curObject : objects)
		curObject->Update();
	
	timerCheck();
	KeepCursorInBounds();
	glutPostRedisplay();
}

bool showMenu = true;

void mainGame::Keyboard(unsigned char key, int x, int y)
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

void mainGame::releaseKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w': if (deltaMove == 0.5f) deltaMove = 0; break;
		case 's': if (deltaMove == -0.5f) deltaMove = 0; break;
	}


	ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
}

void mainGame::mouseButton(int button, int state, int x, int y)
{	
	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		shouldGetPixel = true;
	}

	ImGui_ImplGLUT_MouseFunc(button, state, x, y);
}

bool isWarping = false;
int mouseExtendedX = 0;
int mouseExtendedY = 0;
void mainGame::mouseMove(int x, int y)
{

	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && !isWarping)
	{

		int useX = mouseExtendedX + x;
		int useY = mouseExtendedY + y;

		deltaAngle = (useX - angle) * 0.002f;

		lx = sin(deltaAngle);
		lz = -cos(deltaAngle);

		deltaAngle = (useY * 0.002f);
		ly = deltaAngle;

	
		if (x == 0) {

			isWarping = true;
			mouseExtendedX -= 1919 / 2;
			glutWarpPointer(1920 / 2, y);

		}else if (x == 1919) {

			isWarping = true;
			mouseExtendedX += 1919 / 2;
			glutWarpPointer(1920 / 2, y);

		}

		if (y == 0) {

			isWarping = true;
			mouseExtendedY -= 1079 / 2;
			glutWarpPointer(x, 1080 / 2);

		}else if (y == 1079) {

			isWarping = true;
			mouseExtendedY += 1079 / 2;
			glutWarpPointer(x, 1080 / 2);

		}

	}
	else if (isWarping)
	{
		isWarping = false;
	}

	ImGui_ImplGLUT_MotionFunc(x, y);
}

void GetWindowString(HWND hwnd, std::wstring& s) {
	const DWORD TITLE_SIZE = 1024;
	WCHAR windowTitle[TITLE_SIZE];

	GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

	int length = ::GetWindowTextLength(hwnd);
	wstring title(&windowTitle[0]);

	s = title;
}

void mainGame::KeepCursorInBounds()
{
	HWND hwnd = GetForegroundWindow();
	
	std::wstring x;
	GetWindowString(hwnd, x);

	if (x != L"Joshua Mobley's Game")
	{
		return;
	}

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
}

void mainGame::ShowMenu()
{
	if (showMenu)
	{

		const float DISTANCE = 10.0f;
		static int corner = 1;

		ImGuiIO& io = ImGui::GetIO();
		ImVec2 window_pos = ImVec2(io.DisplaySize.x - DISTANCE, DISTANCE);
		ImVec2 window_pos_pivot = ImVec2(1.0f, 0.0f);

		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		if (ImGui::Begin("Overlay", &showMenu, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
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

void mainGame::Display()
{

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (SceneObject* curObj : objects)
	{
		glPushMatrix();

		if (curObj->id != objectToShootID)
			curObj->Draw();
		else 
			curObj->DrawBasic();

		glPopMatrix();
	}

	ShowMenu();
	ImGui::Render();

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	//Switch to our projection mode
	glMatrixMode(GL_PROJECTION);
	//Save the rest
	glPushMatrix();
	//Start fresh
	glLoadIdentity();
	//Goto ortho mode
	gluOrtho2D(0, 1920, 0, 1080);
	//Flipp
	glScalef(1, -1, 1);
	glTranslatef(0, -1080, 0);
	//Time to draw
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//Draw

	int widthcenter = (glutGet(GLUT_WINDOW_WIDTH) / 2);
	int heightcenter = (glutGet(GLUT_WINDOW_HEIGHT) / 2);
	float sizeOfCrosshair = 3.0f;

	glBegin(GL_QUADS);
		glColor3ub(0,0,0);
		glVertex2f(widthcenter + sizeOfCrosshair, heightcenter + sizeOfCrosshair);
		glVertex2f(widthcenter + sizeOfCrosshair, heightcenter - sizeOfCrosshair);
		glVertex2f(widthcenter - sizeOfCrosshair, heightcenter - sizeOfCrosshair);
		glVertex2f(widthcenter - sizeOfCrosshair, heightcenter + sizeOfCrosshair);
	glEnd();
	glPopMatrix();

	//Switch back to our projection mode
	glMatrixMode(GL_PROJECTION);
	//Finish our calls above
	glPopMatrix();
	//Switch back to our model matrix to continue with out 3D scene
	glMatrixMode(GL_MODELVIEW);


	glFlush();
	glutSwapBuffers();

	if (shouldGetPixel)
	{
		GLdouble window_width = glutGet(GLUT_WINDOW_WIDTH);
		GLdouble window_height = glutGet(GLUT_WINDOW_HEIGHT);

		GLubyte color[4];

		glReadPixels(window_width / 2, (window_height / 2) - 4 , 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);

		int pickedID =
			color[0] +
			color[1] * 256 +
			color[2] * 256 * 256;

		printf("Clicked on pixel %f, %f, R: %i G: %i B: %i, ID: %i\n",
			xpos, ypos, color[0], color[1], color[2], pickedID);

		if (pickedID != 65280)
		{
			// Shot at wrong object/world deduct a point
			printf("Shot at wrong object/world deduct a point\n");
		}
		else
		{

			for (int i = 0; i < objects.size(); i++)
			{
				SceneObject* n = objects.at(i);

				if (n->id == objectToShootID)
				{
					objects.erase(objects.begin() + i);
					delete n;
					break;
				}
			}

		}

		shouldGetPixel = false;
	}

}

mainGame::~mainGame(void)
{

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();

}
