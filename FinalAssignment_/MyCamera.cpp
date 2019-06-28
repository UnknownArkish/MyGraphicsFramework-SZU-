#include "MyCamera.h"



MyCamera::MyCamera()
{
}


MyCamera::~MyCamera()
{
}

bool MyCamera::Init(vec3 position, vec3 up)
{
	if (!Node::Init()) {
		return false;
	}
	// 初始化摄像机的状态
	this->SetPosition(position);
	m_WorldUp = up;
	m_Yaw = YAW;
	m_Pitch = PITCH;
	m_Front = vec3(0.0f, 0.0f, -1.0f);

	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;

	// 更新摄像机的坐标系
	UpdateCameraVectors();
	return true;
}

MyCamera * MyCamera::Create(vec3 position, vec3 up)
{
	MyCamera* pRet = new(std::nothrow)MyCamera();
	if (pRet && pRet->Init(position, up)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

mat4 MyCamera::GetViewMatrix()
{
	return LookAt(this->GetGlobalPosition(), this->GetGlobalPosition() + m_Front, m_Up);
}

mat4 MyCamera::GetProjMatrix()
{
	return Perspective(this->Zoom,
		(GLfloat)Config::Screen_Wdith / (GLfloat)Config::Screen_Height,
		0.1f, 15.0f);
}

vec3 MyCamera::GetFront()
{
	return m_Front;
}

void MyCamera::ProcessKeyboard(My_Camera_Movement direction, float deltaTime)
{
	// 速率计算
	float velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
	case My_Camera_Movement::Forward:				// 向前移动
		ToTranslate(m_Front*velocity);
		break;
	case My_Camera_Movement::Backward:				// 向后移动
		ToTranslate(-m_Front*velocity);
		break;
	case My_Camera_Movement::Left:					// 向左移动
		ToTranslate(-m_Right * velocity);
		break;
	case My_Camera_Movement::Right:					// 向右移动
		ToTranslate(m_Right * velocity);
		break;
	default:
		break;
	}
}

void MyCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;
	// 限制俯仰角，若不作限制，摄像机会翻转
	if (constrainPitch) {
		if (m_Pitch > 89.0f)	m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)	m_Pitch = -89.0f;
	}
	// 更新改变视角角度后的摄像机参数
	UpdateCameraVectors();
}

void MyCamera::ProcessMouseScroll(float yoffset)
{
	Zoom += yoffset;
	if (Zoom < 1.0f)	Zoom = 1.0f;
	if (Zoom > 45.0f)	Zoom = 45.0f;
}

void MyCamera::UpdateCameraVectors()
{
	float yaw = -m_Yaw - 90.0f;
	//this->SetRotation(vec3(m_Pitch, yaw, 0.0f));

	// 更新前向向量
	vec3 front;
	front.x = cos(Degree2Radians(m_Pitch)) * cos(Degree2Radians(m_Yaw));
	front.y = sin(Degree2Radians(m_Pitch));
	front.z = cos(Degree2Radians(m_Pitch)) * sin(Degree2Radians(m_Yaw));
	m_Front = normalize(front);
	// 利用Front更新剩余的坐标向量
	m_Right = normalize(cross(m_Front, m_WorldUp));
	m_Up = normalize(cross(m_Right, m_Front));
}
