#ifndef _MY_CAMERA_H_
#define _MY_CAMERA_H_
#pragma once

#include<Angel.h>
#include"Node.h"

// ������������ƶ�����
enum My_Camera_Movement {
	Forward,
	Backward,
	Left,
	Right
};

// Ĭ�������������ֵ
const float YAW = -90.f;			// ƫ���ǣ�Ĭ����ǰ��
const float PITCH = 0.0f;			// �����ǣ�Ĭ��ƽ�ӣ�
const float SPEED = 0.89f;			// �ƶ��ٶ�
const float SENSITIVITY = 0.3f;		// ������ݶ�
const float ZOOM = 45.0f;			// ���Ŷ�

class MyCamera :public Node
{
private:
	// ���Կ��������λ����Ϣ��״̬����
	vec3 m_Front;					// ָʾ��ǰ������
	vec3 m_Up;						// �������ϵ�����Ϸ�����y�ᣩ
	vec3 m_Right;					// �������ϵ��x��
	vec3 m_WorldUp;					// ����������������
	float m_Yaw;					// ƫ����
	float m_Pitch;					// ������
public:
	// ���Կ����������ʾ���ƶ���״̬����
	float MovementSpeed;			// �ƶ��ٶ�
	float MouseSensitivity;			// ���������
	float Zoom;						// �۽�Zoom
protected:
	MyCamera();
	~MyCamera();
	virtual bool Init(vec3 position, vec3 up);
public:
	static MyCamera* Create(vec3 position = vec3(0.0f, 0.0f, 0.0f), 
		vec3 up = vec3(0.0f, 1.0f, 0.0f));

	// ����LookAt������ȡ��ͼ�任����
	mat4 GetViewMatrix();
	// ����ͶӰ�任�������õ�ͶӰ����
	mat4 GetProjMatrix();

	vec3 GetFront();

	// ������ƶ�����
	void ProcessKeyboard(My_Camera_Movement direction, float deltaTime);
	// ������ӽǱ任����
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// ������������ֺ����������ڷŴ�/��С
	void ProcessMouseScroll(float yoffset);
private:
	// �����������ϵ��������������
	void UpdateCameraVectors();
};



#endif // !_MY_CAMERA_H_


