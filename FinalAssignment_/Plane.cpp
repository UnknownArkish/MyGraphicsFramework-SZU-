#include "Plane.h"

#include"PlaneRenderer.h"

Plane::Plane()
{
}

bool Plane::Init()
{
	if (!Node::Init()) {
		return false;
	}

	m_Texture = nullptr;
	m_Material = MaterialPreSet::Silver;
	m_IsLighted = true;
	m_IsAnimator = false;

	return true;
}

bool Plane::Render()
{
	if (!Node::Render()) {
		return false;
	}
	// @TODO：在这里调用PlaneRenderer进行Plane的绘制
	PlaneRenderer::GetInstance()->Render(this, m_IsLighted);
	return true;
}


Plane::~Plane()
{
}

Plane * Plane::Create()
{
	Plane* pRet = new(std::nothrow)Plane();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void Plane::SetTexture(Texture * texture)
{
	m_Texture = texture;
}
