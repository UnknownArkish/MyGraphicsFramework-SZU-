#include"stdafx.h"
#include "Cube.h"

#include"CubeRenderer.h"

Cube::Cube()
{
}


Cube::~Cube()
{
}

bool Cube::Render()
{
	if (!Node::Render()) {
		return false;
	}
	// 调用CubeRenderer以绘制自身
	CubeRenderer::GetInstance()->Render(this);
	return true;
}


Cube * Cube::Create()
{
	Cube* pRet = new (std::nothrow)Cube();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	return nullptr;
}

bool Cube::Init()
{
	if (!Node::Init()) {
		return false;
	}

	// 默认材质为银制品
	m_Material = MaterialPreSet::Silver;
	// 默认没有立方体贴图
	m_CubeMap = nullptr;

	return true;
}