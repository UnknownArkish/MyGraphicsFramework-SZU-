
#ifndef _OPENGL_OBJECT_H_
#define _OPENGL_OBJECT_H_

#pragma once

#include"Angel.h"
#include<vector>

class OpenGLObject {
public:
	GLuint vao;

	std::vector<vec3> VertexPosition;		// �������� λ��
	std::vector<vec3> VertexColor;			// �������� ��ɫ
	std::vector<vec3> TextureCoordinate;	// �������� VT����
	std::vector<vec3> VertexNormal;			// �������� ������

	OpenGLObject();
	~OpenGLObject();
private:
	void Init();
	void Clear();
};

#endif // !_OPENGL_OBJECT_H_
