
#ifndef _CAMERA_SYSTEM_H_
#define _CAMERA_SYSTEM_H_

#pragma once

//#include<Camera_GLUT.h>
#include"MyCamera.h"
//#include"CameraNode.h"
#include"Ref.h"

class CameraSystem:public Ref
{
private:
	static CameraSystem* m_Instance;
	CameraSystem();
	~CameraSystem();
public:
	static CameraSystem* GetInstance() { return m_Instance; }
	static CameraSystem* Create();
private:
	static MyCamera* m_MainCamera;
private:
	virtual bool Init();
public:
	MyCamera * GetMainCamera() { return m_MainCamera; }
	void SetMainCamera(MyCamera* camera);
};

#endif // !_CAMERA_SYSTEM_H_


