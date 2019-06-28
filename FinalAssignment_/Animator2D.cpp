#include "Animator2D.h"



Animator2D::Animator2D()
{
}

void Animator2D::Update(float deltaTime)
{
	// 如果暂停状态则直接返回
	if (m_IsStop)	return;
	// 如果不设置循环，且动画已结束，则返回
	if (!m_IsLoop && m_CurrentFrame >= GetAnimationFrameSize()) {
		Pause();
	}

	m_BaseTime += deltaTime;
	if (m_BaseTime >= m_DeltaTime) {
		m_CurrentFrame++;				// 当前帧自增
		Play(m_CurrentFrame);			// 播放当前帧的信息
		m_BaseTime = 0.0f;				// 基准时间清零
	}
}

bool Animator2D::Init(Animation animation)
{
	if (!Plane::Init()) {
		return false;
	}

	this->SetIsLighted(false);
	this->SetIsAnimator(true);

	// 默认暂停
	m_IsPlaying = false;
	m_IsStop = true;
	// 默认循环
	m_IsLoop = true;

	// 设置默认的 每帧之间的时间间隔
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

