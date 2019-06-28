
#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_
#pragma once

#include"Scene.h"
#include"InputSystem.h"
#include"Cube.h"
#include"Robot.h"

class TestScene :public Scene, public KeyboardListener
{
private:
	Cube * cube_;
	Robot* m_robot;
protected:
	TestScene();
public:
	~TestScene();

	static TestScene* Create();
	virtual bool Init();

	virtual void OnSceneEnter()override;
	virtual void OnSceneExit()override;

	virtual void Update(float deltaTime)override;
private:
	void ToTest();

	// Í¨¹ý KeyboardListener ¼Ì³Ð
	virtual void OnKeyboardUp(KeyboardEventArgs * args) override;
	virtual void OnKeyboardDown(KeyboardEventArgs* args)override;
};




#endif // !_TEST_SCENE_H_

