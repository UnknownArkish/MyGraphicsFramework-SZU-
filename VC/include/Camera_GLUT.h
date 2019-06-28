
#ifndef _CAMERA_GLUT_H_
#define _CAMERA_GLUT_H_

#pragma once

#include<Angel.h>
#include<vector>

// ������������ƶ�����
enum Camera_Movement {
	Forward,
	Backward,
	Left,
	Right
};

// Ĭ�������������ֵ
const float YAW = -90.f;		// ƫ���ǣ�Ĭ����ǰ��
const float PITCH = 0.0f;		// �����ǣ�Ĭ��ƽ�ӣ�
const float SPEED = 2.5f;		// �ƶ��ٶ�
const float SENSITIVITY = 0.3f;	// ������ݶ�
const float ZOOM = 45.0f;		// ���Ŷ�

class Camera
{
public:
	vec3 Position;			// �������λ�ã��������ϵ��ԭ�㣩
	vec3 Front;				// ָʾ��ǰ������
	vec3 Up;				// �������ϵ�����Ϸ�����y�ᣩ
	vec3 Right;				// �������ϵ��x��
	vec3 WorldUp;			// ����������������

	float Yaw;				// ƫ����
	float Pitch;			// ������

	float MovementSpeed;	// �ƶ��ٶ�
	float MouseSensitivity;	// ���������
	float Zoom;

	// ���캯��
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
	// ����LookAt������ȡ��ͼ�任����
	mat4 GetViewMatrix();
	// �������Keyboard�����������ƶ�
	void ProcessKeyboard(Camera_Movement direction, float delteTime);
	// �������Mouse�����������ӽǸı�
	// @parm constrainPitch: �����Ƿ����Ƹ����ǣ�ע���������ƿ��ܻᷢ��������ķ�ת
	void ProcessMouseMovemonet(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// �������Scroll���������ԷŴ�/��С
	void ProcessMouseScroll(float yoffset);

private:
	// �����������ϵ��������������
	void updateCameraVectors();
};



#endif // !_CAMERA_GLUT_H_


