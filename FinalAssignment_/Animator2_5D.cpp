#include "Animator2_5D.h"



Animator2_5D::Animator2_5D()
{
}

bool Animator2_5D::Init(Animation animation)
{
	if (!Node::Init()) {
		return false;
	}

	m_Animator_1 = Animator2D::Create(animation);
	m_Animator_2 = Animator2D::Create(animation);
	m_Animator_2->SetRotation(vec3(0.0f, 90.0f, 0.0f));

	this->AddChildren(m_Animator_1);
	this->AddChildren(m_Animator_2);

	return true;
}


Animator2_5D::~Animator2_5D()
{
}

Animator2_5D * Animator2_5D::Create(Animation animation)
{
	Animator2_5D* pRet = new(std::nothrow)Animator2_5D();
	if (pRet && pRet->Init(animation)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void Animator2_5D::SetAnimation(Animation animation)
{
}

Animation Animator2_5D::GetAnimation()
{
	return m_Animator_1->GetAnimation();
}

int Animator2_5D::GetAnimationFrameSize()
{
	return m_Animator_1->GetAnimationFrameSize();
}

float Animator2_5D::GetDeltaTime()
{
	return m_Animator_1->GetDeltaTime();
}

void Animator2_5D::SetDuration(float duration, float intervalTime)
{
	float deltaTime = duration / GetAnimationFrameSize();
	this->SetDeltaTime(deltaTime, intervalTime);
}

void Animator2_5D::SetFPS(float fps, float intervalTime)
{
	float deltaTime = 1.0f / fps;
	this->SetDeltaTime(deltaTime, intervalTime);
}

void Animator2_5D::SetDeltaTime(float deltaTime, float intervalTime)
{
	m_Animator_1->SetDeltaTime(deltaTime);
	m_Animator_2->SetDeltaTime(deltaTime + intervalTime);
}

void Animator2_5D::SetIntervalTime(float intervalTime)
{
	this->SetDeltaTime(this->GetDeltaTime(), intervalTime);
}

void Animator2_5D::Start(int from_1, int from_2)
{
	m_Animator_1->Start(from_1);
	m_Animator_2->Start(from_2);
}

void Animator2_5D::Pause()
{
	m_Animator_1->Pause();
	m_Animator_2->Pause();
}

void Animator2_5D::Resume()
{
	m_Animator_1->Resume();
	m_Animator_2->Resume();
}

void Animator2_5D::Play(int from_1, int from_2, bool toPause)
{
	m_Animator_1->Play(from_1, toPause);
	m_Animator_2->Play(from_2, toPause);
}

void Animator2_5D::SetLoop(bool flag)
{
	m_Animator_1->SetLoop(flag);
	m_Animator_2->SetLoop(flag);
}
