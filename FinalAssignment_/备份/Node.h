
#ifndef _NODE_H_
#define _NODE_H_
#pragma once

#include"stdafx.h"
#include"Ref.h"

class Node :public Ref
{
protected:
	Node();
	~Node();
protected:
	Node * m_Parent;
	std::vector<Node*> m_Childrens;
private:
	vec3 m_LocalX;						// 本地X坐标轴
	vec3 m_LocalY;						// 本地Y坐标轴
	vec3 m_LocalZ;						// 本地Z坐标轴

	vec3 m_GlobalX;						// 本地X坐标轴
	vec3 m_GlobalY;						// 本地Y坐标轴
	vec3 m_GlobalZ;						// 本地Z坐标轴

	bool m_Visiable;					// 是否可见
	vec3 m_Anchor;						// 锚点
	// 几何变换，相对于父节点
	vec3 m_Position;					// 位置信息
	vec3 m_Rotation;					// 旋转信息
	vec3 m_Scale;						// 缩放信息

	// 世界坐标系下
	vec3 m_GlobalPosition;
	vec3 m_GlobalRotation;
	vec3 m_GlobalScale;

	mat4 m_ModelMatrix_Local;			// 模型矩阵（本地）
	mat4 m_ModelMatrix_Global;			// 模型矩阵
protected:
	virtual bool Render();				// 渲染函数，在这里进行OpenGL对象的绘制
	virtual bool Init();
	virtual void Update(float deltaTime)override;				// 重写Update函数
public:
	static Node* Create();
	virtual void ToUpdate(float deltaTime)override;

	virtual void SetParent(Node* node);							// 设置父节点
	virtual Node* GetParent();									// 获得父节点

	virtual void AddChildren(Node* node);						// 添加子节点
	virtual void RemoveChildren(Node* node);					// 移除子节点
	std::vector<Node*> GetAllChilder();							// 返回所有子节点

	virtual void SetVisiable(bool visable) { m_Visiable = visable; }
	bool IsVisalbe() { return m_Visiable; }

	virtual void SetAnchor(vec3 anchor);
	vec3 GetAnchor() { return m_Anchor; }

	// 几何变换函数，相对于父节点
	virtual void ToTranslate(vec3 translation);					// 移动函数，在原来基础上移动translation
	virtual void ToRotate(vec3 rotation);						// 旋转函数，在原来基础上旋转rotation
	virtual void ToScale(vec3 scale);							// 缩放函数，在原来基础上缩放scale

	virtual void SetPosition(vec3 position);					// 设置位置信息
	virtual void SetRotation(vec3 rotation);					// 设置旋转信息
	virtual void SetScale(vec3 scale);							// 设置缩放信息

	vec3 GetPosition() { return m_Position; }
	vec3 GetRotation() { return m_Rotation; }
	vec3 GetScale() { return m_Scale; }

	vec3 GetGlobalPosition() { return m_GlobalPosition; }
	vec3 GetGlobalRotation() { return m_GlobalRotation; }
	vec3 GetGlobalScale() { return m_GlobalScale; }

	vec3 GetLocalX() { return m_LocalX; }
	vec3 GetLocalY() { return m_LocalY; }
	vec3 GetLocalZ() { return m_LocalZ; }

	vec3 GetGlobalX() { return m_GlobalX; }
	vec3 GetGlobalY() { return m_GlobalY; }
	vec3 GetGlobalZ() { return m_GlobalZ; }

	mat4 GetGlobalMatrix() { return m_ModelMatrix_Global; }
	mat4 GetLocalMatrix() { return m_ModelMatrix_Local; }

	virtual void Display();
private:
	void UpdateLocalPosition();
	void UpdateLocalRotation();
	void UpdateLocalScale();

	void UpdateGlobalPosition();
	void UpdateGlobalRotation();
	void UpdateGlobalScale();

	void UpdateModelMatrix();									// 更新模型矩阵
	
	void UpdateCoordinate();									// 更新坐标系的函数
	void UpdateLocalCoordinate();								// 更新本地坐标系的函数
	void UpdateGlobalCoordinate();								// 更新世界坐标系的函数
};



#endif // !_NODE_H_


