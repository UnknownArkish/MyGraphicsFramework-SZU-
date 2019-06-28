/*
*	GLUT�汾��Texture��
*	���Է���Ĵ�����ʹ��Texture
*/


#ifndef _TEXTURE_GLUT_H_
#define _TEXTURE_GLUT_H_

#pragma once

#include"Angel.h"

class Texture
{
public:
	// Texture��OpenGL�е�ID������ֵ��
	GLuint ID;
	std::string Type;			// ��ͼ����
	std::string Path;			// ��ͼ·��
	// Texture��ͼ�ֱ���
	GLuint Width, Height;		// ������Ϊ��λ������ͼ
	// Texture��ʽ
	GLuint Internal_Format;		// ��������ʽ
	GLuint Image_Format;		// ��ͼ��Դ��ʽ
	// ��ͼ����
	GLuint Wrap_S;				// S�ỷ����ʽ
	GLuint Wrap_T;				// T�ỷ����ʽ
	GLuint Filter_Min;			// �������ر���Ļ����Сʱ�˲���ʽ
	GLuint Filter_Max;			// �������ر���Ļ���ش�ʱ�˲���ʽ

	Texture(GLenum format);
	~Texture();

	// ����������ͼ
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Generate(const char* filePath);
	// ʹ����ͼ
	void Bind() const;
};

#endif // !_TEXTURE_GLUT_H_



