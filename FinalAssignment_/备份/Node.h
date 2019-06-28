
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
	vec3 m_LocalX;						// ����X������
	vec3 m_LocalY;						// ����Y������
	vec3 m_LocalZ;						// ����Z������

	vec3 m_GlobalX;						// ����X������
	vec3 m_GlobalY;						// ����Y������
	vec3 m_GlobalZ;						// ����Z������

	bool m_Visiable;					// �Ƿ�ɼ�
	vec3 m_Anchor;						// ê��
	// ���α任������ڸ��ڵ�
	vec3 m_Position;					// λ����Ϣ
	vec3 m_Rotation;					// ��ת��Ϣ
	vec3 m_Scale;						// ������Ϣ

	// ��������ϵ��
	vec3 m_GlobalPosition;
	vec3 m_GlobalRotation;
	vec3 m_GlobalScale;

	mat4 m_ModelMatrix_Local;			// ģ�;��󣨱��أ�
	mat4 m_ModelMatrix_Global;			// ģ�;���
protected:
	virtual bool Render();				// ��Ⱦ���������������OpenGL����Ļ���
	virtual bool Init();
	virtual void Update(float deltaTime)override;				// ��дUpdate����
public:
	static Node* Create();
	virtual void ToUpdate(float deltaTime)override;

	virtual void SetParent(Node* node);							// ���ø��ڵ�
	virtual Node* GetParent();									// ��ø��ڵ�

	virtual void AddChildren(Node* node);						// ����ӽڵ�
	virtual void RemoveChildren(Node* node);					// �Ƴ��ӽڵ�
	std::vector<Node*> GetAllChilder();							// ���������ӽڵ�

	virtual void SetVisiable(bool visable) { m_Visiable = visable; }
	bool IsVisalbe() { return m_Visiable; }

	virtual void SetAnchor(vec3 anchor);
	vec3 GetAnchor() { return m_Anchor; }

	// ���α任����������ڸ��ڵ�
	virtual void ToTranslate(vec3 translation);					// �ƶ���������ԭ���������ƶ�translation
	virtual void ToRotate(vec3 rotation);						// ��ת��������ԭ����������תrotation
	virtual void ToScale(vec3 scale);							// ���ź�������ԭ������������scale

	virtual void SetPosition(vec3 position);					// ����λ����Ϣ
	virtual void SetRotation(vec3 rotation);					// ������ת��Ϣ
	virtual void SetScale(vec3 scale);							// ����������Ϣ

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

	void UpdateModelMatrix();									// ����ģ�;���
	
	void UpdateCoordinate();									// ��������ϵ�ĺ���
	void UpdateLocalCoordinate();								// ���±�������ϵ�ĺ���
	void UpdateGlobalCoordinate();								// ������������ϵ�ĺ���
};



#endif // !_NODE_H_


