
#ifndef _BASE_CONTROLLER_H_
#define _BASE_CONTROLLER_H_
#pragma once

#include"InputSystem.h"
#include"Ref.h"

/*
*	Controller类，实现了三种Listener的接口，同时已经向InputSystem注册了对应的事件
*	只需要继承Controller类并实现对应的函数即可作出操作
*/
class BaseController :public Ref, KeyboardListener, MousePassiveListener, MouseMotionListener
{
protected:
	BaseController();
	~BaseController();
	virtual bool Init();
public:
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


#endif // !_BASE_CONTROLLER_H_


