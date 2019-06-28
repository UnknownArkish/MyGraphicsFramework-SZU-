#include "ResourcesSystem.h"

#include<fstream>
#include<sstream>

ResourcesSystem* ResourcesSystem::m_Instance = nullptr;
std::map<std::string, Shader*> ResourcesSystem::m_Shaders;
std::map<std::string, Texture*> ResourcesSystem::m_Textures;
std::map<std::string, Animation> ResourcesSystem::m_Animations;
std::map<std::string, CubeMap*> ResourcesSystem::m_CubeMaps;
std::map<std::string, ModelResource*> ResourcesSystem::m_ModelResources;

ResourcesSystem::ResourcesSystem()
{
}


ResourcesSystem::~ResourcesSystem()
{
}

bool ResourcesSystem::Init()
{
	if (!Ref::Init()) {
		return false;
	}

	// @TODO：ResourcesSystem的初始化

	return true;
}

ResourcesSystem * ResourcesSystem::Create()
{
	if (m_Instance == nullptr) {
		m_Instance = new (std::nothrow)ResourcesSystem();
		if (m_Instance&&m_Instance->Init()) {
			return m_Instance;
		}
		delete m_Instance;
		m_Instance = nullptr;
		return nullptr;
	}
	return m_Instance;
}

Shader * ResourcesSystem::LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFIle, const GLchar * gShaderFile, std::string name)
{
	if (m_Shaders.find(name) == m_Shaders.end()) {
		m_Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFIle, gShaderFile);
	}
	return m_Shaders[name];
}

Texture * ResourcesSystem::LoadTexture(const GLchar * picFile, const GLchar* type, std::string name)
{
	stbi_set_flip_vertically_on_load(true);			// y轴翻转加载的图片
	if (m_Textures.find(name) == m_Textures.end()) {
		m_Textures[name] = LoadTextureFromFile(picFile, type);
	}
	return m_Textures[name];
}

Animation ResourcesSystem::LoadAnimation(const GLchar * folderPath, std::string name)
{
	if (m_Animations.find(name) == m_Animations.end()) {
		Animation animation;
		int index = 0;
		char name_children[128];
		std::vector<std::string> fileNames = Tools::GetInstance()->GetFileNameInFolder(folderPath);
		for (std::string fileName : fileNames) {
			sprintf_s(name_children, "%s_%d", name.c_str(), index++);

			Texture* texture = LoadTexture(fileName.c_str(), "", name_children);
			animation.push_back(texture);
		}
		m_Animations[name] = animation;
	}
	return m_Animations[name];
}

CubeMap * ResourcesSystem::LoadCubeMap(std::vector<std::string> faces, std::string name)
{
	if (m_CubeMaps.find(name) == m_CubeMaps.end()) {
		m_CubeMaps[name] = CubeMap::Create(faces);
	}
	return m_CubeMaps[name];
}

CubeMap * ResourcesSystem::LoadCubeMap(const GLchar * folderPath, std::string name)
{
	if (m_CubeMaps.find(name) == m_CubeMaps.end()) {
		std::vector<std::string> faces;
		char facePath[128];
		sprintf_s(facePath, "%s/%s_ft.tga", folderPath, name.c_str());
		faces.push_back(facePath);
		sprintf_s(facePath, "%s/%s_bk.tga", folderPath, name.c_str());
		faces.push_back(facePath);
		sprintf_s(facePath, "%s/%s_up.tga", folderPath, name.c_str());
		faces.push_back(facePath);
		sprintf_s(facePath, "%s/%s_dn.tga", folderPath, name.c_str());
		faces.push_back(facePath);
		sprintf_s(facePath, "%s/%s_rt.tga", folderPath, name.c_str());
		faces.push_back(facePath);
		sprintf_s(facePath, "%s/%s_lf.tga", folderPath, name.c_str());
		faces.push_back(facePath);
		return LoadCubeMap(faces, name);
	}
	else {
		return m_CubeMaps[name];
	}
}

ModelResource* ResourcesSystem::LoadModel(const GLchar * modelFile, std::string name)
{
	if (m_ModelResources.find(name) == m_ModelResources.end()) {
		m_ModelResources[name] = LoadModelResourceFromFile(modelFile);
	}
	return m_ModelResources[name];
}

Shader * ResourcesSystem::GetShader(std::string name)
{
	Shader* shader = nullptr;
	if (m_Shaders.find(name) != m_Shaders.end()) {
		shader = m_Shaders[name];
	}
	return shader;
}

Texture * ResourcesSystem::GetTexture(std::string name)
{
	Texture* texture = nullptr;
	if (m_Textures.find(name) != m_Textures.end()) {
		texture = m_Textures[name];
	}
	return texture;
}

Animation ResourcesSystem::GetAnimation(std::string name)
{
	Animation animation;
	if (m_Animations.find(name) != m_Animations.end()) {
		animation = m_Animations[name];
	}
	return animation;
}

CubeMap * ResourcesSystem::GetCubeMap(std::string name)
{
	CubeMap* map = nullptr;
	if (m_CubeMaps.find(name) != m_CubeMaps.end()) {
		map = m_CubeMaps[name];
	}
	return map;
}

ModelResource* ResourcesSystem::GetModelResource(std::string name)
{
	ModelResource* model = nullptr;
	if (m_ModelResources.find(name) != m_ModelResources.end()) {
		model = m_ModelResources[name];
	}
	return model;
}

Shader * ResourcesSystem::LoadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
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

Texture * ResourcesSystem::LoadTextureFromFile(const GLchar * picFile, const GLchar* type)
{
	Texture* texture = nullptr;

	// 加载图片
	int width, height, nrChannels;
	unsigned char *data = stbi_load(picFile, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)	format = GL_RED;
		else if (nrChannels == 3)	format = GL_RGB;
		else if (nrChannels == 4)	format = GL_RGBA;
		// 创建贴图对象
		texture = new Texture(format);
		texture->Path = std::string(picFile);
		texture->Type = std::string(type);
		texture->Generate(width, height, data);
		// 释放内存中的图片数据
		stbi_image_free(data);
	}
	else {
		std::cout << "Can't not open Texture!!!" << std::endl;
	}
	return texture;
}

ModelResource* ResourcesSystem::LoadModelResourceFromFile(const GLchar * modelFile)
{
	ModelResource* model = nullptr;

	Assimp::Importer importer;
	importer.ReadFile(modelFile, aiProcess_Triangulate);
	aiScene* scene = importer.GetOrphanedScene();
	// 检查读取的scene是否有效
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return model;
	}

	// 创建模型资源对象
	model = new ModelResource();
	model->ModelScene = scene;
	std::string path = std::string(modelFile);
	model->Directory = path.substr(0, path.find_last_of('/'));

	return model;
}
