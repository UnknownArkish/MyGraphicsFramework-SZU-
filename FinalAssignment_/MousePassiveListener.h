

#ifndef _MOUSE_PASSIVE_LISTENER_H_
#define _MOUSE_PASSIVE_LISTENER_H_
#pragma once

#include"MouseEventArgs.h"

class MousePassiveListener {
public:
	virtual void OnMousePassive(MouseEventArgs* args) = 0;
};


#endif // !_MOUSE_PASSIVE_LISTENER_H_


