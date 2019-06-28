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

	GLuint startTime = glutGet(GLUT_ELAPSED_TIME);						// 用以计算每帧之间的时间差
	Update(m_CurrentScene);												// 更新场景下的Update信息
	if (m_CurrentScene != nullptr) {
		m_CurrentScene->Display();										// 然后进行场景的绘制
	}
	GLuint endTime = glutGet(GLUT_ELAPSED_TIME);

	glutSwapBuffers();
	GameModel::DeltaTime = (GLfloat)(endTime - startTime) / 1000;		// 更新GameModel中的DeltaTime
}

void Game::Idle()
{
	GLuint time = glutGet(GLUT_ELAPSED_TIME);
	//GLfloat dTime = ((GLfloat)(time - m_BaseTime)) / 1000.0f;
	//// 特定帧率时间下进行绘制
	//if (dTime >= GameModel::DeltaTime) {
	//	Display();
	//	m_BaseTime = time;
	//}
}

void Game::Update(Node * node)
{
	static float deltaTime = GameModel::DeltaTime;
	node->ToUpdate(deltaTime);
	//// 每帧调用一次当前场景下所有节点的Update函数
	//std::vector<Node*> temp = node->GetAllChilder();
	//for (Node* children : temp) {
	//	children->Update(deltaTime);
	//}
}


void Game::Init()
{
	// @TODO：初始化系统配置
	InitEnvironment();
	// @TODO：初始化系统框架
	InitFramework();
	// @TODO：初始化资源
	InitResources();
	// @TODO：初始化基于框架以上的类
	InitMiscellaneous();

	// @TODO：初始化初始的场景
	delete EntranceScene::Create();
}

void Game::InitEnvironment()
{
	// @TODO：初始化Game
	GLfloat FPS = Config::FPS;
	GameModel::FPS = FPS;
	GameModel::DeltaTime = 1.0 / FPS;
}

void Game::InitFramework()
{
	CameraSystem::Create();			// 初始化摄像机系统
	LightSystem::Create();			// 初始化光照系统
	InputSystem::Create();			// 初始化输入系统
	ResourcesSystem::Create();		// 初始化资源管理系统
}

void Game::InitResources()
{
	InitShader();
	InitTexture();
}

void Game::InitShader()
{
	// @TODO：加载着色器
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
	// @TODO：加载贴图和天空盒等
	std::vector<std::string> defaultSkybox{
		"Resources/Texture/Skybox/Demo/right.jpg",
		"Resources/Texture/Skybox/Demo/left.jpg",
		"Resources/Texture/Skybox/Demo/top.jpg",
		"Resources/Texture/Skybox/Demo/bottom.jpg",
		"Resources/Texture/Skybox/Demo/front.jpg",
		"Resources/Texture/Skybox/Demo/back.jpg",
	};
	ResourcesSystem::GetInstance()->LoadCubeMap(defaultSkybox, "DefaultSkybox");		// 加载默认的天空盒

	ResourcesSystem::GetInstance()->LoadTexture("Resources/Texture/TestTexture.jpg", "", "TestTexture");
}

void Game::InitMiscellaneous()
{
	// @TODO：初始化一些基于框架上的系统

	CubeRenderer::Create();			// 初始化方块渲染器
	PlaneRenderer::Create();		// 初始化平面渲染器
	Skybox::Create();				// 初始化天空盒系统
}

void Game::StartGame()
{
	if (m_IsStart == GL_TRUE)	return;

	m_IsStart = GL_TRUE;
	// @TODO：开始计时#include
	m_BaseTime = GetRunTime();
}


void Game::EnterScene(Scene * scene)
{
	if (scene == nullptr || m_CurrentScene == scene) {
		return;
	}
	if (m_CurrentScene != nullptr) {						// 执行场景退出的回调
		m_CurrentScene->OnSceneExit();
	}

	// @TOOD：清空输入系统中已经注册的Listener
	// @TODO：清空光照系统中已有的光照

	m_CurrentScene = scene;									
	m_CurrentScene->OnSceneEnter();							// 执行场景进入的回调
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
