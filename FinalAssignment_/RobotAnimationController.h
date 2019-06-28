

#ifndef _ROBOT_ANIMATION_CONTROLLER_H_
#define _ROBOT_ANIMATION_CONTROLLER_H_
#pragma once


#include"Robot.h"
#include"BaseAnimationConroller.h"

class RobotAnimationController :public BaseAnimationController
{
private:
	Robot * m_Robot;			// 需要操作的机器人
	RobotUnit m_Target;			// 操作的部位

	vec3 m_BaseRotation;		// 基准旋转信息
protected:
	RobotAnimationController();
	virtual bool Init(Robot* robot, RobotUnit target, vec3 range, int keyFrameNum);
public:
	~RobotAnimationController();

	static RobotAnimationController* Create(Robot* robot, RobotUnit target, vec3 range, int keyFrameNum);

	virtual void Update(float deltaTime) override;
};



#endif // !_ROBOT_ANIMATION_CONTROLLER_H_


