
#ifndef _SCENE_H_
#define _SCENE_H_
#pragma once

#include"Node.h"
#include"CameraSystem.h"
#include"Skybox.h"

class Scene :public Node
{
private:
	Skybox * m_Skybox;
	MyCamera * m_MainCamera;								// �������
protected:
	Scene();
	virtual bool Init();									// ��ʼ������
public:
	~Scene();
	static Scene* Create();									// ��������

	Skybox* GetSkybox() { return m_Skybox; }
	MyCamera* GetMainCamera() { return m_MainCamera; }

	virtual void OnSceneEnter();							// ��������ص�����
	virtual void OnSceneExit();								// �����˳��ص�����
};


#endif // !_SCENE_H_


