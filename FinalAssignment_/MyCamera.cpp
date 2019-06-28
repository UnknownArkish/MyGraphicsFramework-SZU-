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
	// ��ʼ���������״̬
	this->SetPosition(position);
	m_WorldUp = up;
	m_Yaw = YAW;
	m_Pitch = PITCH;
	m_Front = vec3(0.0f, 0.0f, -1.0f);

	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;

	// ���������������ϵ
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
	// ���ʼ���
	float velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
	case My_Camera_Movement::Forward:				// ��ǰ�ƶ�
		ToTranslate(m_Front*velocity);
		break;
	case My_Camera_Movement::Backward:				// ����ƶ�
		ToTranslate(-m_Front*velocity);
		break;
	case My_Camera_Movement::Left:					// �����ƶ�
		ToTranslate(-m_Right * velocity);
		break;
	case My_Camera_Movement::Right:					// �����ƶ�
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
	// ���Ƹ����ǣ����������ƣ�������ᷭת
	if (constrainPitch) {
		if (m_Pitch > 89.0f)	m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)	m_Pitch = -89.0f;
	}
	// ���¸ı��ӽǽǶȺ�����������
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

	// ����ǰ������
	vec3 front;
	front.x = cos(Degree2Radians(m_Pitch)) * cos(Degree2Radians(m_Yaw));
	front.y = sin(Degree2Radians(m_Pitch));
	front.z = cos(Degree2Radians(m_Pitch)) * sin(Degree2Radians(m_Yaw));
	m_Front = normalize(front);
	// ����Front����ʣ�����������
	m_Right = normalize(cross(m_Front, m_WorldUp));
	m_Up = normalize(cross(m_Right, m_Front));
}
