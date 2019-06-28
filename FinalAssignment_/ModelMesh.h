
/*
*	模型网格类
*/

#ifndef _MODEL_MESH_H_
#define _MODEL_MESH_H_
#pragma once

#include"Node.h"
#include<Shader_GLUT.h>
#include<Texture_GLUT.h>
#include"Material.h"

// 顶点信息结构体
struct Vertex {
	vec3 Position;			// 位置信息
	vec3 Normal;			// 法线信息
	vec2 TexCoords;			// 纹理坐标信息
	vec3 Tangent;			// 切线
	vec3 Bitangent;			// 双切线
};

class ModelMesh :public Node
{
private:
	Shader * m_Shader = nullptr;				// 绘制Model的着色器

	GLuint m_VAO, m_VBO, m_EBO;					// 用于绑定OpenGL对象
	std::vector<Vertex> m_Vertices;				// 顶点属性信息
	std::vector<unsigned int> m_Indices;		// 用以绘制的索引
	std::vector<Texture*> m_Textures;			// 贴图

	Material m_Material;
protected:
	ModelMesh();
	virtual bool Render	()override;
	void GenerateShadow();						// 产生阴影
	virtual bool Init(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);
public:
	~ModelMesh();

	static ModelMesh* Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);

	void SetMaterial(Material material);
private:
	void InitMesh();							// 初始化网格
};



#endif // !_MODEL_MESH_H_

