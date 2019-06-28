#include "CubeRenderer.h"
#include"stdafx.h"

#include"CameraSystem.h"
#include"LightSystem.h"
#include"ResourcesSystem.h"

CubeRenderer* CubeRenderer::m_Instance = nullptr;
Shader* CubeRenderer::m_Shader = nullptr;

CubeRenderer * CubeRenderer::Create()
{
	if (m_Instance == nullptr) {
		m_Instance = new (std::nothrow)CubeRenderer();
		if (m_Instance && m_Instance->Init()) {
			return m_Instance;
		}
		else {
			delete m_Instance;
			m_Instance = nullptr;
			return nullptr;
		}
	}
	return m_Instance;
}

bool CubeRenderer::Init()
{
	if (!Renderer::Init()) {
		return false;
	}
	return true;
}

CubeRenderer::CubeRenderer()
{
}


CubeRenderer::~CubeRenderer()
{
}

void CubeRenderer::LoadModel()
{
	//m_Mesh = new OFFMesh();
	//Tools::GetInstance()->ReadOFF("Resources/Model/OFF/cube.off", m_Mesh);
}

void CubeRenderer::InitData()
{
	float verticesPos[] = {
		// positions
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};
	float verticesNormal[] = {
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,

		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,

		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f
	};

	int len = (sizeof(verticesPos) / sizeof(verticesPos[0])) / 3;
	for (int i = 0; i < len; i++) {
		vec3 position = vec3(verticesPos[3 * i + 0], verticesPos[3 * i + 1], verticesPos[3 * i + 2]);
		vec3 normal = vec3(verticesNormal[3 * i + 0], verticesNormal[3 * i + 1], verticesNormal[3 * i + 2]);

		m_CubeVertexPos.push_back(position);
		m_CubeNormals.push_back(normal);
	}

	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// 用于天空盒的顶点
	//float skyboxVertices[] = {
	//	// positions          
	//	-1.0f,  1.0f, -1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f,  1.0f, -1.0f,
	//	-1.0f,  1.0f, -1.0f,

	//	-1.0f, -1.0f,  1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f,  1.0f, -1.0f,
	//	-1.0f,  1.0f, -1.0f,
	//	-1.0f,  1.0f,  1.0f,
	//	-1.0f, -1.0f,  1.0f,

	//	1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f,  1.0f,
	//	1.0f,  1.0f,  1.0f,
	//	1.0f,  1.0f,  1.0f,
	//	1.0f,  1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,

	//	-1.0f, -1.0f,  1.0f,
	//	-1.0f,  1.0f,  1.0f,
	//	1.0f,  1.0f,  1.0f,
	//	1.0f,  1.0f,  1.0f,
	//	1.0f, -1.0f,  1.0f,
	//	-1.0f, -1.0f,  1.0f,

	//	-1.0f,  1.0f, -1.0f,
	//	1.0f,  1.0f, -1.0f,
	//	1.0f,  1.0f,  1.0f,
	//	1.0f,  1.0f,  1.0f,
	//	-1.0f,  1.0f,  1.0f,
	//	-1.0f,  1.0f, -1.0f,

	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f,  1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f,  1.0f,
	//	1.0f, -1.0f,  1.0f
	//};
	//len = (sizeof(skyboxVertices) / sizeof(skyboxVertices[0])) / 3;
	//for (int i = 0; i < len; i++) {
	//	vec3 position = vec3(skyboxVertices[i * 3 + 0], skyboxVertices[i * 3 + 1], skyboxVertices[i * 3 + 2]);
	//	m_SkyboxVertices.push_back(position);
	//}
	
	//for (int i = 0; i < m_Mesh->m_FaceNum; i++) {
	//	vec3i face = m_Mesh->m_faces[i];
	//	m_VertexPos.push_back(m_Mesh->m_vertices[face.a]);
	//	m_VertexPos.push_back(m_Mesh->m_vertices[face.b]);
	//	m_VertexPos.push_back(m_Mesh->m_vertices[face.c]);
	//}
}

void CubeRenderer::InitShader()
{
	m_Shader = ResourcesSystem::GetInstance()->GetShader("CubeShader");
}

