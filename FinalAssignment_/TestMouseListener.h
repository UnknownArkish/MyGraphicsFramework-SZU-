
#ifndef _TEST_MOUSE_LISTENER_H_
#define _TEST_MOUSE_LISTENER_H_
#pragma once

#include"MouseMotionListener.h"
#include"MousePassiveListener.h"

class TestMouseListener :public MouseMotionListener,MousePassiveListener
{
public:
	TestMouseListener();
	~TestMouseListener();

	// ͨ�� MouseListener �̳�
	virtual bool OnMouseDown(MouseEventArgs * args) override;
	virtual void OnMouseMotion(MouseEventArgs * args) override;
	virtual void OnMouseUp(MouseEventArgs * args) override;

	// ͨ�� MousePassiveListener �̳�
	virtual void OnMousePassive(MouseEventArgs * args) override;
};




#endif // !_TEST_MOUSE_LISTENER_H_

