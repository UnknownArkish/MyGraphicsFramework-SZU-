#include "CameraNode.h"



CameraNode::CameraNode()
{
}

bool CameraNode::Init(vec3 position, vec3 up)
{
	if (!Node::Init()) {
		return false;
	}

	this->SetPosition(position);
	m_WorldUp = up;

	m_DefaultDirection = m_Direction = DefaultDirection;
	Zoom = ZOOM;

	UpdateCameraVectors();
	return true;
}


CameraNode::~CameraNode()
{
}

CameraNode * CameraNode::Create(vec3 position, vec3 up)
{
	CameraNode* pRet = new(std::nothrow)CameraNode();
	if (pRet && pRet->Init(position, up)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void CameraNode::ToTranslate(vec3 translation)
{
	Node::ToTranslate(translation);
	UpdateCameraVectors();
}

void CameraNode::ToRotate(vec3 rotation)
{
	Node::ToRotate(rotation);
	UpdateCameraVectors();
}

void CameraNode::ToScale(vec3 scale)
{
	Node::ToScale(scale);
	UpdateCameraVectors();
}

void CameraNode::SetPosition(vec3 position)
{
	Node::SetPosition(position);
	UpdateCameraVectors();
}

void CameraNode::SetRotation(vec3 rotation)
{
	Node::SetRotation(rotation);
	UpdateCameraVectors();
}

void CameraNode::SetScale(vec3 scale)
{
	Node::SetScale(scale);
	UpdateCameraVectors();
}


mat4 CameraNode::GetViewMatrix()
{
	return LookAt(this->GetPosition(), this->GetPosition() + m_Direction, m_Up);
}

mat4 CameraNode::GetProjMatrix()
{
	return Perspective(this->Zoom,
		(GLfloat)Config::Screen_Wdith / (GLfloat)Config::Screen_Height,
		0.1f, 15.0f);
}

void CameraNode::UpdateCameraVectors()
{
	vec4 direction = this->GetGlobalMatrix() * vec4(m_DefaultDirection, 0.0f);
	m_Direction = normalize(vec3(direction.x, direction.y, direction.z));

	std::cout << m_Direction.x << ' ' << m_Direction.y << ' ' << m_Direction.z << ' ' << std::endl;

	// 利用Direction更新剩余的坐标向量
	m_Right = normalize(cross(m_Direction, m_WorldUp));
	m_Up = normalize(cross(m_Right, m_Direction));

}
