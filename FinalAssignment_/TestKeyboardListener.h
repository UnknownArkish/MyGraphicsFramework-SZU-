
#ifndef _TEST_KEYBOARD_LISTENER_H_
#define _TEST_KEYBOARD_LISTENER_H_
#pragma once

#include"KeyboardListener.h"
#include"stdafx.h"

class TestKeyboardListener:KeyboardListener
{
public:
	TestKeyboardListener();
	~TestKeyboardListener();

	// 通过 KeyboardListener 继承
	//virtual void OnKeyboardDown(unsigned char key, int x, int y) override;
	//virtual void OnKeyboardUp(unsigned char key, int x, int y) override;

	// 通过 KeyboardListener 继承
	virtual void OnKeyboardDown(KeyboardEventArgs * args) override;
	virtual void OnKeyboardUp(KeyboardEventArgs * args) override;
};

#endif // !_TEST_KEYBOARD_LISTENER_H_




