
/*
*	��պ�ϵͳ
*	��������һ������ķ���
*/

#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#pragma once

#include"Cube.h"
#include<Shader_GLUT.h>

class Skybox :public Cube
{
private:
	Shader* m_Shader;					// ��պ���ɫ��
	GLuint m_Vao;						// ��պ�vao
	
	std::vector<vec3>	m_VerticesPos;	// ����λ����Ϣ
private:
	static Skybox * m_Instance;
	Skybox();
	~Skybox();
public:
	static Skybox* GetInstance() { return m_Instance; }
protected:
	virtual bool Render() override;
	virtual bool Init()override;
public:
	static Skybox* Create();
private:
	void InitData();		// ��ʼ������
	void InitShader();		// ��ʼ����ɫ��
	void BindObject();		// ��OpenGL����
};



#endif // !_SKYBOX_H_


