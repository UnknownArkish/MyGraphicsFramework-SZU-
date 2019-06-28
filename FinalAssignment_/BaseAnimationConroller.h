
#ifndef _BASE_ANIMATION_CONTROLLER_H_
#define _BASE_ANIMATION_CONTROLLER_H_
#pragma once

#include"Node.h"

class BaseAnimationController :public Node
{
private:
	vec3 m_Range;						// 摆动范围
	int m_KeyFrameNum;					// 关键帧数量
	int m_CurrentKeyFrame;				// 当前关键帧
protected:
	vec3 GetNextPlayTheta();			// 播放下一帧的角度大小
protected:
	BaseAnimationController();
	virtual bool Init(vec3 range, int keyFrameNum);
public:
	~BaseAnimationController();
};



#endif // !_BASE_ANIMATION_CONTROLLER_H_


