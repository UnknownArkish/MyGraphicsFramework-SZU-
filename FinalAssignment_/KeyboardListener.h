
#ifndef _KEYBOARD_LISTENER_H_
#define _KEYBOARD_LISTENER_H_
#pragma once

#include"KeyboardEventArgs.h"

class KeyboardListener {
public:
	virtual void OnKeyboardDown(KeyboardEventArgs* args) = 0;
	virtual void OnKeyboardUp(KeyboardEventArgs* args) = 0;
};



#endif // !_KEYBOARD_LISTENER_H_


