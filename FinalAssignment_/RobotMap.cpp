#include "RobotMap.h"

#include"ResourcesSystem.h"

RobotMap::RobotMap()
{
}

bool RobotMap::Init()
{
	if (!Ref::Init()) {
		return false;
	}

	// ʹ��Ĭ�ϵ�Robot��ͼ
	Head = ResourcesSystem::GetInstance()->GetCubeMap("DefaultHeadMap");
	Body = ResourcesSystem::GetInstance()->GetCubeMap("DefaultBodyMap");
	LeftUpperHand = ResourcesSystem::GetInstance()->GetCubeMap("DefaultLeftUpperHandMap");
	LeftLowerHand = ResourcesSystem::GetInstance()->GetCubeMap("DefaultLeftLowerHandMap");
	RightUpperHand = ResourcesSystem::GetInstance()->GetCubeMap("DefaultRightUpperHandMap");
	RightLowerHand = ResourcesSystem::GetInstance()->GetCubeMap("DefaultRightLowerHandMap");
	LeftUpperLeg = ResourcesSystem::GetInstance()->GetCubeMap("DefaultLeftUpperLegMap");
	LeftLowerLeg = ResourcesSystem::GetInstance()->GetCubeMap("DefaultLeftLowerLegMap");
	RightUpperLeg = ResourcesSystem::GetInstance()->GetCubeMap("DefaultRightUpperLegMap");
	RightLowerLeg = ResourcesSystem::GetInstance()->GetCubeMap("DefaultRightLowerLegMap");

	return true;
}

RobotMap::~RobotMap()
{
}

RobotMap * RobotMap::Create()
{
	RobotMap* pRet = new(std::nothrow)RobotMap();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}
