#include "Robot.h"



Robot::Robot()
{
}

bool Robot::Render()
{
	if (!Node::Render()) {
		return false;
	}
	return true;
}

bool Robot::Init(RobotMap* map)
{
	if (!Node::Init()) {
		return false;
	}

	// @TODO：初始化机器人
	InitTorso();
	if (map) {
		SetRobotMap(map);
	}
	else {
		//SetRobotMap(RobotMap::Create());
	}

	return true;
}


Robot::~Robot()
{
}

Robot * Robot::Create(RobotMap * map)
{
	Robot* pRet = new(std::nothrow)Robot();
	if (pRet && pRet->Init(map)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void Robot::SetRobotMap(RobotMap * map)
{
	if (map == nullptr)	return;

	m_Map = map;

	m_Head->SetCubeMap(map->Head);
	m_Body->SetCubeMap(map->Body);

	m_LeftUpperHand->SetCubeMap(map->LeftUpperHand);
	m_LeftLowerHand->SetCubeMap(map->LeftLowerHand);
	m_RightUpperHand->SetCubeMap(map->RightUpperHand);
	m_RightLowerHand->SetCubeMap(map->RightLowerHand);

	m_LeftUpperLeg->SetCubeMap(map->LeftUpperLeg);
	m_LeftLowerLeg->SetCubeMap(map->LeftLowerLeg);
	m_RightUpperLeg->SetCubeMap(map->RightUpperLeg);
	m_RightLowerLeg->SetCubeMap(map->RightLowerLeg);
}

void Robot::SetDefaultMap()
{
	SetRobotMap(RobotMap::Create());
}

void Robot::SetMaterial(Material material)
{
	m_Head->SetMaterial(material);
	m_Body->SetMaterial(material);

	m_LeftUpperHand->SetMaterial(material);
	m_LeftLowerHand->SetMaterial(material);
	m_RightUpperHand->SetMaterial(material);
	m_RightLowerHand->SetMaterial(material);

	m_LeftUpperLeg->SetMaterial(material);
	m_LeftLowerLeg->SetMaterial(material);
	m_RightUpperLeg->SetMaterial(material);
	m_RightLowerLeg->SetMaterial(material);
}

void Robot::SetUnitMap(CubeMap * map, RobotUnit target)
{
	switch (target)
	{
	case Head:
		m_Head->SetCubeMap(map);
		break;
	case Body:
		m_Body->SetCubeMap(map);
		break;
	case LeftUpperHand:
		m_LeftUpperHand->SetCubeMap(map);
		break;
	case LeftLowerHand:
		m_LeftLowerHand->SetCubeMap(map);
		break;
	case RightUpperHand:
		m_RightUpperHand->SetCubeMap(map);
		break;
	case RightLowerHand:
		m_RightLowerHand->SetCubeMap(map);
		break;
	case LeftUpperLeg:
		m_LeftUpperLeg->SetCubeMap(map);
		break;
	case LeftLowerLeg:
		m_LeftLowerLeg->SetCubeMap(map);
		break;
	case RightUpperLeg:
		m_RightUpperLeg->SetCubeMap(map);
		break;
	case RightLowerLeg:
		m_RightLowerLeg->SetCubeMap(map);
		break;
	default:
		break;
	}
}

void Robot::SetUnitRotation(vec3 rotation, RobotUnit target)
{
	switch (target)
	{
	case Head:
		m_Head->SetRotation(rotation);
		break;
	case Body:
		m_Body->SetRotation(rotation);
		break;
	case LeftUpperHand:
		m_LeftUpperHand->SetRotation(rotation);
		break;
	case LeftLowerHand:
		m_LeftLowerHand->SetRotation(rotation);
		break;
	case RightUpperHand:
		m_RightUpperHand->SetRotation(rotation);
		break;
	case RightLowerHand:
		m_RightLowerHand->SetRotation(rotation);
		break;
	case LeftUpperLeg:
		m_LeftUpperLeg->SetRotation(rotation);
		break;
	case LeftLowerLeg:
		m_LeftLowerLeg->SetRotation(rotation);
		break;
	case RightUpperLeg:
		m_RightUpperLeg->SetRotation(rotation);
		break;
	case RightLowerLeg:
		m_RightLowerLeg->SetRotation(rotation);
		break;
	default:
		break;
	}
}

void Robot::ToRotateUnit(vec3 rotation, RobotUnit target)
{
	switch (target)
	{
	case Head:
		m_Head->ToRotate(rotation);
		break;
	case Body:
		m_Body->ToRotate(rotation);
		break;
	case LeftUpperHand:
		m_LeftUpperHand->ToRotate(rotation);
		break;
	case LeftLowerHand:
		m_LeftLowerHand->ToRotate(rotation);
		break;
	case RightUpperHand:
		m_RightUpperHand->ToRotate(rotation);
		break;
	case RightLowerHand:
		m_RightLowerHand->ToRotate(rotation);
		break;
	case LeftUpperLeg:
		m_LeftUpperLeg->ToRotate(rotation);
		break;
	case LeftLowerLeg:
		m_LeftLowerLeg->ToRotate(rotation);
		break;
	case RightUpperLeg:
		m_RightUpperLeg->ToRotate(rotation);
		break;
	case RightLowerLeg:
		m_RightLowerLeg->ToRotate(rotation);
		break;
	default:
		break;
	}
}

vec3 Robot::GetUnitRotation(RobotUnit target)
{
	vec3 rotation;
	switch (target)
	{
	case Head:
		rotation = m_Head->GetRotation();
		break;
	case Body:
		rotation = m_Body->GetRotation();
		break;
	case LeftUpperHand:
		rotation = m_LeftUpperHand->GetRotation();
		break;
	case LeftLowerHand:
		rotation = m_LeftLowerHand->GetRotation();
		break;
	case RightUpperHand:
		rotation = m_RightUpperHand->GetRotation();
		break;
	case RightLowerHand:
		rotation = m_RightLowerHand->GetRotation();
		break;
	case LeftUpperLeg:
		rotation = m_LeftUpperLeg->GetRotation();
		break;
	case LeftLowerLeg:
		rotation = m_LeftLowerLeg->GetRotation();
		break;
	case RightUpperLeg:
		rotation = m_RightUpperLeg->GetRotation();
		break;
	case RightLowerLeg:
		rotation = m_RightLowerLeg->GetRotation();
		break;
	default:
		break;
	}
	return rotation;
}

void Robot::InitTorso()
{	
	// @TODO：Robot的初始化，确定每个部件的初始相对位置
	// 身体的初始化
	m_Body = Cube::Create();
	m_Body->SetInstanceMatrix(Scale(DefaultBodySize));
	this->AddChildren(m_Body);

	// 头部
	m_Head = Cube::Create();
	m_Body->AddChildren(m_Head);
	m_Head->SetInstanceMatrix(Translate(vec3(0.0f, 0.5f*DefaultHeadSize.y, 0.0f)) * Scale(DefaultHeadSize));
	m_Head->SetPosition(vec3(0.0f, 0.5f*DefaultBodySize.y, 0.0f));
	// 左手臂
	m_LeftUpperHand = Cube::Create();
	m_Body->AddChildren(m_LeftUpperHand);
	// 设置实例矩阵
	m_LeftUpperHand->SetInstanceMatrix(
		Translate(0.5f*DefaultHandSize.x, -0.5f*DefaultHandSize.y, 0.0f) * Scale(DefaultHandSize));
	// 设置左上臂相对于Body的位置
	m_LeftUpperHand->SetPosition(vec3(0.5f*DefaultBodySize.x, 0.44f*DefaultBodySize.y, 0.0f));

	m_LeftLowerHand = Cube::Create();
	m_LeftUpperHand->AddChildren(m_LeftLowerHand);
	m_LeftLowerHand->SetInstanceMatrix(Translate(0.0f, -0.5f*DefaultHandSize.y, 0.0f) * Scale(DefaultHandSize));
	m_LeftLowerHand->SetPosition(vec3(0.5f*DefaultHandSize.x, -DefaultHandSize.y, 0.0f));
	// 右手臂
	m_RightUpperHand = Cube::Create();
	m_Body->AddChildren(m_RightUpperHand);
	m_RightUpperHand->SetInstanceMatrix(Translate(-0.5f*DefaultHandSize.x, -0.5f*DefaultHandSize.y, 0.0f) * Scale(DefaultHandSize));
	m_RightUpperHand->SetPosition(vec3(-0.5f*DefaultBodySize.x, 0.44f*DefaultBodySize.y, 0.0f));

	m_RightLowerHand = Cube::Create();
	m_RightUpperHand->AddChildren(m_RightLowerHand);
	m_RightLowerHand->SetInstanceMatrix(Translate(vec3(0.0f, -0.5f*DefaultHandSize.y, 0.0f)) * Scale(DefaultHandSize));
	m_RightLowerHand->SetPosition(vec3(-0.5f*DefaultHandSize.x, -DefaultHandSize.y, 0.0f));
	// 左腿
	m_LeftUpperLeg = Cube::Create();
	m_Body->AddChildren(m_LeftUpperLeg);
	m_LeftUpperLeg->SetInstanceMatrix(Translate(vec3(0.0f, -0.5f*DefaultLegSize.y, 0.0f)) * Scale(DefaultLegSize));
	m_LeftUpperLeg->SetPosition(vec3(0.25f*DefaultBodySize.x, -0.5f*DefaultBodySize.y, 0.0f * DefaultBodySize.z));

	m_LeftLowerLeg = Cube::Create();
	m_LeftUpperLeg->AddChildren(m_LeftLowerLeg);
	m_LeftLowerLeg->SetInstanceMatrix(Translate(vec3(0.0f, -0.5f*DefaultLowerLegSize.y, 0.0f)) * Scale(DefaultLowerLegSize));
	m_LeftLowerLeg->SetPosition(vec3(0.0f, -DefaultLegSize.y, 0.0f));
	// 右腿
	m_RightUpperLeg = Cube::Create();
	m_Body->AddChildren(m_RightUpperLeg);
	m_RightUpperLeg->SetInstanceMatrix(Translate(vec3(0.0f, -0.5f*DefaultLegSize.y, 0.0f)) * Scale(DefaultLegSize));
	m_RightUpperLeg->SetPosition(vec3(-0.25f*DefaultBodySize.x, -0.5f*DefaultBodySize.y, 0.0f * DefaultBodySize.z));

	m_RightLowerLeg = Cube::Create();
	m_RightUpperLeg->AddChildren(m_RightLowerLeg);
	m_RightLowerLeg->SetInstanceMatrix(Translate(vec3(0.0f, -0.5f*DefaultLowerLegSize.y, 0.0f)) * Scale(DefaultLowerLegSize));
	m_RightLowerLeg->SetPosition(vec3(0.0f, -DefaultLegSize.y, 0.0f));
}
