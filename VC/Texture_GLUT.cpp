#include "include/Texture_GLUT.h"
#include"include/stb_image.h"

#include<iostream>

Texture::Texture(GLenum format)
	:Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
	Internal_Format = Image_Format = format;

	Type = Path = "";

	glGenTextures(1, &this->ID);
}

Texture::~Texture()
{
}

void Texture::Generate(GLuint width, GLuint height, unsigned char * data)
{
	this->Width = width;
	this->Height = height;
	// 创建贴图
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
	// 生成多级渐远纹理贴图
	glGenerateMipmap(GL_TEXTURE_2D);
	// 设置贴图环绕和滤波形式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

	// 解除绑定
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Generate(const char * filePath)
{
	int width, height, nrChannels;
	// 垂直翻转图片的读取信息
	stbi_set_flip_vertically_on_load(true);
	// 从文件中读取数据
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data) {
		// 创建、绑定OpenGL的Texture对象
		this->Generate(width, height, data);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
		return;
	}
	// 释放内存
	stbi_image_free(data);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
