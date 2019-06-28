#ifndef _MY_CAMERA_H_
#define _MY_CAMERA_H_
#pragma once

#include<Angel.h>
#include"Node.h"

// 定义摄像机的移动方向
enum My_Camera_Movement {
	Forward,
	Backward,
	Left,
	Right
};

// 默认摄像机参数数值
const float YAW = -90.f;			// 偏航角（默认向前）
const float PITCH = 0.0f;			// 俯仰角（默认平视）
const float SPEED = 0.89f;			// 移动速度
const float SENSITIVITY = 0.3f;		// 鼠标敏捷度
const float ZOOM = 45.0f;			// 缩放度

class MyCamera :public Node
{
private:
	// 用以控制摄像机位置信息的状态变量
	vec3 m_Front;					// 指示向前的向量
	vec3 m_Up;						// 相机坐标系下向上分量（y轴）
	vec3 m_Right;					// 相机坐标系下x轴
	vec3 m_WorldUp;					// 世界坐标向上向量
	float m_Yaw;					// 偏航角
	float m_Pitch;					// 俯仰角
public:
	// 用以控制摄像机显示、移动的状态变量
	float MovementSpeed;			// 移动速度
	float MouseSensitivity;			// 鼠标灵敏度
	float Zoom;						// 聚焦Zoom
protected:
	MyCamera();
	~MyCamera();
	virtual bool Init(vec3 position, vec3 up);
public:
	static MyCamera* Create(vec3 position = vec3(0.0f, 0.0f, 0.0f), 
		vec3 up = vec3(0.0f, 1.0f, 0.0f));

	// 根据LookAt函数获取视图变换矩阵
	mat4 GetViewMatrix();
	// 根据投影变换函数，得到投影矩阵
	mat4 GetProjMatrix();

	vec3 GetFront();

	// 摄像机移动函数
	void ProcessKeyboard(My_Camera_Movement direction, float deltaTime);
	// 摄像机视角变换函数
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// 摄像机的鼠标滚轮函数，可用于放大/缩小
	void ProcessMouseScroll(float yoffset);
private:
	// 更新相机坐标系的三个坐标向量
	void UpdateCameraVectors();
};



#endif // !_MY_CAMERA_H_


