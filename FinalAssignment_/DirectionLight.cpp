#include "DirectionLight.h"



DirectionLight::DirectionLight()
{
}

bool DirectionLight::Init()
{
	if (!BaseLight::Init()) {
		return false;
	}

	m_Type = LightType::DIRECTION_LIGHT;

	this->SetVisiable(false);							// 方向光默认不可见

	// 默认光线方向
	m_DefaultDirection = DEFAULT_DIRECTION;

	return true;
}


DirectionLight::~DirectionLight()
{
}

DirectionLight * DirectionLight::Create()
{
	DirectionLight* pRet = new (std::nothrow)DirectionLight();
	if (pRet&&pRet->Init()) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}


void DirectionLight::LoadLight(Shader * shader, std::string uniformPath)
{
	BaseLight::LoadLight(shader, uniformPath);
	// @TODO：向uniformPath中填充光照参数
	// 计算旋转以后的方向信息
	vec4 direction_vec4 = GetGlobalMatrix() * vec4(m_DefaultDirection,0.0f);
	vec3 direction = vec3(direction_vec4.x, direction_vec4.y, direction_vec4.z);

	shader->SetVector3f((uniformPath + ".direction").c_str(), direction);
}

vec3 DirectionLight::GetLightPosition()
{
	vec4 direction_vec4 = GetGlobalMatrix() * vec4(m_DefaultDirection, 0.0f);
	vec3 direction = vec3(direction_vec4.x, direction_vec4.y, direction_vec4.z);
	return -direction;
}
