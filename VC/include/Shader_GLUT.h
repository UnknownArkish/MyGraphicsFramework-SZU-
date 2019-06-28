/*********************************
* 
* ʹ��GLUT��Angel�汾����ɫ��������
* ע���Angel�ļ��о���Ϊ��ת�þ���
*
**********************************/

#ifndef _SHADER_GLUT_H_
#define _SHADER_GLUT_H_

#pragma once

#include<Angel.h>

class Shader
{
public:
	GLuint ID;				// ����ID
	Shader() {}
	Shader(const GLchar *vertexSource, const GLchar *fragmentSource, 
		const GLchar *geometrySource = nullptr) { Compile(vertexSource, fragmentSource, geometrySource); }
	~Shader() {}
	// ���õ�ǰ��ɫ��Ϊʹ��״̬
	Shader &Use();
	// ���ָ����ɫ���ļ�����ɫ��
	void Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);
	void CompileWithFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
	// ����uniform���������ɺ���
	void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, vec2 &value, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, vec3 &value, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, vec4 &value, GLboolean useShader = false);
	void    SetMatrix4(const GLchar *name, mat4 &matrix, GLboolean useShader = false);
	// ��ȡָ����������λ�õĺ���
	GLuint GetAttribLocation(const GLchar *name);
private:
	// �����롢���Ӵ�����Ϣ�����
	void    checkCompileErrors(GLuint object, std::string type);

	const GLchar* ReadShaderFile(const GLchar* shaderFilePath);
};


#endif // !_SHADER_GLUT_H_


