
/*
*	层级建模模型
*	Rotot作为根节点，有子节点身体（Body）
*	Body有子节点头（Head）、手（Hand）、腿（Leg）
*	所有节点本质上是Cube，贴图由立方体贴图实现
*/

#ifndef _ROBOT_H_
#define _ROBOT_H_
#pragma once

#include"Node.h"
#include"Cube.h"
#include"CubeMap.h"
#include"RobotMap.h"
#include"MyCamera.h"

const vec3 DefaultHeadSize = vec3(0.78f, 0.9f, 0.7f);
const vec3 DefaultBodySize = vec3(1.18f, 2.0f, 0.7f);
const vec3 DefaultHandSize = vec3(0.462f, 1.13f, 0.7f);
const vec3 DefaultLegSize = vec3(0.568f, 1.413, 0.7f);
const vec3 DefaultLowerLegSize = vec3(0.568f, 1.651f, 0.7f);

// 机器人部位枚举
enum RobotUnit {
	Head,
	Body,
	LeftUpperHand,
	LeftLowerHand,
	RightUpperHand,
	RightLowerHand,
	LeftUpperLeg,
	LeftLowerLeg,
	RightUpperLeg,
	RightLowerLeg
};

class Robot :public Node
{
private:
	// 躯干部份
	Cube * m_Head;
	Cube * m_Body;

	Cube* m_LeftUpperHand;
	Cube* m_LeftLowerHand;
	Cube* m_RightUpperHand;
	Cube* m_RightLowerHand;

	Cube* m_LeftUpperLeg;
	Cube* m_LeftLowerLeg;
	Cube* m_RightUpperLeg;
	Cube* m_RightLowerLeg;

	RobotMap * m_Map;
protected:
	Robot();

	virtual bool Render()override;
	virtual bool Init(RobotMap* map);
public:
	~Robot();

	static Robot* Create(RobotMap* map = nullptr);

	void SetMaterial(Material material);

	void SetRobotMap(RobotMap* map);
	void SetDefaultMap();

	void SetUnitMap(CubeMap* map, RobotUnit target);
	void SetUnitRotation(vec3 rotation, RobotUnit target);
	void ToRotateUnit(vec3 rotation, RobotUnit target);
	vec3 GetUnitRotation(RobotUnit target);
private:
	void InitTorso();

private:
	//// 设置每个部位的立方体贴图
	//void SetHeadMap(CubeMap* map) { m_Head->SetCubeMap(map); }
	//void SetBodyMap(CubeMap* map) { m_Body->SetCubeMap(map); }
	//void SetLeftUpperHandMap(CubeMap* map) { m_LeftUpperHand->SetCubeMap(map); }
	//void SetLeftLowerHandMap(CubeMap* map) { m_LeftLowerHand->SetCubeMap(map); }
	//void SetRightUpperHandMap(CubeMap* map) { m_RightUpperHand->SetCubeMap(map); }
	//void SetRightLowerHandMap(CubeMap* map) { m_RightLowerHand->SetCubeMap(map); }
	//void SetLeftUpperLegMap(CubeMap* map) { m_LeftUpperLeg->SetCubeMap(map); }
	//void SetLeftLowerLegMap(CubeMap* map) { m_LeftLowerLeg->SetCubeMap(map); }
	//void SetRightUpperLegMap(CubeMap* map) { m_RightUpperLeg->SetCubeMap(map); }
	//void SetRightLowerLegMap(CubeMap* map) { m_RightLowerLeg->SetCubeMap(map); }

