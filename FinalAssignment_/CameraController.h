
#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_
#pragma once

#include"BaseController.h"
#include"CameraSystem.h"

class CameraController :public BaseController
{
private:
	GLboolean m_IsFirstKeyDown;
	GLuint m_LastMouseX;
	GLuint m_LastMouseY;
private:
	CameraSystem * m_CameraSystem = nullptr;
protected:
	CameraController();
	~CameraController();
public:
	static CameraController* Create();
	virtual bool Init();

	virtual void OnKeyboardDown(KeyboardEventArgs* args) override;
	virtual void OnKeyboardUp(KeyboardEventArgs* args)override;

	virtual void OnMousePassive(MouseEventArgs* args) override;
	virtual bool OnMouseDown(MouseEventArgs * args) override;
	virtual void OnMouseMotion(MouseEventArgs * args) override;
	virtual void OnMouseUp(MouseEventArgs * args) override;
	
};


#endif // !_CAMERA_CONTROLLER_H_



