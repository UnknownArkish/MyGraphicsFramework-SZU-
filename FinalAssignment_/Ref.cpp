#include "stdafx.h"
#include "Ref.h"


Ref::Ref()
{
}


Ref::~Ref()
{
}

bool Ref::Init()
{
	return true;
}


void Ref::Update(float deltaTime)
{
	// 每帧调用一次
}

void Ref::ToUpdate(float deltaTime)
{
	this->Update(deltaTime);
}
