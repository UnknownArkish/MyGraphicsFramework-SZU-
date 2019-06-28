#include "Animator2D.h"



Animator2D::Animator2D()
{
}

void Animator2D::Update(float deltaTime)
{
	// �����ͣ״̬��ֱ�ӷ���
	if (m_IsStop)	return;
	// ���������ѭ�����Ҷ����ѽ������򷵻�
	if (!m_IsLoop && m_CurrentFrame >= GetAnimationFrameSize()) {
		Pause();
	}

	m_BaseTime += deltaTime;
	if (m_BaseTime >= m_DeltaTime) {
		m_CurrentFrame++;				// ��ǰ֡����
		Play(m_CurrentFrame);			// ���ŵ�ǰ֡����Ϣ
		m_BaseTime = 0.0f;				// ��׼ʱ������
	}
}

bool Animator2D::Init(Animation animation)
{
	if (!Plane::Init()) {
		return false;
	}

	this->SetIsLighted(false);
	this->SetIsAnimator(true);

	// Ĭ����ͣ
	m_IsPlaying = false;
	m_IsStop = true;
	// Ĭ��ѭ��
	m_IsLoop = true;

	// ����Ĭ�ϵ� ÿ֮֡���ʱ����
	this->SetFPS(DEFAULT_PLAY_FPS);

	SetAnimation(animation);
	Play(0, true);

	m_BaseTime = 0.0f;

	return true;
}


Animator2D::~Animator2D()
{
}

Animator2D * Animator2D::Create(Animation animation)
{
	Animator2D* pRet = new (std::nothrow)Animator2D();
	if (pRet && pRet->Init(animation)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

Animation Animator2D::GetAnimation()
{
	return m_Animation;
}

void Animator2D::SetAnimation(Animation animation)
{
	m_Animation = animation;
}

int Animator2D::GetAnimationFrameSize()
{
	return m_Animation.size();
}

float Animator2D::GetDeltaTime()
{
	return m_DeltaTime;
}

void Animator2D::SetDuration(float duration)
{
	float deltaTime = duration / GetAnimationFrameSize();
	this->SetDeltaTime(deltaTime);
}

void Animator2D::SetFPS(float fps)
{
	float deltaTime = 1.0f / fps;
	this->SetDeltaTime(deltaTime);
}

void Animator2D::SetDeltaTime(float deltaTime)
{
	m_DeltaTime = deltaTime;
}

void Animator2D::Start(int from)
{
	if (m_IsPlaying == true)	return;

	m_IsPlaying = true;
	m_IsStop = false;

	this->Play(from, false);
}

void Animator2D::Pause()
{
	if (m_IsStop)	return;

	m_IsPlaying = false;
	m_IsStop = true;
}

void Animator2D::Resume()
{
	if (m_IsPlaying)	return;

	m_IsPlaying = true;
	m_IsStop = false;
}

void Animator2D::Play(int from, bool toPause)
{
	if (from < 0)	return;

	m_CurrentFrame = from % GetAnimationFrameSize();
	this->SetTexture(m_Animation[m_CurrentFrame]);
	if (toPause) {
		this->Pause();
	}
}


void Animator2D::SetLoop(bool flag)
{
	m_IsLoop = flag;
}

