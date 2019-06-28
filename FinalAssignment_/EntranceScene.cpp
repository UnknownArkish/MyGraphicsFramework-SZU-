#include "EntranceScene.h"


#include"Game.h"
#include"TestScene.h"
#include"ResourcesSystem.h"
#include"MyScene.h"

bool EntranceScene::Init()
{
	if (!Scene::Init()) {
		return false;
	}

	// @TODO����������г�ʼ��
	//glutSetCursor(GLUT_CURSOR_NONE);											// ���ع��
	vec2 screenSize = Game::GetInstance()->GetWindowSize();
	Game::GetInstance()->SetCursorPosition(screenSize / 2);

	// ��������У���ͼ��ģ�͡���Ƶ����Դ��Ԥ����
	ResourcesSystem::GetInstance()->LoadModel("Resources/Model/grass/grass.fbx", "grass");
	ResourcesSystem::GetInstance()->LoadModel("Resources/Model/tree/tree.obj", "tree");
	ResourcesSystem::GetInstance()->LoadModel("Resources/Model/chair_1/file.fbx", "chair_1");
	ResourcesSystem::GetInstance()->LoadModel("Resources/Model/stone/scene.gltf", "stone");

	ResourcesSystem::GetInstance()->LoadCubeMap("Resources/Texture/Skybox/iceflow","iceflow");
	ResourcesSystem::GetInstance()->LoadCubeMap("Resources/Texture/Skybox/mnight", "mnight");
	std::vector<std::string> faces{
		"Resources/Texture/Ground/ground.jpg",
		"Resources/Texture/Ground/ground.jpg",
		"Resources/Texture/Ground/ground.jpg",
		"Resources/Texture/Ground/ground.jpg",
		"Resources/Texture/Ground/ground.jpg",
		"Resources/Texture/Ground/ground.jpg",
	};
	ResourcesSystem::GetInstance()->LoadCubeMap(faces, "ground");

	ResourcesSystem::GetInstance()->LoadTexture("Resources/Texture/Ground/ground.jpg", "", "ground");


	ResourcesSystem::GetInstance()->LoadAnimation("Resources/Texture/Fire/Fire_1", "Fire_1");
	ResourcesSystem::GetInstance()->LoadAnimation("Resources/Texture/Fire/Fire_2", "Fire_2");
	ResourcesSystem::GetInstance()->LoadAnimation("Resources/Texture/Fire/Fire_3", "Fire_3");
	ResourcesSystem::GetInstance()->LoadAnimation("Resources/Texture/Snow/Snow_1", "Snow_1");
	ResourcesSystem::GetInstance()->LoadAnimation("Resources/Texture/Snow/Snow_2", "Snow_2");


	// @TODO�������������Ҫ���صĵ�һ������
	Game::GetInstance()->EnterScene(MyScene::Create());

	return true;
}

EntranceScene::EntranceScene()
{
}

EntranceScene::~EntranceScene()
{
}

EntranceScene * EntranceScene::Create()
{
	EntranceScene* pRet = new (std::nothrow)EntranceScene();
	if (pRet&&pRet->Init()) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}
