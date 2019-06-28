#include "include/Camera_GLUT.h"


mat4 Camera::GetViewMatrix()
{
	return LookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float delteTime)
{
	// 速率计算
	float velocity = MovementSpeed * delteTime;	
	switch (direction)
	{
		case Camera_Movement::Forward:				// 向前移动
			Position += Front * velocity;
			break;
		case Camera_Movement::Backward:				// 向后移动
			Position -= Front * velocity;
			break;
		case Camera_Movement::Left:					// 向左移动
			Position -= Right * velocity;
			break;
		case Camera_Movement::Right:				// 向右移动
			Position += Right * velocity;
			break;
		default:
			break;
	}
}

// xoffset、yoffset为鼠标偏移值；constrainPitch为是否翻转y轴方向
void Camera::ProcessMouseMovemonet(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;
	// 限制俯仰角，若不作限制，摄像机会翻转
	if (constrainPitch) {
		if (Pitch > 89.0f)	Pitch = 89.0f;
		if (Pitch < -89.0f)	Pitch = -89.0f;
	}
	// 更新改变视角角度后的摄像机参数
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
	// 更新前向向量
	vec3 front;
	front.x = cos(Degree2Radians(Pitch)) * cos(Degree2Radians(Yaw));
	front.y = sin(Degree2Radians(Pitch));
	front.z = cos(Degree2Radians(Pitch)) * sin(Degree2Radians(Yaw));
	Front = normalize(front);
	// 利用Front更新剩余的坐标向量
	Right = normalize(cross(Front, WorldUp));
	Up = normalize(cross(Right, Front));
}
