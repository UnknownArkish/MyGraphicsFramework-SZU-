
#ifndef _CAMERA_GLUT_H_
#define _CAMERA_GLUT_H_

#pragma once

#include<Angel.h>
#include<vector>

// 定义摄像机的移动方向
enum Camera_Movement {
	Forward,
	Backward,
	Left,
	Right
};

// 默认摄像机参数数值
const float YAW = -90.f;		// 偏航角（默认向前）
const float PITCH = 0.0f;		// 俯仰角（默认平视）
const float SPEED = 2.5f;		// 移动速度
const float SENSITIVITY = 0.3f;	// 鼠标敏捷度
const float ZOOM = 45.0f;		// 缩放度

class Camera
{
public:
	vec3 Position;			// 摄像机的位置（相机坐标系下原点）
	vec3 Front;				// 指示向前的向量
	vec3 Up;				// 相机坐标系下向上分量（y轴）
	vec3 Right;				// 相机坐标系下x轴
	vec3 WorldUp;			// 世界坐标向上向量

	float Yaw;				// 偏航角
	float Pitch;			// 俯仰角

	float MovementSpeed;	// 移动速度
	float MouseSensitivity;	// 鼠标灵敏度
	float Zoom;

	// 构造函数
	Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f),
		vec3 up = vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW, float pitch = PITCH
	) :Front(vec3(0.0f, 0.0f, -1.0)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),Zoom(ZOOM) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	Camera(float posX, float posY, float posZ,
		float upX, float upY, float upZ,
		float yaw, float pitch
	) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = vec3(posX, posY, posZ);
		WorldUp = vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// 根据LookAt函数获取视图变换矩阵
	mat4 GetViewMatrix();
	// 摄像机的Keyboard函数，用以移动
	void ProcessKeyboard(Camera_Movement direction, float delteTime);
	// 摄像机的Mouse函数，用以视角改变
	// @parm constrainPitch: 设置是否限制俯仰角，注意若不限制可能会发生摄像机的翻转
	void ProcessMouseMovemonet(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// 摄像机的Scroll函数，用以放大/缩小
	void ProcessMouseScroll(float yoffset);

private:
	// 更新相机坐标系的三个坐标向量
	void updateCameraVectors();
};



#endif // !_CAMERA_GLUT_H_


