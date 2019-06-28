#include "MyScene.h"

#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

#include"Cube.h"
#include"ResourcesSystem.h"
#include"CameraController.h"
#include"InputSystem.h"
#include"LightSystem.h"
#include"Robot.h"
#include"PointLight.h"
#include"Model.h"
#include"RobotAnimationController.h"

MyScene::MyScene()
{
}

bool MyScene::Init()
{
	if (!Scene::Init()) {
		return false;
	}

	InitCameraContoller();			// 初始化摄像机控制器
	InitSceneController();			
	InitSkybox();					// 初始化天空盒
	InitAmbientLight();
	//InitFlashLight();

	InitGround();					// 初始化地板
	InitFire();
	InitSnow();

	InitRobot();
	InitRobotController();

	InitModel();					// 初始化一些装饰的模型

	// 播放一段火的音效
	//PlaySound(TEXT("Resources/Audio/fire.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	return true;
}


MyScene::~MyScene()
{
}

MyScene * MyScene::Create()
{
	MyScene* pRet = new(std::nothrow)MyScene();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void MyScene::Update(float deltaTime)
{

}

void MyScene::InitCameraContoller()
{
	// @TOD：初始化摄像机
	CameraController* controller = CameraController::Create();
}

void MyScene::InitSceneController()
{
	InputSystem::GetInstance()->AddKeyboardListener(this);
}

void MyScene::InitSkybox()
{
	Skybox* skybox = this->GetSkybox();
	skybox->SetCubeMap(ResourcesSystem::GetInstance()->GetCubeMap("mnight"));
}

void MyScene::InitAmbientLight()
{
	m_AmbienLight = DirectionLight::Create();					// 创建一个方向光作为环境光源
	LightSystem::GetInstance()->AddLight(m_AmbienLight);		// 向光照系统添加这个光源
	m_AmbienLight->SetRotation(vec3(-145.0f, 0.0f, 0.0f));		// 旋转方向光
	m_AmbienLight->SetAmbient(EnvironmentAmbient);				// 设置环境光的三个分量
	m_AmbienLight->SetDiffuse(EnvironmentDiffuse);
	m_AmbienLight->SetSpecular(EnvironmentSpecular);
	this->AddChildren(m_AmbienLight);
}

void MyScene::InitFlashLight()
{
	m_FlashLight = SpotLight::Create();
	LightSystem::GetInstance()->AddLight(m_FlashLight);
	CameraSystem::GetInstance()->GetMainCamera()->AddChildren(m_FlashLight);
}


void MyScene::InitGround()
{
	int halfSize = Size_Of_Ground / 2;
	for (int x = 0; x < Size_Of_Ground; x++) {				// 控制行
		for (int z = 0; z < Size_Of_Ground; z++) {			// 控制列
			Plane* plane = Plane::Create();
			// 设置地板的贴图为ground
			plane->SetTexture(ResourcesSystem::GetInstance()->GetTexture("ground"));
			this->AddChildren(plane);						// 将其添加进我们的场景当中
			plane->SetPosition(vec3(-1.0f*halfSize + 1.0f*x, -0.0f, -1.0f*halfSize + 1.0f*z));
			plane->SetRotation(vec3(90.0f, 0.0f, 0.0f));	// 设置旋转角度
			plane->SetMaterial(Ground);						// 设置地板的材质

			m_Grounds.push_back(plane);
		}
	}
}

void MyScene::InitFire()
{
	m_Bondfire = Node::Create();

	PointLight* fixLight = PointLight::Create();
	LightSystem::GetInstance()->AddLight(fixLight);
	fixLight->SetAnchor(vec3(0.0f, -0.5f, 0.0f));
	fixLight->SetPosition(vec3(0.0f, 0.2f, 0.0f));
	fixLight->SetVisiable(false);

	fixLight->SetAmbient(FixLightAmbient);
	fixLight->SetDiffuse(FixLightDiffuse);
	fixLight->SetSpecular(FixLightSpecular);

	m_Bondfire->AddChildren(fixLight);

	float intervalScalePerCircle = 1.0 / (Circle_Num + 1);
	// 创建篝火
	for (int i = 0; i < Circle_Num; i++) {

		int fireNum = 1 + i * Interaval_Num_Fire_Per_Circle;										// 当前圈的火焰数量
		float radius = i * Radius_Per_Circle * cos(Degree2Radians(i*15.0f));						// 当前圈的半径
		float dTheta = 360.0f / fireNum;															// 当前圈火焰之间的角度差

		for (int j = 0; j < fireNum; j++) {
			float x = cos(Degree2Radians(dTheta*j)) * radius;
			float z = sin(Degree2Radians(dTheta*j)) * radius;
			
			Animator2_5D* fire;
			if (i < Maximum_Fire_Circle_Num) {
				fire = Fire::Create(ResourcesSystem::GetInstance()->GetAnimation("Fire_1"));
			}
			else {
				fire = Animator2_5D::Create(ResourcesSystem::GetInstance()->GetAnimation("Fire_1"));
			}
			fire->Start();

			float randomFactor = Tools::GetInstance()->_Random(0, fire->GetAnimationFrameSize());
			float randomFactor_0_1 = randomFactor / fire->GetAnimationFrameSize();

			fire->SetScale(vec3(1.0f - intervalScalePerCircle * i + randomFactor_0_1 / 10));
			m_Bondfire->AddChildren(fire);
			fire->SetAnchor(vec3(0.0f, -0.5f, 0.0f));
			fire->SetPosition(vec3(x + randomFactor_0_1 / 10, 0.0f, z + randomFactor_0_1 / 10));
			fire->SetFPS(12.0f + i * 2 * randomFactor_0_1, 0.01f* randomFactor);

			fire->Play(randomFactor, randomFactor + 1);
		}
	}
	m_Bondfire->SetScale(vec3(0.92f, 1.0f, 0.92f));
	this->AddChildren(m_Bondfire);
}

void MyScene::InitSnow()
{
	//Animator2_5D* snow = Animator2_5D::Create(ResourcesSystem::GetInstance()->GetAnimation("Snow_2"));
	//this->AddChildren(snow);
	//snow->SetPosition(vec3(-0.5f, 1.0f, -0.5f));
	//snow->SetFPS(4.0);
	//snow->Start();
}

void MyScene::InitRobot()
{
	// 坐着的家伙
	m_Human_Sitted = Robot::Create();
	m_Human_Sitted->SetScale(vec3(0.1f));
	m_Human_Sitted->SetMaterial(Human);
	this->AddChildren(m_Human_Sitted);
	m_Human_Sitted->SetPosition(vec3(0.8f, 0.118f, 0.8f));
	m_Human_Sitted->SetRotation(vec3(6.12f, -145.0f, 0.0f));

	m_Human_Sitted->SetUnitRotation(vec3(-12.5f, -27.5f, 0.0f),RobotUnit::Head);
	m_Human_Sitted->SetUnitRotation(vec3(-67.0f, 0.0f, 0.0f), RobotUnit::LeftUpperHand);
	m_Human_Sitted->SetUnitRotation(vec3(0.0f, 0.0f, -37.0f), RobotUnit::LeftLowerHand);
	m_Human_Sitted->SetUnitRotation(vec3(-62.0f, 0.0f, 0.0f), RobotUnit::RightUpperHand);
	m_Human_Sitted->SetUnitRotation(vec3(0.0f, 0.0f, 32.0f), RobotUnit::RightLowerHand);

	m_Human_Sitted->SetUnitRotation(vec3(-137.5f, 0.0f, 25.12f),RobotUnit::LeftUpperLeg);
	m_Human_Sitted->SetUnitRotation(vec3(78.0f, 0.0f, 0.0f),RobotUnit::LeftLowerLeg);
	m_Human_Sitted->SetUnitRotation(vec3(-125.0f, 0.0f, -24.35f), RobotUnit::RightUpperLeg);
	m_Human_Sitted->SetUnitRotation(vec3(73.0f, 0.0f, 0.0f), RobotUnit::RightLowerLeg);


	// 站着的家伙
	m_Human_Stand = Robot::Create();
	m_Human_Stand->SetScale(vec3(0.1f));
	m_Human_Stand->SetMaterial(Human);
	m_Human_Stand->SetPosition(vec3(0.678f, 0.40f, -0.716f));
	this->AddChildren(m_Human_Stand);

	m_Human_Stand->SetRotation(vec3(-6.0f, -42.0f, 0.f));

	m_Human_Stand->SetUnitRotation(vec3(12.5f, 25.0f, 0.0f),RobotUnit::Head);
	m_Human_Stand->SetUnitRotation(vec3(-0.0f, 0.0f, 3.0f), RobotUnit::LeftUpperHand);
	m_Human_Stand->SetUnitRotation(vec3(-1.0f, 0.0f, -1.3f),RobotUnit::LeftLowerHand);
	m_Human_Stand->SetUnitRotation(vec3(-0.0f, 0.0f, -9.0f),RobotUnit::RightUpperHand);
	m_Human_Stand->SetUnitRotation(vec3(-26.0f, 0.0f, 10.0f),RobotUnit::RightLowerHand);

	m_Human_Stand->SetUnitRotation(vec3(2.0f, 3.0f, 4.0),RobotUnit::LeftUpperLeg);
	m_Human_Stand->SetUnitRotation(vec3(5.113f, 0.0f, 0.0f),RobotUnit::LeftLowerLeg);
	m_Human_Stand->SetUnitRotation(vec3(2.0f, -1.3f, -4.0f),RobotUnit::RightUpperLeg);
	m_Human_Stand->SetUnitRotation(vec3(5.113f, 0.0f, 0.0f), RobotUnit::RightLowerLeg);
}

void MyScene::InitRobotController()
{
	// 设置这些家伙的动画机
	RobotAnimationController* controller = nullptr;
	controller = RobotAnimationController::Create(m_Human_Sitted, RobotUnit::LeftUpperLeg, vec3(-1.2f, 1.0f, 3.0f), 60);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Sitted, RobotUnit::RightUpperLeg, vec3(-0.8f, -1.0f, -2.6f), 60);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Sitted, RobotUnit::LeftUpperHand, vec3(0.0f, 0.0f, 2.0f), 60);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Sitted, RobotUnit::RightUpperHand, vec3(0.0f, 0.0f, -2.0f), 60);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Sitted, RobotUnit::LeftLowerLeg, vec3(2.0f, 0.0f, 0.0f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Sitted, RobotUnit::RightLowerLeg, vec3(1.6f, 0.0f, 0.0f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Sitted, RobotUnit::Head, vec3(4.6f, 0.80f, 0.0f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Sitted, RobotUnit::Body, vec3(-1.8f, 0.0f, 0.0f), 48);
	this->AddChildren(controller);

	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::Body, vec3(0.3f, 0.1f, -0.2f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::LeftUpperLeg, vec3(-2.0f, 0.0f, -0.5f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::LeftLowerLeg, vec3(4.0f, 0.0f, 1.43f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::RightUpperLeg, vec3(1.8f, 0.0f, 0.23f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::RightLowerLeg, vec3(-4.2f, 0.0f, -0.8f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::Head, vec3(-4.16f, 0.3f, 0.0f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::LeftUpperHand, vec3(0.0f, 0.6f, 1.6f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::RightLowerHand, vec3(5.12f, 2.3f, 0.0f), 48);
	this->AddChildren(controller);
	controller = RobotAnimationController::Create(m_Human_Stand, RobotUnit::RightUpperHand, vec3(0.0f, 0.0f, -1.3f), 48);
	this->AddChildren(controller);
}

void MyScene::InitModel()
{
	float fireSize = Circle_Num * Radius_Per_Circle + 0.1f;
	int halt_Size = 1.0f * Size_Of_Ground / 2;

	// 建立草的模型
	for (int i = 0; i < Grass_Num; i++) {

		float z = Tools::GetInstance()->_Random(-halt_Size * Dense_Level, halt_Size * Dense_Level);
		float x = Tools::GetInstance()->_Random(-halt_Size * Dense_Level, halt_Size * Dense_Level);
		if (z >= -fireSize && z <= fireSize && x >= -fireSize && x <= fireSize) {
			i--;
			continue;
		}

		float r = Tools::GetInstance()->_Random(-_RShakeFactor, _RShakeFactor);
		float g = Tools::GetInstance()->_Random(-_GShakeFactor, _GShakeFactor);
		float b = Tools::GetInstance()->_Random(-_BShakeFactor, _BShakeFactor);
		Material material = Grass;
		material.Ambient += vec3(r, g, b);
		material.Diffuse += vec3(r, g, b);

		Model* grass = Model::Create(ResourcesSystem::GetInstance()->GetModelResource("grass"), material);
		this->AddChildren(grass);
		grass->SetScale(vec3(0.001f) + sin(i)*Tools::GetInstance()->_Random(-0.0005f, 0.0005f));
		grass->SetPosition(vec3(x, 0.0f, z));

		float rotateNoise = Tools::GetInstance()->_Random(-71.0f, 71.0f);
		grass->SetRotation(vec3(0.0f, (x + z)*rotateNoise, 0.0f));
	}
	for (int i = 0; i < GrassPath_Num; i++) {
		int numNoise = Tools::GetInstance()->_Random(0, 3);						// 草丛中草个数噪音
		int radiusNoise = Tools::GetInstance()->_Random(-0.05f, 0.05f);			// 草丛半径噪音
		float radius = GrassPathRadius + radiusNoise;

		// 草丛的中心位置
		float z = Tools::GetInstance()->_Random(-halt_Size * Dense_Level, halt_Size * Dense_Level);
		float x = Tools::GetInstance()->_Random(-halt_Size * Dense_Level, halt_Size * Dense_Level);
		if (z >= -fireSize && z <= fireSize && x >= -fireSize && x <= fireSize) {
			i--;
			continue;
		}

		for (int j = 0; j < GrassPath_Per_Grass_Num + numNoise; j++) {
			float rotateNoise = Tools::GetInstance()->_Random(-71.0f, 71.0f);

			float _z = cos(Degree2Radians(Tools::GetInstance()->_Random())) * radius * Dense_Level + z;
			float _x = sin(Degree2Radians(Tools::GetInstance()->_Random())) * radius * Dense_Level + x;

			float r = Tools::GetInstance()->_Random(-_RShakeFactor, _RShakeFactor);
			float g = Tools::GetInstance()->_Random(-_GShakeFactor, _GShakeFactor);
			float b = Tools::GetInstance()->_Random(-_BShakeFactor, _BShakeFactor);
			Material material = Grass;
			material.Ambient += vec3(r, g, b);
			material.Diffuse += vec3(r, g, b);

			Model* grass = Model::Create(ResourcesSystem::GetInstance()->GetModelResource("grass"), material);
			//grass->SetMaterial(Ground);
			this->AddChildren(grass);
			grass->SetPosition(vec3(_x, 0.0f, _z));
			grass->SetScale(vec3(0.0007f) + sin(j)*Tools::GetInstance()->_Random(-0.0005f, 0.0005f));
			grass->SetRotation(vec3(0.0f, (_x + _z)*rotateNoise, 0.0f));
		}
	}

	// 树的模型
	for (int i = 0; i < Tree_Num; i++) {

		float z = Tools::GetInstance()->_Random(-halt_Size * Dense_Level, halt_Size * Dense_Level);
		float x = Tools::GetInstance()->_Random(-halt_Size * Dense_Level, halt_Size * Dense_Level);
		if (z >= -fireSize && z <= fireSize && x >= -fireSize && x <= fireSize) {
			i--;
			continue;
		}

		float rotateNoise = Tools::GetInstance()->_Random(-180.0f, 180.0f);
		float scaleNoise = Tools::GetInstance()->_Random(-0.06f, 0.06f);

		float r = Tools::GetInstance()->_Random(-_RShakeFactor, _RShakeFactor);
		float g = Tools::GetInstance()->_Random(-_GShakeFactor, _GShakeFactor);
		float b = Tools::GetInstance()->_Random(-_BShakeFactor, _BShakeFactor);
		Material material = Tree;
		material.Ambient += vec3(r, g, b);
		material.Diffuse += vec3(r, g, b);

		Model* tree = Model::Create(ResourcesSystem::GetInstance()->GetModelResource("tree"), material);
		tree->SetScale(vec3(0.16f + scaleNoise));
		tree->SetPosition(vec3(x, 0.0f, z));
		tree->SetRotation(vec3(0.0f, rotateNoise*i, 0.0f));
		this->AddChildren(tree);
	}


	// 石头的模型
	float dThta_Stone = 360.0f / Stone_Num;					// 每块石头的角度
	for (int i = 0; i < Stone_Num; i++) {
		float z = sin(Degree2Radians(dThta_Stone*i)) * (fireSize - Radius_Per_Circle) * Dense_Level;
		float x = cos(Degree2Radians(dThta_Stone*i)) * (fireSize - Radius_Per_Circle) * Dense_Level;

		float rotateNoise = Tools::GetInstance()->_Random(-180.0f, 180.0f);
		float scaleNoise = Tools::GetInstance()->_Random(-0.08f, 0.08f);

		Model* stone = Model::Create(ResourcesSystem::GetInstance()->GetModelResource("stone"));
		stone->SetScale(vec3(0.5f + scaleNoise));
		stone->SetRotation(vec3(138.0f, 0.0f, 0.0f));
		stone->SetPosition(vec3(x, 0.1f, z));
		this->AddChildren(stone);
	}

	// 椅子的模型
	Model* chair = Model::Create(ResourcesSystem::GetInstance()->GetModelResource("chair_1"),MaterialPreSet::Black_plastic);
	chair->SetScale(vec3(0.00043f));
	chair->SetRotation(vec3(-90.0f, 0.0f, 148.5f));
	chair->SetPosition(vec3(-0.612f, 0.0f, 0.716f));
	this->AddChildren(chair);
}


void MyScene::OnKeyboardDown(KeyboardEventArgs * args)
{
	// 如果为esc键，则退出程序
	if (args->Key == VK_ESCAPE) {
		exit(EXIT_SUCCESS);
	}
}

void MyScene::OnKeyboardUp(KeyboardEventArgs * args)
{
}
