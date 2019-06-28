#include "BaseLight.h"

#include"CubeRenderer.h"

bool BaseLight::Init()
{
	if (!Node::Init()) {
		return false;
	}
	m_Valiable = true;
	m_Type = LightType::DIRECTION_LIGHT;
	
	// 默认光照强度系数
	m_Ambient = DEFAULT_AMBIENT;
	m_Diffuse = DEFAULT_DIFFUSE;
	m_Specular = DEFAULT_SPECULAR;

	// 设置一些几何变换，使得Light不会和正常物体一样大
	this->SetScale(vec3(0.2f));

	return true;
}

bool BaseLight::Render()
{
	if (!Node::Render()) {
		return false;
	}

	// @TODO：将来在这里进行光源的绘制
	// @TODO：实现SphereRenderer之后
	CubeRenderer::GetInstance()->Render(this->GetGlobalMatrix(), this->m_Ambient);

	return true;
}

void BaseLight::LoadLight(Shader * shader, std::string uniformPath)
{
	// 填充一些共有的属性
	shader->SetVector3f((uniformPath + ".ambient").c_str(), this->m_Ambient);
	shader->SetVector3f((uniformPath + ".diffuse").c_str(), this->m_Diffuse);
	shader->SetVector3f((uniformPath + ".specular").c_str(), this->m_Specular);
}
