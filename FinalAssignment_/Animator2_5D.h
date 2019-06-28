
#ifndef _ANIMATOR_2_5D_H_
#define _ANIMATOR_2_5D_H_
#pragma once

#include"Animator2D.h"
#include"Node.h"

class Animator2_5D :public Node
{
private:
	Animator2D * m_Animator_1 = nullptr;			// 拥有两个2D动画机
	Animator2D * m_Animator_2 = nullptr;			// 并将它们呈90°摆放
protected:
	Animator2_5D();

	virtual bool Init(Animation animation);
public:
	~Animator2_5D();

	static Animator2_5D* Create(Animation aniamtion);

	void SetAnimation(Animation animation);
	Animation GetAnimation();
	int GetAnimationFrameSize();

	float GetDeltaTime();													// 获取每帧播放的时间
	void SetDuration(float duration, float intervalTime = 0.0f);			// 设置持续时间
	void SetFPS(float fps, float intervalTime = 0.0f);						// 设置动画机每秒播放的帧数
	void SetDeltaTime(float deltaTime, float intervalTime = 0.0f);			// 设置每帧之间的时间间隔
	void SetIntervalTime(float intervalTime);

	void Start(int from_1 = 0, int from_2 = 0);								// 从from帧开始播放函数
	void Pause();															// 中止函数
	void Resume();															// 恢复函数
	void Play(int from_1, int from_2, bool toPause = false);				// 播放from帧，并判断是否暂停
	void SetLoop(bool flag);												// 设置是否循环
};



#endif // !_ANIMATOR_2_5D_H_


