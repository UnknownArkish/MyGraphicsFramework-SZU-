
#ifndef _USER_CHARACTER_H_
#define _USER_CHARACTER_H_
#pragma once

#include"Node.h"
#include"KeyboardListener.h"

/*
*	一个监听器创建的例子，由于该类会附着在场景上，因此继承自Node类
*	除此以外，由于需要接受键盘输入，因此实现了KeyboardListener接口
*/
class UseCharacter :public Node, public KeyboardListener
{
protected:
	UseCharacter();
	virtual bool Init()override;
public:
	~UseCharacter();
	static UseCharacter* Create();

	// 通过 KeyboardListener 继承
	virtual void OnKeyboardDown(KeyboardEventArgs * args) override;
	virtual void OnKeyboardUp(KeyboardEventArgs * args) override;
};





#endif // !_USER_CHARACTER_H_


