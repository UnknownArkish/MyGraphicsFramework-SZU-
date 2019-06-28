/*
*	GLUT版本的Texture类
*	可以方便的创建和使用Texture
*/


#ifndef _TEXTURE_GLUT_H_
#define _TEXTURE_GLUT_H_

#pragma once

#include"Angel.h"

class Texture
{
public:
	// Texture在OpenGL中的ID（索引值）
	GLuint ID;
	std::string Type;			// 贴图类型
	std::string Path;			// 贴图路径
	// Texture贴图分辨率
	GLuint Width, Height;		// 以像素为单位加载贴图
	// Texture格式
	GLuint Internal_Format;		// 纹理对象格式
	GLuint Image_Format;		// 贴图资源格式
	// 贴图配置
	GLuint Wrap_S;				// S轴环绕形式
	GLuint Wrap_T;				// T轴环绕形式
	GLuint Filter_Min;			// 纹理像素比屏幕像素小时滤波形式
	GLuint Filter_Max;			// 纹理像素比屏幕像素大时滤波形式

	Texture(GLenum format);
	~Texture();

	// 创建纹理贴图
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Generate(const char* filePath);
	// 使用贴图
	void Bind() const;
};

#endif // !_TEXTURE_GLUT_H_



