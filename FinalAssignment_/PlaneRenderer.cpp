#include "PlaneRenderer.h"

#include"ResourcesSystem.h"
#include"CameraSystem.h"
#include"LightSystem.h"

PlaneRenderer* PlaneRenderer::m_Instace = nullptr;
Shader* PlaneRenderer::m_Shader = nullptr;

PlaneRenderer * PlaneRenderer::Create()
{
	if (m_Instace == nullptr) {
		m_Instace = new(std::nothrow)PlaneRenderer();
		if (m_Instace && m_Instace->Init()) {
			return m_Instace;
		}
		delete m_Instace;
		m_Instace = nullptr;
		return nullptr;
	}
	return m_Instace;;
}

bool PlaneRenderer::Init()
{
	if (!Renderer::Init()) {
		return false;
	}

	// 在这里进行初始化

	return true;
}

PlaneRenderer::PlaneRenderer()
{
}


PlaneRenderer::~PlaneRenderer()
{
}

void PlaneRenderer::LoadModel()
{
}

void PlaneRenderer::InitData()
{
}

void PlaneRenderer::InitShader()
{
	m_Shader = ResourcesSystem::GetInstance()->GetShader("PlaneShader");
}

void PlaneRenderer::BindObject()
{
	float vertices[] = {
		// positions          // colors           // texture coords   // Normal 
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,          0.0f, 0.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,          0.0f, 0.0f, 1.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,         0.0f, 0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,         0.0f, 0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	unsigned int VBO, EBO;
	glGenVertexArrays(1, &m_PlaneVao);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(m_PlaneVao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void PlaneRenderer::Render(Plane * plane, bool toLighted)
{
	if (plane == nullptr)	return;

	// @TODO：设置shader的矩阵等，以指定贴图绘制Plane
	if (m_Shader) {
		m_Shader->Use();

		vec3 black = vec3(0.0f, 0.0f, 0.0f);
		m_Shader->SetVector3f("color", black);

		Texture* texture = plane->GetTexture();
		// 设置贴图信息
		if (texture) {
			// 设置为使用贴图
			m_Shader->SetInteger("useTexture", GL_TRUE);
			// 绑定相应的OpenGL贴图对象
			glActiveTexture(GL_TEXTURE0);
			texture->Bind();
			m_Shader->SetInteger("material.texture", 0);
		}
		else {
			m_Shader->SetInteger("useTexture", GL_FALSE);
		}
		// @TODO：传递材质信息
		Material material = plane->GetMaterial();
		m_Shader->SetVector3f("material.ambient", material.Ambient);
		m_Shader->SetVector3f("material.diffuse", material.Diffuse);
		m_Shader->SetVector3f("material.specular", material.Specular);
		m_Shader->SetFloat("material.shiness", material.Shiness);

		// @TODO：设置矩阵等信息
		mat4 modelMatrix = plane->GetGlobalMatrix();
		m_Shader->SetMatrix4("modelMatrix", modelMatrix);
		MyCamera* camera = CameraSystem::GetInstance()->GetMainCamera();
		if (camera) {
			// 设置摄像机位置
			vec3 viewPos = camera->GetGlobalPosition();
			m_Shader->SetVector3f("viewPos", viewPos);

			mat4 viewMatrix = camera->GetViewMatrix();
			m_Shader->SetMatrix4("viewMatrix", viewMatrix);
			mat4 projMatrix = camera->GetProjMatrix();
			m_Shader->SetMatrix4("projMatrix", projMatrix);
		}


		if (toLighted) {
			LightSystem::GetInstance()->LightBake(this->m_Shader);
		}
		else {
			// 否则设置所有灯光的数量为0
			m_Shader->SetInteger("directionLightNum", 0);
			m_Shader->SetInteger("pointLightNum", 0);
			m_Shader->SetInteger("spotLightNum", 0);
			vec3 white = vec3(1.0f, 1.0f, 1.0f);
			m_Shader->SetVector3f("color", white);
		}


		// 设置是否为动画机
		if (plane->IsAnimator()) {
			m_Shader->SetInteger("isAnimator", GL_TRUE);
		}
		else {
			m_Shader->SetInteger("isAnimator", GL_FALSE);
		}


		// 最后进行绘制
		glBindVertexArray(m_PlaneVao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void PlaneRenderer::Render(mat4 modelMatrix, vec3 color, bool toLighted)
{
	if (m_Shader) {
		m_Shader->Use();

		m_Shader->SetInteger("useTexture", GL_FALSE);

		// 设置模型、视图、投影矩阵
		m_Shader->SetMatrix4("modelMatrix", modelMatrix);
		MyCamera* camera = CameraSystem::GetInstance()->GetMainCamera();
		if (camera) {
			// 设置摄像机位置
			vec3 viewPos = camera->GetPosition();
			m_Shader->SetVector3f("viewPos", viewPos);
			mat4 viewMatrix = camera->GetViewMatrix();
			m_Shader->SetMatrix4("viewMatrix", viewMatrix);
			mat4 projMatrix = camera->GetProjMatrix();
			m_Shader->SetMatrix4("projMatrix", projMatrix);
		}

		if (toLighted) {
			LightSystem::GetInstance()->LightBake(this->m_Shader);
		}

		glBindVertexArray(m_PlaneVao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void PlaneRenderer::Render(vec3 position, vec3 rotation, vec3 scale, vec3 color, bool toLighted)
{
	mat4 modelMatrix = Translate(position) * RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z) * Scale(scale);
	this->Render(modelMatrix, color, toLighted);
}
