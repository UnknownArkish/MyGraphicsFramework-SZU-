#include "ModelMesh.h"

#include"CameraSystem.h"
#include"ResourcesSystem.h"
#include"LightSystem.h"

ModelMesh::ModelMesh()
{
}

bool ModelMesh::Render()
{
	if (!Node::Render()) {
		return false;
	}

	// @TODO：向着色器中传递信息，进行绘制
	if (m_Shader) {
		m_Shader->Use();

		// 模型、试图、投影矩阵
		mat4 modelMatrix = this->GetRenderMatrix();
		m_Shader->SetMatrix4("modelMatrix", modelMatrix);
		MyCamera* camera = CameraSystem::GetInstance()->GetMainCamera();
		if (camera) {
			// 设置摄像机位置
			vec3 viewPos = camera->GetPosition();
			m_Shader->SetVector3f("viewPos", viewPos);
			// 设置视图矩阵
			mat4 viewMatrix = camera->GetViewMatrix();
			m_Shader->SetMatrix4("viewMatrix", viewMatrix);
			// 设置投影矩阵
			mat4 projMatrix = camera->GetProjMatrix();
			m_Shader->SetMatrix4("projMatrix", projMatrix);
		}

		// 设置颜色为黑色
		vec3 black = vec3(0.0f);
		m_Shader->SetVector3f("color", black);

		// 贴图部分
		if (m_Textures.size() > 0) {
			m_Shader->SetInteger("isHaveTexture", GL_TRUE);

			unsigned int ambientNr = 0;
			unsigned int diffuseNr = 0;
			unsigned int specularNr = 0;
			unsigned int normalNr = 0;
			unsigned int heightNr = 0;
			for (unsigned int i = 0; i < m_Textures.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				int number;
				std::string name = m_Textures[i]->Type;
				if (name == "texture_ambient") {
					number = ambientNr++;
				}
				else if (name == "texture_diffuse") {
					number = diffuseNr++;
				}
				else if (name == "texture_specular") {
					number = specularNr++;
				}
				else if (name == "texture_normal") {
					number = normalNr++;					// transfer unsigned int to stream
				}
				else if (name == "texture_height") {
					number = heightNr++;					// transfer unsigned int to stream
				}
				char uniformPath[128];
				sprintf_s(uniformPath, "material.%s[%d]", name.c_str(), number);
				m_Shader->SetInteger(uniformPath, i);
				m_Textures[i]->Bind();
			}
			m_Shader->SetInteger("ambientNr", ambientNr);
			m_Shader->SetInteger("diffuseNr", diffuseNr);
			m_Shader->SetInteger("specularNr", specularNr);
		}
		else {
			m_Shader->SetInteger("isHaveTexture", GL_FALSE);
			m_Shader->SetVector3f("material.ambient", m_Material.Ambient);
			m_Shader->SetVector3f("material.diffuse", m_Material.Diffuse);
			m_Shader->SetVector3f("material.specular", m_Material.Specular);
		}
		m_Shader->SetFloat("material.shiness", m_Material.Shiness);

		// 向光照系统申请光源信息
		LightSystem::GetInstance()->LightBake(this->m_Shader);

		m_Shader->SetInteger("isShadow", GL_FALSE);
		// 绘制网格
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

		// 生成阴影信息
		this->GenerateShadow();
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	return true;
}

void ModelMesh::GenerateShadow()
{
	// 使用阴影
	m_Shader->SetInteger("isShadow", GL_TRUE);
	// @TODO：设置阴影基本颜色
	vec3 shadowColor = vec3(0.1f);
	m_Shader->SetVector3f("color", shadowColor);

	// 向光照系统获取光源位置信息
	std::vector<vec3> lightsPosition = LightSystem::GetInstance()->GetLightsPosition();
	// 为每个光源位置设置一个新的模型矩阵
	// 并绘制阴影
	for (vec3 lightPosition : lightsPosition) {
		lightPosition.y += 0.5f;
		if (lightPosition.y <= 1.0f) {
			continue;
		}

		mat4 m;
		m[3][1] = -1.0f / lightPosition.y;
		m[3][3] = 0.0f;
		mat4 modelMatrix = Translate(vec3(0.0f,-0.01f,0.0f)) * Translate(lightPosition) * m * Translate(-lightPosition) *  this->GetGlobalMatrix();
		modelMatrix[1][3] = 0.0f;
		m_Shader->SetMatrix4("modelMatrix", modelMatrix);

		// 绘制网格
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	}
}

bool ModelMesh::Init(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures)
{
	if (!Node::Init()) {
		return false;
	}

	this->m_Vertices = vertices;
	this->m_Indices = indices;
	this->m_Textures = textures;

	m_Material = MaterialPreSet::Green_rubber;

	// 初始化网格
	this->InitMesh();

	// @TODO：初始化着色器
	m_Shader = ResourcesSystem::GetInstance()->GetShader("ModelShader");

	return true;
}

ModelMesh::~ModelMesh()
{
}

ModelMesh * ModelMesh::Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures)
{
	ModelMesh* pRet = new (std::nothrow)ModelMesh();
	if (pRet && pRet->Init(vertices, indices, textures)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void ModelMesh::SetMaterial(Material material)
{
	this->m_Material = material;
}

void ModelMesh::InitMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

	// 顶点位置，通过计算偏移值得到下一个顶点位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// 顶点法线
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// 顶点纹理坐标
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);

}
