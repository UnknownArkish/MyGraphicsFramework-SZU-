/*
*	ģ����
*	��������ʱ��ָ��һ��ģ���ļ������󽫻�Ӵ����ж�ȡģ���ļ�
*	���󶨶�Ӧ��OpenGL����Model����Ϊ���ڵ�
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
	// ���͵�ǰ�ڵ㣬�����ӽڵ��������ǰ�ڵ���
	ModelNode * ProcessNode(aiNode* node, ModelResource* modelResource);
	ModelMesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture*> LoadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif // !_MODEL_H_


