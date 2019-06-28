#include "UseCharacter.h"

#include"InputSystem.h"

UseCharacter::UseCharacter()
{
}

bool UseCharacter::Init()
{
	if (!Node::Init()) {
		return false;
	}
	// ��InputSystemע�������
	InputSystem::GetInstance()->AddKeyboardListener(this);
	return true;
}


UseCharacter::~UseCharacter()
{
}

UseCharacter * UseCharacter::Create()
{
	UseCharacter* pRet = new(std::nothrow)UseCharacter();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void UseCharacter::OnKeyboardDown(KeyboardEventArgs * args)
{
	switch (args->Key)
	{
	case 'w':
		// @TODO��������ƶ���ɫ�ɣ�
		break;
	case 's':
		break;
	case 'a':
		break;
	case 'd':
		break;
	default:
		break;
	}
}

void UseCharacter::OnKeyboardUp(KeyboardEventArgs * args)
{
}
