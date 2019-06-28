#include "TestKeyboardListener.h"

#include"InputSystem.h"

TestKeyboardListener::TestKeyboardListener()
{
	InputSystem::GetInstance()->AddKeyboardListener(this);
}


TestKeyboardListener::~TestKeyboardListener()
{
}

//void TestKeyboardListener::OnKeyboardDown(unsigned char key, int x, int y)
//{
//	if (key == VK_ESCAPE) {
//		exit(EXIT_SUCCESS);
//	}
//
//}
//
//void TestKeyboardListener::OnKeyboardUp(unsigned char key, int x, int y)
//{
//}

void TestKeyboardListener::OnKeyboardDown(KeyboardEventArgs * args)
{
	//std::cout << args->Key << std::endl;

	if (args->Key == VK_ESCAPE) {
		exit(EXIT_SUCCESS);
	}
}

void TestKeyboardListener::OnKeyboardUp(KeyboardEventArgs * args)
{
}
