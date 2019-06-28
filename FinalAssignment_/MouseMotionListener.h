
#ifndef _MOUSE_MOTION_LISTENER_H_
#define _MOUSE_MOTION_LISTENER_H_
#pragma once

#include"MouseEventArgs.h"

class MouseMotionListener {
public:
	virtual bool OnMouseDown(MouseEventArgs* args) = 0;
	virtual void OnMouseMotion(MouseEventArgs* args) = 0;
	virtual void OnMouseUp(MouseEventArgs* args) = 0;
};


#endif // !_MOUSE_MOTION_LISTENER_H_


