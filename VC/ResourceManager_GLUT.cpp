#include "ResourceManager_GLUT.h"

#include<iostream>
#include<sstream>
#include<fstream>

#include"include/stb_image.h"

ResourceManager* ResourceManager::m_Instance = nullptr;

std::map<std::string, Shader*> ResourceManager::Shaders;
std::map<std::string, Texture*> ResourceManager::Textures;

ResourceManager * ResourceManager::GetInstance()
{
	if (m_Instance == nullptr) {
		m_Instance = new ResourceManager();
	}
	return m_Instance;
}

Shader * ResourceManager::LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, std::string name)
{
	if (Shaders.find(name) == Shaders.end()) {
		Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	}
	return Shaders[name];
}

Texture * ResourceManager::LoadTexture(const GLchar * picFile, GLboolean isAlpha, std::string name)
{
	if (Textures.find(name) == Textures.end()) {
		Textures[name] = LoadTextureFromFile(picFile, isAlpha);
	}
	return Textures[name];
}

Shader * ResourceManager::GetShader(std::string name)
{
	Shader* shader = nullptr;
	if (Shaders.find(name) != Shaders.end()) {
		shader = Shaders[name];
	}
	return shader;
}

Texture * ResourceManager::GetTexture(std::string name)
{
	Texture* texture = nullptr;
	if (Textures.find(name) != Textures.end()) {
		texture = Textures[name];
	}
	return texture;
}

void ResourceManager::Clear()
{
	for (auto iter : Shaders) {
		glDeleteProgram(iter.second->ID);
	}
	for (auto iter : Textures) {
		glDeleteTextures(1, &iter.second->ID);
	}
	Shaders.clear();
	Textures.clear();
}

ResourceManager::ResourceManager()
{
	stbi_set_flip_vertically_on_load(true);
}


ResourceManager::~ResourceManager()
{
}

Shader * ResourceManager::LoadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
{
	// 从文件中获取着色器程序代码
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// 打开文件
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// 从文件中读取缓冲流
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// 关闭文件流
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// 将流转换为字符串
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// 若几何着色器指定，则读取之
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader* shader = new Shader();
	shader->Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture * ResourceManager::LoadTextureFromFile(const GLchar * picFilee, GLboolean isAlpha)
{
	// Create Texture object
	Texture* texture = nullptr;
	// Load image
	int width, height, nrChannels;
	unsigned char *data = stbi_load(picFilee, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)	format = GL_RED;
		else if (nrChannels == 3)	format = GL_RGB;
		else if (nrChannels == 4)	format = GL_RGBA;

		texture = new Texture(format);

		// Now generate texture
		texture->Generate(width, height, data);
		// And finally free image data
		stbi_image_free(data);
	}
	else {
		std::cout << "Can't not open Texture!!!" << std::endl;
	}
	return texture;
}
