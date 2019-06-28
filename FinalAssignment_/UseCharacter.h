
#ifndef _USER_CHARACTER_H_
#define _USER_CHARACTER_H_
#pragma once

#include"Node.h"
#include"KeyboardListener.h"

/*
*	һ�����������������ӣ����ڸ���ḽ���ڳ����ϣ���˼̳���Node��
*	�������⣬������Ҫ���ܼ������룬���ʵ����KeyboardListener�ӿ�
*/
class UseCharacter :public Node, public KeyboardListener
{
protected:
	UseCharacter();
	virtual bool Init()override;
public:
	~UseCharacter();
	static UseCharacter* Create();

	// ͨ�� KeyboardListener �̳�
	virtual void OnKeyboardDown(KeyboardEventArgs * args) override;
	virtual void OnKeyboardUp(KeyboardEventArgs * args) override;
};





#endif // !_USER_CHARACTER_H_


