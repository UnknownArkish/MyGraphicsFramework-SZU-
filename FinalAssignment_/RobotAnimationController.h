

#ifndef _ROBOT_ANIMATION_CONTROLLER_H_
#define _ROBOT_ANIMATION_CONTROLLER_H_
#pragma once


#include"Robot.h"
#include"BaseAnimationConroller.h"

class RobotAnimationController :public BaseAnimationController
{
private:
	Robot * m_Robot;			// ��Ҫ�����Ļ�����
	RobotUnit m_Target;			// �����Ĳ�λ

	vec3 m_BaseRotation;		// ��׼��ת��Ϣ
protected:
	RobotAnimationController();
	virtual bool Init(Robot* robot, RobotUnit target, vec3 range, int keyFrameNum);
public:
	~RobotAnimationController();

	static RobotAnimationController* Create(Robot* robot, RobotUnit target, vec3 range, int keyFrameNum);

	virtual void Update(float deltaTime) override;
};



#endif // !_ROBOT_ANIMATION_CONTROLLER_H_


