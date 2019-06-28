
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
	GLuint m_CubeVao;					// ��ͨ����Vao
	GLuint m_SkyboxVao;					// ��պ�vao
	OFFMesh* m_Mesh;
	std::vector<vec3> m_CubeVertexPos;		// �������� λ����Ϣ
	std::vector<vec3> m_CubeNormals;		// �������� ��������Ϣ
protected:
	CubeRenderer();
	~CubeRenderer();

	// ͨ�� Renderer �̳�
	virtual void LoadModel() override;
	virtual void InitData() override;
	virtual void InitShader() override;
	virtual void BindObject() override;
public:
	void Render(Cube* cube);				// ���ݲ����е�cube������л���


	// ͨ�� Renderer �̳�
	virtual void Render(vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), vec3 scale = vec3(1.0f), vec3 color = vec3(1.0f), bool toLighted = false) override;
	virtual void Render(mat4 modelMatrix, vec3 color, bool toLighted = false) override;
private:
	void GenerateShadow(Cube* cube);						// ������Ӱ
};


#endif // !_CUBE_RENDERER_H_


