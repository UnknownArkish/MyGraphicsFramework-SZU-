#include "Game.h"


#include"CameraSystem.h"
#include"LightSystem.h"
#include"InputSystem.h"
#include"ResourcesSystem.h"

#include"CubeRenderer.h"
#include"PlaneRenderer.h"
#include"Skybox.h"

#include"EntranceScene.h"
#include"GameModel.h"

Game* Game::m_Instance = new Game();
GLuint Game::Window;
GLuint Game::m_BaseTime;
GLboolean Game::m_IsStart = GL_FALSE;
Scene* Game::m_CurrentScene = nullptr;

Game::Game()
{
}


Game::~Game()
{
}

void Game::KeyboardDown(unsigned char key, int x, int y)
{
	InputSystem::GetInstance()->KeyboardDown(key, x, y);
	glutPostRedisplay();
}

void Game::KeyboardUp(unsigned char key, int x, int y)
{
	InputSystem::GetInstance()->KeyboardUp(key, x, y);
	glutPostRedisplay();
}

void Game::Mouse(int button, int state, int x, int y)
{
	InputSystem::GetInstance()->Mouse(button, state, x, y);
	glutPostRedisplay();
}

void Game::Motion(int x, int y)
{
	InputSystem::GetInstance()->Motion(x, y);
	glutPostRedisplay();
}

void Game::Passive(int x, int y)
{
	InputSystem::GetInstance()->Passive(x, y);
	glutPostRedisplay();
}

void Game::Display()
{
	glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint startTime = glutGet(GLUT_ELAPSED_TIME);						// ���Լ���ÿ֮֡���ʱ���
	Update(m_CurrentScene);												// ���³����µ�Update��Ϣ
	if (m_CurrentScene != nullptr) {
		m_CurrentScene->Display();										// Ȼ����г����Ļ���
	}
	GLuint endTime = glutGet(GLUT_ELAPSED_TIME);

	glutSwapBuffers();
	GameModel::DeltaTime = (GLfloat)(endTime - startTime) / 1000;		// ����GameModel�е�DeltaTime
}

void Game::Idle()
{
	GLuint time = glutGet(GLUT_ELAPSED_TIME);
	//GLfloat dTime = ((GLfloat)(time - m_BaseTime)) / 1000.0f;
	//// �ض�֡��ʱ���½��л���
	//if (dTime >= GameModel::DeltaTime) {
	//	Display();
	//	m_BaseTime = time;
	//}
}

void Game::Update(Node * node)
{
	static float deltaTime = GameModel::DeltaTime;
	node->ToUpdate(deltaTime);
	//// ÿ֡����һ�ε�ǰ���������нڵ��Update����
	//std::vector<Node*> temp = node->GetAllChilder();
	//for (Node* children : temp) {
	//	children->Update(deltaTime);
	//}
}


void Game::Init()
{
	// @TODO����ʼ��ϵͳ����
	InitEnvironment();
	// @TODO����ʼ��ϵͳ���
	InitFramework();
	// @TODO����ʼ����Դ
	InitResources();
	// @TODO����ʼ�����ڿ�����ϵ���
	InitMiscellaneous();

	// @TODO����ʼ����ʼ�ĳ���
	delete EntranceScene::Create();
}

void Game::InitEnvironment()
{
	// @TODO����ʼ��Game
	GLfloat FPS = Config::FPS;
	GameModel::FPS = FPS;
	GameModel::DeltaTime = 1.0 / FPS;
}

void Game::InitFramework()
{
	CameraSystem::Create();			// ��ʼ�������ϵͳ
	LightSystem::Create();			// ��ʼ������ϵͳ
	InputSystem::Create();			// ��ʼ������ϵͳ
	ResourcesSystem::Create();		// ��ʼ����Դ����ϵͳ
}

void Game::InitResources()
{
	InitShader();
	InitTexture();
}

void Game::InitShader()
{
	// @TODO��������ɫ��
	ResourcesSystem::GetInstance()->
		LoadShader("Resources/Shader/CubeShader.vs", "Resources/Shader/CubeShader.fs", nullptr, "CubeShader");
	//ResourcesSystem::GetInstance()->
	//	LoadShader("Resources/Shader/GeneralShader.vs", "Resources/Shader/GeneralShader.fs", nullptr, "GeneralShader");
	ResourcesSystem::GetInstance()->
		LoadShader("Resources/Shader/ModelShader.vs", "Resources/Shader/ModelShader.fs", nullptr, "ModelShader");
	ResourcesSystem::GetInstance()->
		LoadShader("Resources/Shader/SkyboxShader.vs", "Resources/Shader/SkyboxShader.fs", nullptr, "SkyboxShader");
	ResourcesSystem::GetInstance()->
		LoadShader("Resources/Shader/PlaneShader.vs", "Resources/Shader/PlaneShader.fs", nullptr, "PlaneShader");
}

void Game::InitTexture()
{
	// @TODO��������ͼ����պе�
	std::vector<std::string> defaultSkybox{
		"Resources/Texture/Skybox/Demo/right.jpg",
		"Resources/Texture/Skybox/Demo/left.jpg",
		"Resources/Texture/Skybox/Demo/top.jpg",
		"Resources/Texture/Skybox/Demo/bottom.jpg",
		"Resources/Texture/Skybox/Demo/front.jpg",
		"Resources/Texture/Skybox/Demo/back.jpg",
	};
	ResourcesSystem::GetInstance()->LoadCubeMap(defaultSkybox, "DefaultSkybox");		// ����Ĭ�ϵ���պ�

	ResourcesSystem::GetInstance()->LoadTexture("Resources/Texture/TestTexture.jpg", "", "TestTexture");
}

void Game::InitMiscellaneous()
{
	// @TODO����ʼ��һЩ���ڿ���ϵ�ϵͳ

	CubeRenderer::Create();			// ��ʼ��������Ⱦ��
	PlaneRenderer::Create();		// ��ʼ��ƽ����Ⱦ��
	Skybox::Create();				// ��ʼ����պ�ϵͳ
}

void Game::StartGame()
{
	if (m_IsStart == GL_TRUE)	return;

	m_IsStart = GL_TRUE;
	// @TODO����ʼ��ʱ#include
	m_BaseTime = GetRunTime();
}


void Game::EnterScene(Scene * scene)
{
	if (scene == nullptr || m_CurrentScene == scene) {
		return;
	}
	if (m_CurrentScene != nullptr) {						// ִ�г����˳��Ļص�
		m_CurrentScene->OnSceneExit();
	}

	// @TOOD���������ϵͳ���Ѿ�ע���Listener
	// @TODO����չ���ϵͳ�����еĹ���

	m_CurrentScene = scene;									
	m_CurrentScene->OnSceneEnter();							// ִ�г�������Ļص�
}

void Game::SetCursorPosition(vec2 pos)
{
	vec2 viewportPos = GetWindowPosition();
	int x = viewportPos.x + pos.x;
	int y = viewportPos.y + pos.y;
	SetCursorPos(x, y);
}

vec2 Game::GetWindowPosition()
{
	int posX = glutGet(GLUT_WINDOW_X);
	int posY = glutGet(GLUT_WINDOW_Y);
	return vec2(posX, posY);
}

vec2 Game::GetWindowSize()
{
	int screenWidth = glutGet(GLUT_WINDOW_WIDTH);
	int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
	return vec2(screenWidth, screenHeight);
}

GLuint Game::GetRunTime()
{
	return glutGet(GLUT_ELAPSED_TIME);
}
