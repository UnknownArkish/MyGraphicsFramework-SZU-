
/*
*	�㼶��ģģ��
*	Rotot��Ϊ���ڵ㣬���ӽڵ����壨Body��
*	Body���ӽڵ�ͷ��Head�����֣�Hand�����ȣ�Leg��
*	���нڵ㱾������Cube����ͼ����������ͼʵ��
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

// �����˲�λö��
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
	// ���ɲ���
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
	//// ����ÿ����λ����������ͼ
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

	//// ����ÿ�����ֵļ��α任��Ϣ
	//// ͷ��
	//void SetHeahRotation(vec3 rotation) { m_Head->SetRotation(rotation); }
	//void SetHeadScale(vec3 scale) { m_Head->SetScale(scale); }
	//// ����
	//void SetBodyRotation(vec3 rotation) { m_Body->SetRotation(rotation); }
	//void SetBodyScale(vec3 scale) { m_Body->SetScale(scale); }
	//// ����
	//void SetLeftUpperHandRotation(vec3 rotation) { m_LeftUpperHand->SetRotation(rotation); }
	//void SetLeftUpperHandScale(vec3 scale) { m_LeftUpperHand->SetScale(scale); }
	//void SetLeftLowerHandRotation(vec3 rotation) { m_LeftLowerHand->SetRotation(rotation); }
	//void SetLeftLowerHandScale(vec3 scale) { m_LeftLowerHand->SetScale(scale); }
	//// ����
	//void SetRightUpperHandRotation(vec3 rotation) { m_RightUpperHand->SetRotation(rotation); }
	//void SetRightUpperHandScale(vec3 scale) { m_RightUpperHand->SetScale(scale); }
	//void SetRightLowerHandRotation(vec3 rotation) { m_RightLowerHand->SetRotation(rotation); }
	//void SetRightLowerHandScale(vec3 scale) { m_RightLowerHand->SetScale(scale); }
	//// ����
	//void SetLeftUpperLegRotation(vec3 rotation) { m_LeftUpperLeg->SetRotation(rotation); }
	//void SetLeftUpperLegScale(vec3 scale) { m_LeftUpperLeg->SetScale(scale); }
	//void SetLeftLowerLegRotation(vec3 rotation) { m_LeftLowerLeg->SetRotation(rotation); }
	//void SetLeftLowerLegScale(vec3 scale) { m_LeftLowerLeg->SetScale(scale); }
	//// ����
	//void SetRightUpperLegRotation(vec3 rotation) { m_RightUpperLeg->SetRotation(rotation); }
	//void SetRightUpperLegScale(vec3 scale) { m_RightUpperLeg->SetScale(scale); }
	//void SetRightLowerLegRotation(vec3 rotation) { m_RightLowerLeg->SetRotation(rotation); }
	//void SetRightLowerLeftScale(vec3 scale) { m_RightLowerLeg->SetScale(scale); }

	//// ����ÿ�����ֵļ��α任��Ϣ��ԭ�������ϣ�
	//// ͷ��
	//void ToRotateHeah(vec3 rotation) { m_Head->ToRotate(rotation); }
	//void ToScaleHead(vec3 scale) { m_Head->ToScale(scale); }
	//// ����
	//void ToRotateBody(vec3 rotation) { m_Body->ToRotate(rotation); }
	//void ToScaleBody(vec3 scale) { m_Body->ToScale(scale); }
	//// ����
	//void ToRotateLeftUpperHand(vec3 rotation) { m_LeftUpperHand->ToRotate(rotation); }
	//void ToScaleLeftUpperHand(vec3 scale) { m_LeftUpperHand->ToScale(scale); }
	//void ToRotateLeftLowerHand(vec3 rotation) { m_LeftLowerHand->ToRotate(rotation); }
	//void ToScaleLeftLowerHand(vec3 scale) { m_LeftLowerHand->ToScale(scale); }
	//// ����
	//void ToRotateRightUpperHand(vec3 rotation) { m_RightUpperHand->ToRotate(rotation); }
	//void ToScaleRightUpperHand(vec3 scale) { m_RightUpperHand->ToScale(scale); }
	//void ToRotateRightLowerHand(vec3 rotation) { m_RightLowerHand->ToRotate(rotation); }
	//void ToScaleRightLowerHand(vec3 scale) { m_RightLowerHand->ToScale(scale); }
	//// ����
	//void ToRotateLeftUpperLeg(vec3 rotation) { m_LeftUpperLeg->ToRotate(rotation); }
	//void ToScaleLeftUpperLeg(vec3 scale) { m_LeftUpperLeg->ToScale(scale); }
	//void ToRotateLeftLowerLeg(vec3 rotation) { m_LeftLowerLeg->ToRotate(rotation); }
	//void ToScaleLeftLowerLeg(vec3 scale) { m_LeftLowerLeg->ToScale(scale); }
	//// ����
	//void ToRotateRightUpperLeg(vec3 rotation) { m_RightUpperLeg->ToRotate(rotation); }
	//void ToScaleRightUpperLeg(vec3 scale) { m_RightUpperLeg->ToScale(scale); }
	//void ToRotateRightLowerLeg(vec3 rotation) { m_RightLowerLeg->ToRotate(rotation); }
	//void ToScaleRightLowerLeg(vec3 scale) { m_RightLowerLeg->ToScale(scale); }
};


#endif // !_ROBOT_H_



