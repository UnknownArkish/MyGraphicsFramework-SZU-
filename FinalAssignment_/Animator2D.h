
/*
*	二维动画播放器
*	本质上是一张可以定时修改贴图的Plane
*/

#ifndef _ANIMATOR_2D_H_
#define _ANIMATOR_2D_H_
#pragma once

#include"Animation.h"
#include"Plane.h"

// 默认一秒播放24帧
const float DEFAULT_PLAY_FPS = 24.0f;

class Animator2D :public Plane
{
private:
	Animation m_Animation;						// 播放的贴图数组

	// 播放器的状态
	bool m_IsPlaying;							// 是否正在播放
	bool m_IsStop;								// 是否暂停
	bool m_IsLoop;								// 是否循环
	// 控制播放器如何播放的变量
	unsigned int m_CurrentFrame;				// 当前帧

	float m_DeltaTime;							// 每帧动画之间的时间间隔
	float m_BaseTime;							// 基准时间
protected:
	Animator2D();
	virtual void Update(float deltaTime)override;
	virtual bool Init(Animation animation);
public:
	~Animator2D();
	static Animator2D* Create(Animation animation);

	Animation GetAnimation();					// 获取动画机
	void SetAnimation(Animation animation);		// 设置动画机
	int GetAnimationFrameSize();				// 获取动画机的大小

	float GetDeltaTime();						// 获取每帧播放的时间
	void SetDuration(float duration);			// 设置持续时间
	void SetFPS(float fps);						// 设置动画机每秒播放的帧数
	void SetDeltaTime(float deltaTime);			// 设置每帧之间的时间间隔

	void Start(int from = 0);					// 从from帧开始播放函数
	void Pause();								// 中止函数
	void Resume();								// 恢复函数
	void Play(int from,bool toPause = false);	// 播放from帧，并判断是否暂停
	void SetLoop(bool flag);					// 设置是否循环
};



#endif // !_ANIMATOR_2D_H_



