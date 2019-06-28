#include "BaseController.h"



BaseController::BaseController()
{
}

BaseController::~BaseController()
{
}

bool BaseController::Init()
{
	if (!Ref::Init()) {
		return false;
	}
	InputSystem::GetInstance()->AddKeyboardListener(this);
	InputSystem::GetInstance()->AddMousePassiveListener(this);
	InputSystem::GetInstance()->AddMouseMotionListener(this);
	return true;
}

void BaseController::OnKeyboardDown(KeyboardEventArgs * args)
{
}

void BaseController::OnKeyboardUp(KeyboardEventArgs * args)
{
}

void BaseController::OnMousePassive(MouseEventArgs * args)
{
}

bool BaseController::OnMouseDown(MouseEventArgs * args)
{
	return false;
}

void BaseController::OnMouseMotion(MouseEventArgs * args)
{
}

void BaseController::OnMouseUp(MouseEventArgs * args)
{
}
