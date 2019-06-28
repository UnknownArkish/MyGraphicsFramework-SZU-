#include "Skybox.h"

#include"ResourcesSystem.h"
#include"CameraSystem.h"

Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}

Skybox* Skybox::m_Instance = nullptr;

Skybox * Skybox::Create()
{
	if (m_Instance == nullptr) {
		m_Instance = new(std::nothrow)Skybox();
		if (m_Instance && m_Instance->Init()) {
			return m_Instance;
		}
		delete m_Instance;
		m_Instance = nullptr;
		return nullptr;
	}
	return m_Instance;
}


bool Skybox::Render()
{
	if (!Node::Render()) {
		return false;
	}

	// ʹ����պ���ɫ�������ݲ���
	if (m_Shader) {
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

		m_Shader->Use();
		MyCamera* camera = CameraSystem::GetInstance()->GetMainCamera();
		if (camera) {
			mat4 viewMatrix = camera->GetViewMatrix();
			m_Shader->SetMatrix4("viewMatrix", viewMatrix);
			mat4 projMatrix = camera->GetProjMatrix();
			m_Shader->SetMatrix4("projMatrix", projMatrix);
		}
		glActiveTexture(GL_TEXTURE0);
		m_CubeMap->Bind();
		m_Shader->SetInteger("skybox", 0);

		glBindVertexArray(m_Vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthFunc(GL_LESS); // set depth function back to default
	}
	
	return true;
}

bool Skybox::Init()
{
	if (!Cube::Init()) {
		return false;
	}

	// @TODO����ʼ������
	InitData();
	// @TODO����ʼ����ɫ��
	InitShader();
	// @TODO����OpenGL����
	BindObject();

	// @TODO��ʹ��Ĭ�ϵ���պ�
	m_CubeMap = ResourcesSystem::GetInstance()->GetCubeMap("DefaultSkybox");

	return true;
}

void Skybox::InitData()
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	int len = sizeof(skyboxVertices) / sizeof(skyboxVertices[0]) / 3;
	for (int i = 0; i < len; i++) {
		m_VerticesPos.push_back(vec3(skyboxVertices[i * 3 + 0], skyboxVertices[i * 3 + 1], skyboxVertices[i * 3 + 2]));
	}
}

void Skybox::InitShader()
{
	m_Shader = ResourcesSystem::GetInstance()->GetShader("SkyboxShader");		// ��ȡ��պ���ɫ��
}

void Skybox::BindObject()
{
	unsigned int vbo;

	glGenVertexArrays(1, &m_Vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(m_Vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_VerticesPos.size() * sizeof(vec3), m_VerticesPos.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	// �����
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
