#include "stdafx.h"
#include "Scene.h"

#include"Skybox.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

Scene * Scene::Create()
{
	Scene* pRet = new(std::nothrow)Scene();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	return nullptr;
}

bool Scene::Init()
{
	if (!Node::Init()) {
		return false;
	}

	// @TODO：初始化一个摄像机，并设置其为主摄像机
	m_MainCamera = MyCamera::Create();
	CameraSystem::GetInstance()->SetMainCamera(m_MainCamera);
	this->AddChildren(m_MainCamera);

	// @TODO：从天空盒中获取一个天空盒实例，并添加进自己的场景下
	m_Skybox = Skybox::GetInstance();
	this->AddChildren(m_Skybox);

	return true;
}

void Scene::OnSceneEnter()
{
}

void Scene::OnSceneExit()
{
}
