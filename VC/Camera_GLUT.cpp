#include "include/Camera_GLUT.h"


mat4 Camera::GetViewMatrix()
{
	return LookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float delteTime)
{
	// ���ʼ���
	float velocity = MovementSpeed * delteTime;	
	switch (direction)
	{
		case Camera_Movement::Forward:				// ��ǰ�ƶ�
			Position += Front * velocity;
			break;
		case Camera_Movement::Backward:				// ����ƶ�
			Position -= Front * velocity;
			break;
		case Camera_Movement::Left:					// �����ƶ�
			Position -= Right * velocity;
			break;
		case Camera_Movement::Right:				// �����ƶ�
			Position += Right * velocity;
			break;
		default:
			break;
	}
}

// xoffset��yoffsetΪ���ƫ��ֵ��constrainPitchΪ�Ƿ�תy�᷽��
void Camera::ProcessMouseMovemonet(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;
	// ���Ƹ����ǣ����������ƣ�������ᷭת
	if (constrainPitch) {
		if (Pitch > 89.0f)	Pitch = 89.0f;
		if (Pitch < -89.0f)	Pitch = -89.0f;
	}
	// ���¸ı��ӽǽǶȺ�����������
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom += yoffset;
	if (Zoom < 1.0f)	Zoom = 1.0f;
	if (Zoom > 45.0f)	Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	// ����ǰ������
	vec3 front;
	front.x = cos(Degree2Radians(Pitch)) * cos(Degree2Radians(Yaw));
	front.y = sin(Degree2Radians(Pitch));
	front.z = cos(Degree2Radians(Pitch)) * sin(Degree2Radians(Yaw));
	Front = normalize(front);
	// ����Front����ʣ�����������
	Right = normalize(cross(Front, WorldUp));
	Up = normalize(cross(Right, Front));
}
