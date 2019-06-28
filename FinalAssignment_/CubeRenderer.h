
#ifndef _CUBE_RENDERER_H_
#define _CUBE_RENDERER_H_
#pragma once

#include"Renderer.h"
#include<OFFMesh.h>

#include"Cube.h"

class CubeRenderer:public Renderer
{
private:
	static CubeRenderer* m_Instance;
	static Shader* m_Shader;
public:
	static CubeRenderer* GetInstance() { return m_Instance; }
	static CubeRenderer* Create();
private:
	virtual bool Init();
private:
	GLuint m_CubeVao;					// 普通方块Vao
	GLuint m_SkyboxVao;					// 天空盒vao
	OFFMesh* m_Mesh;
	std::vector<vec3> m_CubeVertexPos;		// 顶点属性 位置信息
	std::vector<vec3> m_CubeNormals;		// 顶点属性 法向量信息
protected:
	CubeRenderer();
	~CubeRenderer();

	// 通过 Renderer 继承
	virtual void LoadModel() override;
	virtual void InitData() override;
	virtual void InitShader() override;
	virtual void BindObject() override;
public:
	void Render(Cube* cube);				// 根据参数中的cube对象进行绘制


	// 通过 Renderer 继承
	virtual void Render(vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), vec3 scale = vec3(1.0f), vec3 color = vec3(1.0f), bool toLighted = false) override;
	virtual void Render(mat4 modelMatrix, vec3 color, bool toLighted = false) override;
private:
	void GenerateShadow(Cube* cube);						// 产生阴影
};


#endif // !_CUBE_RENDERER_H_


