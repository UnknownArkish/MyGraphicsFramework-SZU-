
#ifndef _BASE_ANIMATION_CONTROLLER_H_
#define _BASE_ANIMATION_CONTROLLER_H_
#pragma once

#include"Node.h"

class BaseAnimationController :public Node
{
private:
	vec3 m_Range;						// �ڶ���Χ
	int m_KeyFrameNum;					// �ؼ�֡����
	int m_CurrentKeyFrame;				// ��ǰ�ؼ�֡
protected:
	vec3 GetNextPlayTheta();			// ������һ֡�ĽǶȴ�С
protected:
	BaseAnimationController();
	virtual bool Init(vec3 range, int keyFrameNum);
public:
	~BaseAnimationController();
};



#endif // !_BASE_ANIMATION_CONTROLLER_H_


