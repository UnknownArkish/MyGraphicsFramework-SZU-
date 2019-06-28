#include "PointLight.h"

PointLight::PointLight()
{
}

bool PointLight::Init()
{
	if (!BaseLight::Init()) {
		return false;
	}

	m_Type = LightType::POINT_LIGHT;

	// @TODO��ʹ��Ĭ��˥�����ӣ�����Ϊ20
	m_Factor = AttrnuationFactorPreset::FACTOR_20;

	return true;
}


PointLight::~PointLight()
{
}

PointLight * PointLight::Create()
{
	PointLight* pRet = new(std::nothrow)PointLight();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void PointLight::LoadLight(Shader * shader, std::string uniformPath)
{
	BaseLight::LoadLight(shader, uniformPath);

	// @TODO����uniformPath���������
	// ����m_Position�Ǿֲ�����ϵ�µ�λ����Ϣ��������Ҫ�Ƚ���ת��Ϊ��������ϵ��
	vec4 position_vec4 = this->GetGlobalPosition();
	vec3 position = vec3(position_vec4.x, position_vec4.y, position_vec4.z);

	// λ�úͷ�����Ϣ
	shader->SetVector3f((uniformPath + ".position").c_str(), position);
	// ˥������
	shader->SetFloat((uniformPath + ".constant").c_str(), m_Factor.Constant);
	shader->SetFloat((uniformPath + ".linear").c_str(), m_Factor.Linear);
	shader->SetFloat((uniformPath + ".quadratic").c_str(), m_Factor.Quadratic);
}

vec3 PointLight::GetLightPosition()
{
	return this->GetGlobalPosition();
}
