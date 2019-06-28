#include "TestMouseListener.h"

#include"InputSystem.h"

TestMouseListener::TestMouseListener()
{
	InputSystem::GetInstance()->AddMouseMotionListener(this);
	InputSystem::GetInstance()->AddMousePassiveListener(this);
}


TestMouseListener::~TestMouseListener()
{
}

bool TestMouseListener::OnMouseDown(MouseEventArgs * args)
{

	std::cout << "OnMouseDown::" << args->OriginLocation.x << ' ' << args->OriginLocation.y << std::endl;
	return true;
}

void TestMouseListener::OnMouseMotion(MouseEventArgs * args)
{
	std::cout << "OnMouseMove::" << args->Location.x << ' ' << args->Location.y << std::endl;
}

void TestMouseListener::OnMouseUp(MouseEventArgs * args)
{
	std::cout << "OnMouseUp::" << args->OriginLocation.x << ' ' << args->OriginLocation.y << std::endl;
}

void TestMouseListener::OnMousePassive(MouseEventArgs * args)
{
	std::cout << "OnMousePassive::" << args->OriginLocation.x << ' ' << args->OriginLocation.y << std::endl;
}