void CubeRenderer::BindObject()
{
	// @TODO：使用着色器，并解释顶点属性
	m_Shader->Use();

	GLuint vbo[2];

	// @TODO：创建vao、vbo
	glGenVertexArrays(1, &m_CubeVao);
	glGenBuffers(2, vbo);

	// @TODO：绑定vao、绑定vbo
	glBindVertexArray(m_CubeVao);
	// 绑定数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, m_CubeVertexPos.size() * sizeof(vec3), m_CubeVertexPos.data(), GL_STATIC_DRAW);
	GLuint vPositionPos = m_Shader->GetAttribLocation("vPosition");
	glEnableVertexAttribArray(vPositionPos);
	glVertexAttribPointer(vPositionPos, 3, GL_FLOAT, 0, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, m_CubeNormals.size() * sizeof(vec3), m_CubeNormals.data(), GL_STATIC_DRAW);
	GLuint vNormalPos = m_Shader->GetAttribLocation("vNormal");
	glEnableVertexAttribArray(vNormalPos);
	glVertexAttribPointer(vNormalPos, 3, GL_FLOAT, 0, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void CubeRenderer::Render(Cube * cube)
{
	// @TODO：更新Shader的Uniform数据
	m_Shader->Use();

	// 设置模型矩阵
	mat4 modelMatrix = cube->GetRenderMatrix();
	m_Shader->SetMatrix4("modelMatrix", modelMatrix);

	// 设置颜色为黑色
	vec3 black = vec3(0.0f);
	m_Shader->SetVector3f("color", black);

	// 若方块有立方体贴图的信息
	CubeMap* map = cube->GetCubeMap();
	if (map != nullptr) {
		m_Shader->SetInteger("isHaveCubeMap", GL_TRUE);

		glActiveTexture(GL_TEXTURE0);					// 激活纹理单元
		map->Bind();									// 绑定
		m_Shader->SetInteger("material.cubeMap", 0);	// 设置着色器中的纹理单元
	}
	else {
		m_Shader->SetInteger("isHaveCubeMap", GL_FALSE);
	}
	// 使用普通的材质球
	Material material = cube->GetMaterial();
	m_Shader->SetVector3f("material.ambient", material.Ambient);
	m_Shader->SetVector3f("material.diffuse", material.Diffuse);
	m_Shader->SetVector3f("material.specular", material.Specular);
	m_Shader->SetFloat("material.shiness", material.Shiness);

	// 判断摄像机是否存在
	MyCamera* camera = CameraSystem::GetInstance()->GetMainCamera();
	if (camera) {
		// 设置摄像机位置
		vec3 viewPos = camera->GetGlobalPosition();
		m_Shader->SetVector3f("viewPos", viewPos);
		// 设置视图矩阵
		mat4 viewMatrix = camera->GetViewMatrix();
		m_Shader->SetMatrix4("viewMatrix", viewMatrix);
		// 设置投影矩阵
		mat4 projMatrix = camera->GetProjMatrix();
		m_Shader->SetMatrix4("projMatrix", projMatrix);
	}
	// @TODO：向光照系统申请光照请求
	LightSystem::GetInstance()->LightBake(this->m_Shader);

	// 绘制本体，不使用阴影的flag
	m_Shader->SetInteger("isShadow", GL_FALSE);
	// @TODO：绑定vao进行绘制
	glBindVertexArray(m_CubeVao);
	glDrawArrays(GL_TRIANGLES, 0, m_CubeVertexPos.size());

	// @TODO：在这里绘制Cube的阴影
	this->GenerateShadow(cube);
}

void CubeRenderer::Render(vec3 position, vec3 rotation, vec3 scale, vec3 color, bool toLighted)
{
	m_Shader->Use();

	mat4 modelMatrix = Translate(position) * RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z) * Scale(scale);
	this->Render(modelMatrix, color, toLighted);
}

void CubeRenderer::Render(mat4 modelMatrix, vec3 color, bool toLighted)
{
	// 使用着色器
	m_Shader->Use();
	// 设置模型矩阵
	m_Shader->SetMatrix4("modelMatrix", modelMatrix);
	// 设置基本颜色
	m_Shader->SetVector3f("color", color);
	// 判断摄像机是否存在
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
	// @TODO：向光照系统申请光照请求
	if (toLighted) {
		LightSystem::GetInstance()->LightBake(this->m_Shader);
	}

	// @TODO：绑定vao进行绘制
	glBindVertexArray(m_CubeVao);
	glDrawArrays(GL_TRIANGLES, 0, m_CubeVertexPos.size());
}

void CubeRenderer::GenerateShadow(Cube* cube)
{
	// 使用阴影
	m_Shader->SetInteger("isShadow", GL_TRUE);
	// 设置阴影的基本颜色
	vec3 shadowColor = vec3(0.1f);
	m_Shader->SetVector3f("color", shadowColor);

	// 向光照系统获取光源位置信息
	std::vector<vec3> lightsPosition = LightSystem::GetInstance()->GetLightsPosition();
	// 为每个光源位置设置一个新的模型矩阵
	// 并绘制阴影
	for (vec3 lightPosition : lightsPosition) {
		lightPosition.y += 0.5f;
		if (lightPosition.y <= 1.0f) {		// 如果光源太低不进行绘制，防止影子太长
			continue;
		}
		mat4 m;
		m[3][1] = -1.0f / lightPosition.y;
		m[3][3] = 0.0f;
		mat4 modelMatrix = Translate(vec3(0.0f, -0.01f, 0.0f)) * 
			Translate(lightPosition) * m * Translate(-lightPosition) * cube->GetGlobalMatrix();
		modelMatrix[1][3] = 0.0f;
		m_Shader->SetMatrix4("modelMatrix", modelMatrix);
		// 进行阴影的绘制
		glBindVertexArray(m_CubeVao);
		glDrawArrays(GL_TRIANGLES, 0, m_CubeVertexPos.size());
	}
}
