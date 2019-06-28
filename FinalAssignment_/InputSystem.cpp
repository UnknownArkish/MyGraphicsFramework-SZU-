#include "stdafx.h"
#include "InputSystem.h"

#include"stdafx.h"

InputSystem* InputSystem::m_Instance = nullptr;
GLboolean InputSystem::Keys[1024];
std::vector<KeyboardListener*> InputSystem::m_KeyboardListeners;
std::vector<MouseMotionListener*> InputSystem::m_MouseMotionListeners;
std::vector<MousePassiveListener*> InputSystem::m_MousePassiveListeners;

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}

InputSystem * InputSystem::Create()
{
	if (m_Instance == nullptr) {
		m_Instance = new (std::nothrow)InputSystem();
		if (m_Instance && m_Instance->Init()) {
			return m_Instance;
		}
		else {
			delete m_Instance;
			m_Instance = nullptr;
			return nullptr;
		}
	}
	return m_Instance;
}

bool InputSystem::Init()
{
	if (!Ref::Init()) {
		return false;
	}

	_LastMouseEventArgs = nullptr;
	_LastMouseDownReturn.clear();
	_MouseState = GLUT_UP;
	
	return true;
}

void InputSystem::AddKeyboardListener(KeyboardListener * listener)
{
	if (std::find(m_KeyboardListeners.begin(), m_KeyboardListeners.end(), listener) == m_KeyboardListeners.end()) {
		m_KeyboardListeners.push_back(listener);
	}
}

void InputSystem::AddMouseMotionListener(MouseMotionListener * listener)
{
	if (std::find(m_MouseMotionListeners.begin(), m_MouseMotionListeners.end(), listener) == m_MouseMotionListeners.end()) {
		m_MouseMotionListeners.push_back(listener);
	}
}

void InputSystem::AddMousePassiveListener(MousePassiveListener * listener)
{
	if (std::find(m_MousePassiveListeners.begin(), m_MousePassiveListeners.end(), listener) == m_MousePassiveListeners.end()) {
		m_MousePassiveListeners.push_back(listener);
	}
}

void InputSystem::RemoveKeyboardListener(KeyboardListener * listener)
{
	std::vector<KeyboardListener*>::iterator it = 
		std::find(m_KeyboardListeners.begin(), m_KeyboardListeners.end(), listener);
	if (it != m_KeyboardListeners.end()) {
		m_KeyboardListeners.erase(it);
	}
}

void InputSystem::RemoveMouseMotionListener(MouseMotionListener * listener)
{
	std::vector<MouseMotionListener*>::iterator it =
		std::find(m_MouseMotionListeners.begin(), m_MouseMotionListeners.end(), listener);
	if (it != m_MouseMotionListeners.end()) {
		m_MouseMotionListeners.erase(it);
	}
}

void InputSystem::RemoveMousePassiveListener(MousePassiveListener * listener)
{
	std::vector<MousePassiveListener*>::iterator it =
		std::find(m_MousePassiveListeners.begin(), m_MousePassiveListeners.end(), listener);
	if (it != m_MousePassiveListeners.end()) {
		m_MousePassiveListeners.erase(it);
	}
}

void InputSystem::KeyboardDown(unsigned char key, int x, int y)
{
	// 将输入信息包装成KeyboardEventArgs
	KeyboardEventArgs* args = new KeyboardEventArgs();
	args->Key = key;
	args->MousePosition.x = x;
	args->MousePosition.y = y;

	Keys[key] = true;						// 将键位设置为True
	for (KeyboardListener* listener : m_KeyboardListeners) {
		listener->OnKeyboardDown(args);		// 调用监听器中的键盘按下的函数
	}
}

void InputSystem::KeyboardUp(unsigned char key, int x, int y)
{
	KeyboardEventArgs* args = new KeyboardEventArgs();
	args->Key = key;
	args->MousePosition.x = x;
	args->MousePosition.y = y;

	Keys[key] = false;
	for (KeyboardListener* listener : m_KeyboardListeners) {
		listener->OnKeyboardUp(args);
	}
}

void InputSystem::Mouse(int button, int state, int x, int y)
{
	_MouseButton = button;
	_MouseState = state;

	if (_MouseState == GLUT_DOWN) {
		if (_LastMouseEventArgs == nullptr) {
			if (Config::DEBUG)	std::cout << x << ' ' << y << std::endl;

			_LastMouseEventArgs = new MouseEventArgs();
			_LastMouseEventArgs->Button = button;
			_LastMouseEventArgs->OriginLocation = vec2(x, y);
			_LastMouseEventArgs->Location = vec2(x, y);

			for (MouseMotionListener* listener : m_MouseMotionListeners) {
				_LastMouseDownReturn.push_back(listener->OnMouseDown(_LastMouseEventArgs));
			}
		}
	}
	else if(_MouseState == GLUT_UP) {
		if (Config::DEBUG)	std::cout << x << ' ' << y << std::endl;

		_LastMouseEventArgs->Location = vec2(x, y);
		for (unsigned int i = 0; i < m_MouseMotionListeners.size(); i++) {
			if (_LastMouseDownReturn[i]) {
				m_MouseMotionListeners[i]->OnMouseUp(_LastMouseEventArgs);
			}
		}

		// 还原MouseEventArgs信息
		_LastMouseEventArgs = nullptr;
		_LastMouseDownReturn.clear();
	}
}

void InputSystem::Motion(int x, int y)
{
	if (_LastMouseEventArgs == nullptr)	return;

	//if (_MouseState == GLUT_DOWN) {
		if (Config::DEBUG)	std::cout << x << ' ' << y << std::endl;

		_LastMouseEventArgs->Location = vec2(x, y);
		for (unsigned int i = 0; i < m_MouseMotionListeners.size(); i++) {
			if (_LastMouseDownReturn[i]) {
				m_MouseMotionListeners[i]->OnMouseMotion(_LastMouseEventArgs);
			}
		}
	//}
}

void InputSystem::Passive(int x, int y)
{
	MouseEventArgs* args = new MouseEventArgs();
	args->Button = -1;
	args->OriginLocation = args->Location = vec2(x, y);

	for (MousePassiveListener* listener : m_MousePassiveListeners) {
		listener->OnMousePassive(args);
	}
}
