
#ifndef _RESOURCE_MANAGER_GLUT_H_
#define _RESOURCE_MANAGER_GLUT_H_
#pragma once

#include"Angel.h"

#include<map>
#include<string>

#include"Shader_GLUT.h"
#include"Texture_GLUT.h"

class ResourceManager
{
private:
	static ResourceManager * m_Instance;
public:
	static ResourceManager* GetInstance();

	// 着色器名字-着色器程序
	static std::map<std::string, Shader*> Shaders;
	// 贴图名字-贴图
	static std::map<std::string, Texture*> Textures;
public:

	Shader* LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
	Texture* LoadTexture(const GLchar* picFilee, GLboolean isAlpha, std::string name);

	Shader* GetShader(std::string name);
	Texture* GetTexture(std::string name);

	void Clear();
private:
	ResourceManager();
	~ResourceManager();

	Shader* LoadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile);
	Texture* LoadTextureFromFile(const GLchar* picFilee, GLboolean isAlpha);
};



#endif // !_RESOURCE_MANAGER_GLUT_H_