	//// 设置每个部分的几何变换信息
	//// 头部
	//void SetHeahRotation(vec3 rotation) { m_Head->SetRotation(rotation); }
	//void SetHeadScale(vec3 scale) { m_Head->SetScale(scale); }
	//// 身体
	//void SetBodyRotation(vec3 rotation) { m_Body->SetRotation(rotation); }
	//void SetBodyScale(vec3 scale) { m_Body->SetScale(scale); }
	//// 左手
	//void SetLeftUpperHandRotation(vec3 rotation) { m_LeftUpperHand->SetRotation(rotation); }
	//void SetLeftUpperHandScale(vec3 scale) { m_LeftUpperHand->SetScale(scale); }
	//void SetLeftLowerHandRotation(vec3 rotation) { m_LeftLowerHand->SetRotation(rotation); }
	//void SetLeftLowerHandScale(vec3 scale) { m_LeftLowerHand->SetScale(scale); }
	//// 右手
	//void SetRightUpperHandRotation(vec3 rotation) { m_RightUpperHand->SetRotation(rotation); }
	//void SetRightUpperHandScale(vec3 scale) { m_RightUpperHand->SetScale(scale); }
	//void SetRightLowerHandRotation(vec3 rotation) { m_RightLowerHand->SetRotation(rotation); }
	//void SetRightLowerHandScale(vec3 scale) { m_RightLowerHand->SetScale(scale); }
	//// 左腿
	//void SetLeftUpperLegRotation(vec3 rotation) { m_LeftUpperLeg->SetRotation(rotation); }
	//void SetLeftUpperLegScale(vec3 scale) { m_LeftUpperLeg->SetScale(scale); }
	//void SetLeftLowerLegRotation(vec3 rotation) { m_LeftLowerLeg->SetRotation(rotation); }
	//void SetLeftLowerLegScale(vec3 scale) { m_LeftLowerLeg->SetScale(scale); }
	//// 右腿
	//void SetRightUpperLegRotation(vec3 rotation) { m_RightUpperLeg->SetRotation(rotation); }
	//void SetRightUpperLegScale(vec3 scale) { m_RightUpperLeg->SetScale(scale); }
	//void SetRightLowerLegRotation(vec3 rotation) { m_RightLowerLeg->SetRotation(rotation); }
	//void SetRightLowerLeftScale(vec3 scale) { m_RightLowerLeg->SetScale(scale); }

	//// 设置每个部分的几何变换信息（原来基础上）
	//// 头部
	//void ToRotateHeah(vec3 rotation) { m_Head->ToRotate(rotation); }
	//void ToScaleHead(vec3 scale) { m_Head->ToScale(scale); }
	//// 身体
	//void ToRotateBody(vec3 rotation) { m_Body->ToRotate(rotation); }
	//void ToScaleBody(vec3 scale) { m_Body->ToScale(scale); }
	//// 左手
	//void ToRotateLeftUpperHand(vec3 rotation) { m_LeftUpperHand->ToRotate(rotation); }
	//void ToScaleLeftUpperHand(vec3 scale) { m_LeftUpperHand->ToScale(scale); }
	//void ToRotateLeftLowerHand(vec3 rotation) { m_LeftLowerHand->ToRotate(rotation); }
	//void ToScaleLeftLowerHand(vec3 scale) { m_LeftLowerHand->ToScale(scale); }
	//// 右手
	//void ToRotateRightUpperHand(vec3 rotation) { m_RightUpperHand->ToRotate(rotation); }
	//void ToScaleRightUpperHand(vec3 scale) { m_RightUpperHand->ToScale(scale); }
	//void ToRotateRightLowerHand(vec3 rotation) { m_RightLowerHand->ToRotate(rotation); }
	//void ToScaleRightLowerHand(vec3 scale) { m_RightLowerHand->ToScale(scale); }
	//// 左腿
	//void ToRotateLeftUpperLeg(vec3 rotation) { m_LeftUpperLeg->ToRotate(rotation); }
	//void ToScaleLeftUpperLeg(vec3 scale) { m_LeftUpperLeg->ToScale(scale); }
	//void ToRotateLeftLowerLeg(vec3 rotation) { m_LeftLowerLeg->ToRotate(rotation); }
	//void ToScaleLeftLowerLeg(vec3 scale) { m_LeftLowerLeg->ToScale(scale); }
	//// 右腿
	//void ToRotateRightUpperLeg(vec3 rotation) { m_RightUpperLeg->ToRotate(rotation); }
	//void ToScaleRightUpperLeg(vec3 scale) { m_RightUpperLeg->ToScale(scale); }
	//void ToRotateRightLowerLeg(vec3 rotation) { m_RightLowerLeg->ToRotate(rotation); }
	//void ToScaleRightLowerLeg(vec3 scale) { m_RightLowerLeg->ToScale(scale); }
};


#endif // !_ROBOT_H_



