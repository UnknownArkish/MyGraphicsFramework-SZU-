
#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_
#pragma once

#include"KeyboardListener.h"
#include"MouseMotionListener.h"
#include"MousePassiveListener.h"
#include<vector>

#include"Ref.h"

class InputSystem :public Ref
{
public:
	static GLboolean Keys[1024];
private:
	static InputSystem* m_Instance;
	InputSystem();
	~InputSystem();
public:
	static InputSystem* GetInstance() { return m_Instance; }
	static InputSystem* Create();
private:
	virtual bool Init();
private:
	static std::vector<KeyboardListener*> m_KeyboardListeners;					// ¼üÅÌ¼àÌýÆ÷
	static std::vector<MouseMotionListener*> m_MouseMotionListeners;			// Êó±ê¼àÌýÆ÷
	static std::vector<MousePassiveListener*> m_MousePassiveListeners;			// 
private:
	MouseEventArgs * _LastMouseEventArgs = nullptr;
	std::vector<bool> _LastMouseDownReturn;
	int _MouseButton;
	int _MouseState;
public:
	void AddKeyboardListener(KeyboardListener* listener);
	void AddMouseMotionListener(MouseMotionListener* listener);
	void AddMousePassiveListener(MousePassiveListener* listener);

	void RemoveKeyboardListener(KeyboardListener* listener);
	void RemoveMouseMotionListener(MouseMotionListener* listener);
	void RemoveMousePassiveListener(MousePassiveListener* listener);

	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);

	void Mouse(int button, int state, int x, int y);
	void Motion(int x, int y);
	void Passive(int x, int y);
};



#endif // !_INPUT_SYSTEM_H_


