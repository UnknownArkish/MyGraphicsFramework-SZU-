
#ifndef _REF_H_
#define _REF_H_
#pragma once

#include"stdafx.h"

/* ����еĳ��࣬���ṩһЩ�������麯�������������ʵ�� */
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


