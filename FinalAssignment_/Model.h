/*
*	模型类
*	对象生成时，指定一个模型文件，对象将会从磁盘中读取模型文件
*	并绑定对应的OpenGL对象，Model类作为根节点
*/

#ifndef _MODEL_H_
#define _MODEL_H_
#pragma once

#include"Node.h"
#include"ModelResource.h"
#include"ModelMesh.h"
#include"ModelNode.h"

class Model :public Node
{
private:
	ModelResource* m_ModelResource;
	Material m_Material; 
protected:
	Model();
	//virtual bool Render()override;
	virtual bool Init(ModelResource* modelResource, Material material);
	virtual bool Init(std::string modelFilePath, std::string modelName, Material material);
public:
	~Model();

	static Model* Create(ModelResource* modelResource, Material material = MaterialPreSet::Green_rubber);
	static Model* Create(std::string modelFilePath, std::string modelName, Material material = MaterialPreSet::Green_rubber);
private:
	// 解释当前节点，并将子节点添加至当前节点中
	ModelNode * ProcessNode(aiNode* node, ModelResource* modelResource);
	ModelMesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture*> LoadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif // !_MODEL_H_


