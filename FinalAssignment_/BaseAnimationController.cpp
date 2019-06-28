#include "BaseAnimationConroller.h"


vec3 BaseAnimationController::GetNextPlayTheta()
{
	//std::cout << sin(Degree2Radians((float)m_CurrentKeyFrame / m_KeyFrameNum * 360.0f)) << std::endl;
	vec3 theta = sin(Degree2Radians((float)m_CurrentKeyFrame / m_KeyFrameNum * 360.0f)) * m_Range;
	m_CurrentKeyFrame = (++m_CurrentKeyFrame) % m_KeyFrameNum;
	return theta;
}

BaseAnimationController::BaseAnimationController()
{
}

bool BaseAnimationController::Init(vec3 range, int keyFrameNum)
{
	if (!Node::Init()) {
		return false;
	}
	m_Range = range;
	m_KeyFrameNum = keyFrameNum;
	m_CurrentKeyFrame = 0;

	return true;
}


BaseAnimationController::~BaseAnimationController()
{
}
