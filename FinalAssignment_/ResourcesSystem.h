/*
*	资源管理器
*	负责存储着色器、贴图以及模型信息
*/


#ifndef _RESOURCES_SYSTEM_H_
#define _RESOURCES_SYSTEM_H_
#pragma once

#include<assimp\Importer.hpp>
#include<assimp\scene.h>
#include<assimp\postprocess.h>
#include<stb_image.h>

#include<Shader_GLUT.h>			// 着色器
#include<Texture_GLUT.h>		// 贴图
#include"CubeMap.h"
#include"ModelResource.h"
#include<vector>
#include<map>
#include"Ref.h"
#include"Animation.h"

//typedef aiScene ModelResource;			// 将aiScene定义为加载的模型文件资源
//typedef std::vector<Texture*> Animation;

class ResourcesSystem:public Ref
{
private:
	static ResourcesSystem * m_Instance;
private:
	ResourcesSystem();
	~ResourcesSystem();
	virtual bool Init()override;
public:
	static ResourcesSystem* Create();
	static ResourcesSystem* GetInstance() { return m_Instance; }
private:
	static std::map<std::string, Shader*> m_Shaders;					// 保存的着色器
	static std::map<std::string, Texture*> m_Textures;					// 保存的贴图
	static std::map<std::string, Animation> m_Animations;				// 保存的动画
	static std::map<std::string, CubeMap*> m_CubeMaps;					// 保存的立方体贴图
	static std::map<std::string, ModelResource*> m_ModelResources;		// 保存的模型文件资源中信息
public:
	// 加载着色器
	Shader * LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFIle, const GLchar* gShaderFile, std::string name);
	// 加载贴图
	Texture* LoadTexture(const GLchar* picFile, const GLchar* type, std::string name);
	// 加载文件夹下的所有贴图，作为动画资源
	Animation LoadAnimation(const GLchar* folderPath, std::string name);
	// 加载给定路径的六个面的贴图作为立方体贴图
	CubeMap* LoadCubeMap(std::vector<std::string> faces, std::string name);
	// 加载给定路径下，将给定路径下六个面的贴图所有立方体贴图
	CubeMap* LoadCubeMap(const GLchar* folderPath, std::string name);
	// 加载模型
	ModelResource* LoadModel(const GLchar* modelFile, std::string name);

	Shader* GetShader(std::string name);											// 根据name获取着色器
	Texture* GetTexture(std::string name);											// 根据name获取纹理贴图
	Animation GetAnimation(std::string name);										// 根据name获取动画资源
	CubeMap* GetCubeMap(std::string name);											// 根据name获取立方体贴图
	ModelResource* GetModelResource(std::string name);								// 根据name获取模型资源
private:
	Shader * LoadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile);
	Texture* LoadTextureFromFile(const GLchar* picFile, const GLchar* type);
	ModelResource* LoadModelResourceFromFile(const GLchar* modelFIle);
};



#endif // !_RESOURCES_SYSTEM_H_


