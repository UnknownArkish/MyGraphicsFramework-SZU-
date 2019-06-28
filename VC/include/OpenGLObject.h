
#ifndef _OPENGL_OBJECT_H_
#define _OPENGL_OBJECT_H_

#pragma once

#include"Angel.h"
#include<vector>

class OpenGLObject {
public:
	GLuint vao;

	std::vector<vec3> VertexPosition;		// 顶点属性 位置
	std::vector<vec3> VertexColor;			// 顶点属性 颜色
	std::vector<vec3> TextureCoordinate;	// 顶点属性 VT坐标
	std::vector<vec3> VertexNormal;			// 顶点属性 法向量

	OpenGLObject();
	~OpenGLObject();
private:
	void Init();
	void Clear();
};

#endif // !_OPENGL_OBJECT_H_
