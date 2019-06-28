
/*
*	天空盒系统
*	本质上是一个特殊的方块
*/

#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#pragma once

#include"Cube.h"
#include<Shader_GLUT.h>

class Skybox :public Cube
{
private:
	Shader* m_Shader;					// 天空盒着色器
	GLuint m_Vao;						// 天空盒vao
	
	std::vector<vec3>	m_VerticesPos;	// 顶点位置信息
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
	void InitData();		// 初始化数据
	void InitShader();		// 初始化着色器
	void BindObject();		// 绑定OpenGL对象
};



#endif // !_SKYBOX_H_


