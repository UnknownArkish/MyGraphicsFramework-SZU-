
#ifndef _BASE_CONTROLLER_H_
#define _BASE_CONTROLLER_H_
#pragma once

#include"InputSystem.h"
#include"Ref.h"

/*
*	Controller�࣬ʵ��������Listener�Ľӿڣ�ͬʱ�Ѿ���InputSystemע���˶�Ӧ���¼�
*	ֻ��Ҫ�̳�Controller�ಢʵ�ֶ�Ӧ�ĺ���������������
*/
class BaseController :public Ref, KeyboardListener, MousePassiveListener, MouseMotionListener
{
protected:
	BaseController();
	~BaseController();
	virtual bool Init();
public:
	// ͨ�� KeyboardListener �̳�
	virtual void OnKeyboardDown(KeyboardEventArgs * args) override;
	virtual void OnKeyboardUp(KeyboardEventArgs * args) override;

	// ͨ�� MousePassiveListener �̳�
	virtual void OnMousePassive(MouseEventArgs * args) override;

	// ͨ�� MouseMotionListener �̳�
	virtual bool OnMouseDown(MouseEventArgs * args) override;
	virtual void OnMouseMotion(MouseEventArgs * args) override;
	virtual void OnMouseUp(MouseEventArgs * args) override;
};


#endif // !_BASE_CONTROLLER_H_


