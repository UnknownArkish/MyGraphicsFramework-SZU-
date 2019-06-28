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

	// @TODO����ʼ��һ�����������������Ϊ�������
	m_MainCamera = MyCamera::Create();
	CameraSystem::GetInstance()->SetMainCamera(m_MainCamera);
	this->AddChildren(m_MainCamera);

	// @TODO������պ��л�ȡһ����պ�ʵ��������ӽ��Լ��ĳ�����
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
