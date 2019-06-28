
#ifndef _REF_H_
#define _REF_H_
#pragma once

#include"stdafx.h"

/* 框架中的超类，仅提供一些公共的虚函数，由子类具体实现 */
class Ref
{
protected:
	Ref();
	virtual void Update(float deltaTime);
public:
	~Ref();
	virtual bool Init();
	virtual void ToUpdate(float deltaTime);
};


#endif // !_REF_H_


