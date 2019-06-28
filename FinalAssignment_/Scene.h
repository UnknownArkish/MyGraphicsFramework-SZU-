
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
	MyCamera * m_MainCamera;								// 主摄像机
protected:
	Scene();
	virtual bool Init();									// 初始化函数
public:
	~Scene();
	static Scene* Create();									// 创建函数

	Skybox* GetSkybox() { return m_Skybox; }
	MyCamera* GetMainCamera() { return m_MainCamera; }

	virtual void OnSceneEnter();							// 场景进入回调函数
	virtual void OnSceneExit();								// 场景退出回调函数
};


#endif // !_SCENE_H_


