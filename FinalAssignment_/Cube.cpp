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
	// ����CubeRenderer�Ի�������
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

	// Ĭ�ϲ���Ϊ����Ʒ
	m_Material = MaterialPreSet::Silver;
	// Ĭ��û����������ͼ
	m_CubeMap = nullptr;

	return true;
}