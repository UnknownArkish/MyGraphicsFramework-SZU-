#include "RobotAnimationController.h"



RobotAnimationController::RobotAnimationController()
{
}

bool RobotAnimationController::Init(Robot * robot, RobotUnit target, vec3 range, int keyFrameNum)
{
	if (!BaseAnimationController::Init(range,keyFrameNum)) {
		return false;
	}

	m_Robot = robot;
	m_Target = target;
	m_BaseRotation = m_Robot->GetUnitRotation(target);

	return true;
}


RobotAnimationController::~RobotAnimationController()
{
}

RobotAnimationController * RobotAnimationController::Create(Robot * robot, RobotUnit target, vec3 range, int keyFrameNum)
{
	RobotAnimationController* pRet = new (std::nothrow)RobotAnimationController();
	if (pRet && pRet->Init(robot, target, range, keyFrameNum)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void RobotAnimationController::Update(float deltaTime)
{
	m_Robot->SetUnitRotation(this->m_BaseRotation + this->GetNextPlayTheta(), m_Target);
}
