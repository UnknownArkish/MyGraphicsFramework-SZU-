
#ifndef _RENDERER_H_
#define _RENDERER_H_
#pragma once

#include<ResourceManager_GLUT.h>
#include"Ref.h"

class Renderer:public Ref
{
protected:
	Renderer();
	~Renderer();

	virtual bool Init();
	virtual void LoadModel() = 0;
	virtual void InitData() = 0;
	virtual void InitShader() = 0;
	virtual void BindObject() = 0;
public:
	virtual void Render(mat4 modelMatrix, vec3 color, bool toLighted = false) = 0;
	virtual void Render(vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), vec3 scale = vec3(1.0f), vec3 color = vec3(1.0f), bool toLighted = false) = 0;
};



#endif // !_RENDERER_H_


