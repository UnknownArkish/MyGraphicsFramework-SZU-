
#ifndef _PLANE_RENDERER_H_
#define _PLANE_RENDERER_H_
#pragma once

#include"Renderer.h"
#include"Plane.h"

class PlaneRenderer :public Renderer
{
private:
	static PlaneRenderer* m_Instace;
	static Shader* m_Shader;
public:
	static PlaneRenderer* GetInstance() { return m_Instace; }
	static PlaneRenderer* Create();

private:
	GLuint m_PlaneVao;						// 用以绘制Plane的vao
protected:
	virtual bool Init();
	PlaneRenderer();

	// 通过 Renderer 继承
	virtual void LoadModel() override;
	virtual void InitData() override;
	virtual void InitShader() override;
	virtual void BindObject() override;
public:
	~PlaneRenderer();

	void Render(Plane* plane, bool toLighted = false);

	virtual void Render(mat4 modelMatrix, vec3 color, bool toLighted = false) override;
	virtual void Render(vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), vec3 scale = vec3(1.0f), vec3 color = vec3(1.0f), bool toLighted = false) override;
};



#endif // !_PLANE_RENDERER_H_-


