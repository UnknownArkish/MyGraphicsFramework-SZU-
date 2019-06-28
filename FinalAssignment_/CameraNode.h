
#ifndef _CAMERA_NODE_H_
#define _CAMERA_NODE_H_
#pragma once

#include"Node.h"

const vec3 DefaultDirection = vec3(0.0f, 0.0f, -1.0f);
const float ZOOM = 45.0f;		// ���Ŷ�

class CameraNode :public Node
{
public:
	vec3 m_DefaultDirection;			// Ĭ�Ϸ���
	vec3 m_Direction;					// ��ǰ����

	vec3 m_Right;
	vec3 m_Up;
	vec3 m_WorldUp;

	float Zoom;
protected:
	CameraNode();

	virtual bool Init(vec3 position, vec3 up);
public:
	~CameraNode();

	static CameraNode* Create(vec3 position = vec3(0.0f, 0.0f, 0.0f),
		vec3 up = vec3(0.0f, 1.0f, 0.0f));

	virtual void ToTranslate(vec3 translation)override;					// �ƶ���������ԭ���������ƶ�translation
	virtual void ToRotate(vec3 rotation)override;						// ��ת��������ԭ����������תrotation
	virtual void ToScale(vec3 scale)override;							// ���ź�������ԭ������������scale

	virtual void SetPosition(vec3 position)override;					// ����λ����Ϣ
	virtual void SetRotation(vec3 rotation)override;					// ������ת��Ϣ
	virtual void SetScale(vec3 scale)override;							// ����������Ϣ

	mat4 GetViewMatrix();				// ��ͼ����
	mat4 GetProjMatrix();				// ͶӰ����
private:
	// �����������ϵ��������������
	void UpdateCameraVectors();
};




#endif // !_CAMERA_NODE_H_


