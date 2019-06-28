/*
*	��Դ������
*	����洢��ɫ������ͼ�Լ�ģ����Ϣ
*/


#ifndef _RESOURCES_SYSTEM_H_
#define _RESOURCES_SYSTEM_H_
#pragma once

#include<assimp\Importer.hpp>
#include<assimp\scene.h>
#include<assimp\postprocess.h>
#include<stb_image.h>

#include<Shader_GLUT.h>			// ��ɫ��
#include<Texture_GLUT.h>		// ��ͼ
#include"CubeMap.h"
#include"ModelResource.h"
#include<vector>
#include<map>
#include"Ref.h"
#include"Animation.h"

//typedef aiScene ModelResource;			// ��aiScene����Ϊ���ص�ģ���ļ���Դ
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
	static std::map<std::string, Shader*> m_Shaders;					// �������ɫ��
	static std::map<std::string, Texture*> m_Textures;					// �������ͼ
	static std::map<std::string, Animation> m_Animations;				// ����Ķ���
	static std::map<std::string, CubeMap*> m_CubeMaps;					// �������������ͼ
	static std::map<std::string, ModelResource*> m_ModelResources;		// �����ģ���ļ���Դ����Ϣ
public:
	// ������ɫ��
	Shader * LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFIle, const GLchar* gShaderFile, std::string name);
	// ������ͼ
	Texture* LoadTexture(const GLchar* picFile, const GLchar* type, std::string name);
	// �����ļ����µ�������ͼ����Ϊ������Դ
	Animation LoadAnimation(const GLchar* folderPath, std::string name);
	// ���ظ���·�������������ͼ��Ϊ��������ͼ
	CubeMap* LoadCubeMap(std::vector<std::string> faces, std::string name);
	// ���ظ���·���£�������·�������������ͼ������������ͼ
	CubeMap* LoadCubeMap(const GLchar* folderPath, std::string name);
	// ����ģ��
	ModelResource* LoadModel(const GLchar* modelFile, std::string name);

	Shader* GetShader(std::string name);											// ����name��ȡ��ɫ��
	Texture* GetTexture(std::string name);											// ����name��ȡ������ͼ
	Animation GetAnimation(std::string name);										// ����name��ȡ������Դ
	CubeMap* GetCubeMap(std::string name);											// ����name��ȡ��������ͼ
	ModelResource* GetModelResource(std::string name);								// ����name��ȡģ����Դ
private:
	Shader * LoadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile);
	Texture* LoadTextureFromFile(const GLchar* picFile, const GLchar* type);
	ModelResource* LoadModelResourceFromFile(const GLchar* modelFIle);
};



#endif // !_RESOURCES_SYSTEM_H_


