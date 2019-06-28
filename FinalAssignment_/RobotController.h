
#ifndef _ROBOT_CONTROLLER_H_
#define _ROBOT_CONTROLLER_H_
#pragma once

#include"Robot.h"
#include"CameraSystem.h"
#include"BaseController.h"

class RobotController :public BaseController
{
private:
	GLuint m_LastMouseX;
	GLuint m_LastMouseY;

	Robot * m_Robot = nullptr;
	CameraSystem* m_CameraSystem = nullptr;
protected:
	RobotController();

	virtual bool Init(Robot* robot);
public:
	~RobotController();

	static RobotController* Create(Robot* robot);

	// 通过 KeyboardListener 继承
	virtual void OnKeyboardDown(KeyboardEventArgs * args) override;
	virtual void OnKeyboardUp(KeyboardEventArgs * args) override;

	// 通过 MousePassiveListener 继承
	virtual void OnMousePassive(MouseEventArgs * args) override;

	// 通过 MouseMotionListener 继承
	virtual bool OnMouseDown(MouseEventArgs * args) override;
	virtual void OnMouseMotion(MouseEventArgs * args) override;
	virtual void OnMouseUp(MouseEventArgs * args) override;
};



#endif // !_ROBOT_CONTROLLER_H_

