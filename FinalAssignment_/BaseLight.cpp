#include "BaseLight.h"

#include"CubeRenderer.h"

bool BaseLight::Init()
{
	if (!Node::Init()) {
		return false;
	}
	m_Valiable = true;
	m_Type = LightType::DIRECTION_LIGHT;
	
	// Ĭ�Ϲ���ǿ��ϵ��
	m_Ambient = DEFAULT_AMBIENT;
	m_Diffuse = DEFAULT_DIFFUSE;
	m_Specular = DEFAULT_SPECULAR;

	// ����һЩ���α任��ʹ��Light�������������һ����
	this->SetScale(vec3(0.2f));

	return true;
}

bool BaseLight::Render()
{
	if (!Node::Render()) {
		return false;
	}

	// @TODO��������������й�Դ�Ļ���
	// @TODO��ʵ��SphereRenderer֮��
	CubeRenderer::GetInstance()->Render(this->GetGlobalMatrix(), this->m_Ambient);

	return true;
}

void BaseLight::LoadLight(Shader * shader, std::string uniformPath)
{
	// ���һЩ���е�����
	shader->SetVector3f((uniformPath + ".ambient").c_str(), this->m_Ambient);
	shader->SetVector3f((uniformPath + ".diffuse").c_str(), this->m_Diffuse);
	shader->SetVector3f((uniformPath + ".specular").c_str(), this->m_Specular);
}
