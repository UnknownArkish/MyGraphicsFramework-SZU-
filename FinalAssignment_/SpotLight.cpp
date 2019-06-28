#include "SpotLight.h"



SpotLight::SpotLight()
{
}

bool SpotLight::Init()
{
	if (!BaseLight::Init()) {
		return false;
	}
	m_Type = LightType::SPOT_LIGHT;

	this->SetVisiable(false);
	// 默认方向
	m_DefaultDirection = DEFAULT_DIRECTION;
	// 默认模糊系数
	m_CutOff = DEFAULT_CUT_OFF;
	m_OuterCutOff = DEFAULT_OUTER_CUT_OFF;
	// 默认衰减因子
	m_Factor = AttrnuationFactorPreset::FACTOR_20;

	return true;
}


SpotLight::~SpotLight()
{
}

SpotLight * SpotLight::Create()
{
	SpotLight* pRet = new(std::nothrow)SpotLight();
	if (pRet&& pRet->Init()) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return pRet;
}

void SpotLight::LoadLight(Shader * shader, std::string uniformPath)
{
	BaseLight::LoadLight(shader, uniformPath);

	// @TODO：向unifromPath填充自己的光源数值
	
	// 计算全局的direction信息
	vec3 globalRotation = this->GetGlobalRotation();
	vec4 direction_vector = 
		RotateX(globalRotation.x) * RotateY(globalRotation.y) * RotateZ(globalRotation.z) * vec4(m_DefaultDirection, 0.0f);
	vec3 direction = vec3(direction_vector.x, direction_vector.y, direction_vector.z);
	// 计算全局的position信息
	//vec4 position_vec4 = this->GetGlobalMatrix() * vec4(this->GetPosition(), 1.0f);
	vec3 position = this->GetGlobalPosition();

	// 位置和方向信息
	shader->SetVector3f((uniformPath + ".position").c_str(), position);
	shader->SetVector3f((uniformPath + ".direction").c_str(), direction);

	// 模糊系数
	shader->SetFloat((uniformPath + ".cutOff").c_str(), cos(Degree2Radians(m_CutOff)));
	shader->SetFloat((uniformPath + ".outerCutOff").c_str(), cos(Degree2Radians(m_OuterCutOff)));

	// 衰减因子
	shader->SetFloat((uniformPath + ".constant").c_str(), m_Factor.Constant);
	shader->SetFloat((uniformPath + ".linear").c_str(), m_Factor.Linear);
	shader->SetFloat((uniformPath + ".quadratic").c_str(), m_Factor.Quadratic);
}

vec3 SpotLight::GetLightPosition()
{
	return this->GetGlobalPosition();
}
