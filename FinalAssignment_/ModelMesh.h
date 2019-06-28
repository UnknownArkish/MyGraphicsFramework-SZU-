
/*
*	ģ��������
*/

#ifndef _MODEL_MESH_H_
#define _MODEL_MESH_H_
#pragma once

#include"Node.h"
#include<Shader_GLUT.h>
#include<Texture_GLUT.h>
#include"Material.h"

// ������Ϣ�ṹ��
struct Vertex {
	vec3 Position;			// λ����Ϣ
	vec3 Normal;			// ������Ϣ
	vec2 TexCoords;			// ����������Ϣ
	vec3 Tangent;			// ����
	vec3 Bitangent;			// ˫����
};

class ModelMesh :public Node
{
private:
	Shader * m_Shader = nullptr;				// ����Model����ɫ��

	GLuint m_VAO, m_VBO, m_EBO;					// ���ڰ�OpenGL����
	std::vector<Vertex> m_Vertices;				// ����������Ϣ
	std::vector<unsigned int> m_Indices;		// ���Ի��Ƶ�����
	std::vector<Texture*> m_Textures;			// ��ͼ

	Material m_Material;
protected:
	ModelMesh();
	virtual bool Render	()override;
	void GenerateShadow();						// ������Ӱ
	virtual bool Init(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);
public:
	~ModelMesh();

	static ModelMesh* Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);

	void SetMaterial(Material material);
private:
	void InitMesh();							// ��ʼ������
};



#endif // !_MODEL_MESH_H_

