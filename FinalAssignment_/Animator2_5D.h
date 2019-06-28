
#ifndef _ANIMATOR_2_5D_H_
#define _ANIMATOR_2_5D_H_
#pragma once

#include"Animator2D.h"
#include"Node.h"

class Animator2_5D :public Node
{
private:
	Animator2D * m_Animator_1 = nullptr;			// ӵ������2D������
	Animator2D * m_Animator_2 = nullptr;			// �������ǳ�90��ڷ�
protected:
	Animator2_5D();

	virtual bool Init(Animation animation);
public:
	~Animator2_5D();

	static Animator2_5D* Create(Animation aniamtion);

	void SetAnimation(Animation animation);
	Animation GetAnimation();
	int GetAnimationFrameSize();

	float GetDeltaTime();													// ��ȡÿ֡���ŵ�ʱ��
	void SetDuration(float duration, float intervalTime = 0.0f);			// ���ó���ʱ��
	void SetFPS(float fps, float intervalTime = 0.0f);						// ���ö�����ÿ�벥�ŵ�֡��
	void SetDeltaTime(float deltaTime, float intervalTime = 0.0f);			// ����ÿ֮֡���ʱ����
	void SetIntervalTime(float intervalTime);

	void Start(int from_1 = 0, int from_2 = 0);								// ��from֡��ʼ���ź���
	void Pause();															// ��ֹ����
	void Resume();															// �ָ�����
	void Play(int from_1, int from_2, bool toPause = false);				// ����from֡�����ж��Ƿ���ͣ
	void SetLoop(bool flag);												// �����Ƿ�ѭ��
};



#endif // !_ANIMATOR_2_5D_H_


