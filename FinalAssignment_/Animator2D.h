
/*
*	��ά����������
*	��������һ�ſ��Զ�ʱ�޸���ͼ��Plane
*/

#ifndef _ANIMATOR_2D_H_
#define _ANIMATOR_2D_H_
#pragma once

#include"Animation.h"
#include"Plane.h"

// Ĭ��һ�벥��24֡
const float DEFAULT_PLAY_FPS = 24.0f;

class Animator2D :public Plane
{
private:
	Animation m_Animation;						// ���ŵ���ͼ����

	// ��������״̬
	bool m_IsPlaying;							// �Ƿ����ڲ���
	bool m_IsStop;								// �Ƿ���ͣ
	bool m_IsLoop;								// �Ƿ�ѭ��
	// ���Ʋ�������β��ŵı���
	unsigned int m_CurrentFrame;				// ��ǰ֡

	float m_DeltaTime;							// ÿ֡����֮���ʱ����
	float m_BaseTime;							// ��׼ʱ��
protected:
	Animator2D();
	virtual void Update(float deltaTime)override;
	virtual bool Init(Animation animation);
public:
	~Animator2D();
	static Animator2D* Create(Animation animation);

	Animation GetAnimation();					// ��ȡ������
	void SetAnimation(Animation animation);		// ���ö�����
	int GetAnimationFrameSize();				// ��ȡ�������Ĵ�С

	float GetDeltaTime();						// ��ȡÿ֡���ŵ�ʱ��
	void SetDuration(float duration);			// ���ó���ʱ��
	void SetFPS(float fps);						// ���ö�����ÿ�벥�ŵ�֡��
	void SetDeltaTime(float deltaTime);			// ����ÿ֮֡���ʱ����

	void Start(int from = 0);					// ��from֡��ʼ���ź���
	void Pause();								// ��ֹ����
	void Resume();								// �ָ�����
	void Play(int from,bool toPause = false);	// ����from֡�����ж��Ƿ���ͣ
	void SetLoop(bool flag);					// �����Ƿ�ѭ��
};



#endif // !_ANIMATOR_2D_H_



