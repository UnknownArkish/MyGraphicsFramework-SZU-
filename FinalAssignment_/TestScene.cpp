#include "TestScene.h"

#include"TestKeyboardListener.h"
#include"TestMouseListener.h"
#include"Cube.h"
#include"Model.h"

#include"LightSystem.h"
#include"PointLight.h"
#include"DirectionLight.h"
#include"SpotLight.h"

#include"ResourcesSystem.h"

#include"CameraController.h"

#include"Robot.h"
#include"RobotController.h"

#include"PlaneRenderer.h"
#include"Plane.h"

#include"Animator2D.h"
#include"Animator2_5D.h"

#include"Fire.h"

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

TestScene * TestScene::Create()
{
	TestScene* pRet = new(std::nothrow)TestScene();
	if (pRet&& pRet->Init()) {
		return pRet;
	}
	delete pRet;
	return nullptr;
}

bool TestScene::Init()
{
	if (!Scene::Init()) {
		return false;
	}

	ToTest();
	InputSystem::GetInstance()->AddKeyboardListener(this);

	return true;
}

void TestScene::OnSceneEnter()
{
	std::cout << "OnSceneEnter" << std::endl;
}

void TestScene::OnSceneExit()
{
	std::cout << "OnSceneExit" << std::endl;
}

void TestScene::Update(float deltaTime)
{
	//std::cout << "Update" << std::endl;
	//PlaneRenderer::GetInstance()->Render(vec3(-1.0f, 1.0f, 1.0f));
}

void TestScene::OnKeyboardDown(KeyboardEventArgs * args)
{
	//if (args->Key == 'z') {
	//	cube_->ToRotate(vec3(0.0f, 0.0f, 15.0f));
	//}
	//else if (args->Key == 'x') {
	//	cube_->ToRotate(vec3(15.0f, 0.0f, 0.0f));
	//}
	//else if (args->Key == 'y') {
	//	cube_->ToRotate(vec3(0.0f, 15.0f, 0.0f));
	//}
}

void TestScene::ToTest()
{
	// @DEBUG
	TestKeyboardListener* test = new TestKeyboardListener();
	//TestMouseListener* test_ = new TestMouseListener();

	// @TOD：初始化摄像机
	CameraController* controller = CameraController::Create();

	Cube* cube = Cube::Create();
	cube->ToTranslate(vec3(0.0, 0.0, 0.0f));
	cube->SetAnchor(vec3(0.0f, 0.0f, 0.5f));
	cube->ToRotate(vec3(0.0f, 0.0f, 30.0f));
	//cube->SetCubeMap(ResourcesSystem::GetInstance()->GetCubeMap("iceflow"));
	//cube->SetScale(vec3(2.0f, 2.0f, 2.0f));

	cube_ = Cube::Create();
	cube->AddChildren(cube_);
	cube_->ToTranslate(vec3(1.0f, -1.0f, 0.0f));
	cube_->ToRotate(vec3(0.0f, 0.0f, -30.0f));

	this->AddChildren(cube);
	//this->ToTranslate(vec3(0.0f, 0.5f, 0.0f));

	// 添加灯光
	PointLight* point = PointLight::Create();
	point->SetPosition(vec3(1.0f, 1.0f, 1.0));
	LightSystem::GetInstance()->AddLight(point);
	this->AddChildren(point);

	DirectionLight* directionLight = DirectionLight::Create();
	directionLight->SetPosition(vec3(0.0f, 0.0f, 5.0f));
	directionLight->ToRotate(vec3(30.0f, 0.0f, 0.0f));
	directionLight->SetVisiable(true);
	LightSystem::GetInstance()->AddLight(directionLight);
	this->AddChildren(directionLight);

	SpotLight* spot = SpotLight::Create();
	LightSystem::GetInstance()->AddLight(spot);
	this->GetMainCamera()->AddChildren(spot);

	//Model* nanosuit = Model::Create(ResourcesSystem::GetInstance()->GetModelResource("nanosuit"));
	//nanosuit->SetScale(vec3(0.2f, 0.2f, 0.2f));
	//this->AddChildren(nanosuit);


	//CubeMap* skybox = ResourcesSystem::GetInstance()->GetCubeMap("TestSkybox");
	//// 天空盒
	//Cube* skyBox = Cube::Create();
	//skyBox->SetCubeMap(skybox);
	//this->AddChildren(skyBox);

	// 设置天空盒为其他的！
	Skybox* skybox = this->GetSkybox();
	skybox->SetCubeMap(ResourcesSystem::GetInstance()->GetCubeMap("mnight"));

	m_robot = Robot::Create();
	//m_robot->SetPosition(vec3(0.0f, 0.0f, 1.0f));
	m_robot->SetScale(vec3(0.1f, 0.1f, 0.1f));
	this->AddChildren(m_robot);

	//m_MainCamera->SetPosition(vec3(0.0f, 0.5f, -0.5f));
	//m_robot->AddChildren(m_MainCamera);
	//m_robot->SetCameraAsEye(m_MainCamera);
	//RobotController* controller = RobotController::Create(this->m_robot);

	Plane* plane = Plane::Create();
	plane->SetPosition(vec3(-1.0f, 1.0f, 1.0f));
	plane->SetTexture(ResourcesSystem::GetInstance()->GetTexture("TestTexture"));
	this->AddChildren(plane);
	plane = Plane::Create();
	plane->SetPosition(vec3(-1.0f, 1.0f, 1.0f));
	plane->SetRotation(vec3(0.0f, 90.0f, 0.0f));
	plane->SetTexture(ResourcesSystem::GetInstance()->GetTexture("TestTexture"));
	this->AddChildren(plane);

	//std::vector<Texture*> animation{
	//	ResourcesSystem::GetInstance()->GetTexture("TestTexture")
	//};

	Animator2D* animator = Animator2D::Create(ResourcesSystem::GetInstance()->GetAnimation("Fire_1"));
	animator->Start();
	this->AddChildren(animator);

	Animator2_5D* animator2_5D = Animator2_5D::Create(ResourcesSystem::GetInstance()->GetAnimation("Fire_1"));
	animator2_5D->Start();
	animator2_5D->SetFPS(12.0f, 0.15f);
	animator2_5D->SetPosition(vec3(1.0f, 1.0f, 2.0f));
	this->AddChildren(animator2_5D);

	Fire* fire = Fire::Create(ResourcesSystem::GetInstance()->GetAnimation("Fire_1"));
	fire->SetPosition(vec3(1.0f, 1.0f, -1.0f));
	this->AddChildren(fire);
}

void TestScene::OnKeyboardUp(KeyboardEventArgs * args)
{
}
