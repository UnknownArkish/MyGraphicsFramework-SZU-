
#ifndef _ROBOT_MAP_H_
#define _ROBOT_MAP_H_
#pragma once

#include"Ref.h"
#include"CubeMap.h"

// »úÆ÷ÈËÌùÍ¼
class RobotMap :public Ref {
protected:
	RobotMap();
	virtual bool Init()override;
public:
	~RobotMap();

	CubeMap * Head;
	CubeMap* Body;
	CubeMap* LeftUpperHand;
	CubeMap* LeftLowerHand;
	CubeMap* RightUpperHand;
	CubeMap* RightLowerHand;
	CubeMap* LeftUpperLeg;
	CubeMap* LeftLowerLeg;
	CubeMap* RightUpperLeg;
	CubeMap* RightLowerLeg;

	static RobotMap* Create();
};

#endif // !_ROBOT_MAP_H_



