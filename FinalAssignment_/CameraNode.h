
#ifndef _CAMERA_NODE_H_
#define _CAMERA_NODE_H_
#pragma once

#include"Node.h"

const vec3 DefaultDirection = vec3(0.0f, 0.0f, -1.0f);
const float ZOOM = 45.0f;		// 缩放度

class CameraNode :public Node
{
public:
	vec3 m_DefaultDirection;			// 默认方向
	vec3 m_Direction;					// 当前方向

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

	virtual void ToTranslate(vec3 translation)override;					// 移动函数，在原来基础上移动translation
	virtual void ToRotate(vec3 rotation)override;						// 旋转函数，在原来基础上旋转rotation
	virtual void ToScale(vec3 scale)override;							// 缩放函数，在原来基础上缩放scale

	virtual void SetPosition(vec3 position)override;					// 设置位置信息
	virtual void SetRotation(vec3 rotation)override;					// 设置旋转信息
	virtual void SetScale(vec3 scale)override;							// 设置缩放信息

	mat4 GetViewMatrix();				// 视图矩阵
	mat4 GetProjMatrix();				// 投影矩阵
private:
	// 更新相机坐标系的三个坐标向量
	void UpdateCameraVectors();
};




#endif // !_CAMERA_NODE_H_


