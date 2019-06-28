/*********************************
* 
* 使用GLUT、Angel版本的着色器程序类
* 注意此Angel文件中矩阵为非转置矩阵
*
**********************************/

#ifndef _SHADER_GLUT_H_
#define _SHADER_GLUT_H_

#pragma once

#include<Angel.h>

class Shader
{
public:
	GLuint ID;				// 程序ID
	Shader() {}
	Shader(const GLchar *vertexSource, const GLchar *fragmentSource, 
		const GLchar *geometrySource = nullptr) { Compile(vertexSource, fragmentSource, geometrySource); }
	~Shader() {}
	// 设置当前着色器为使用状态
	Shader &Use();
	// 编程指定着色器文件的着色器
	void Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);
	void CompileWithFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
	// 设置uniform变量的若干函数
	void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, vec2 &value, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, vec3 &value, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, vec4 &value, GLboolean useShader = false);
	void    SetMatrix4(const GLchar *name, mat4 &matrix, GLboolean useShader = false);
	// 获取指定顶点属性位置的函数
	GLuint GetAttribLocation(const GLchar *name);
private:
	// 检查编译、链接错误信息并输出
	void    checkCompileErrors(GLuint object, std::string type);

	const GLchar* ReadShaderFile(const GLchar* shaderFilePath);
};


#endif // !_SHADER_GLUT_H_


