#include "LightSystem.h"

#include<string.h>


LightSystem* LightSystem::m_Instance = nullptr;
std::vector<BaseLight*> LightSystem::m_Lights;

LightSystem::LightSystem()
{
}

LightSystem::~LightSystem()
{
}

LightSystem * LightSystem::Create()
{
	if (m_Instance == nullptr) {
		m_Instance = new(std::nothrow)LightSystem();
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

bool LightSystem::Init()
{
	if (!Ref::Init()) {
		return false;
	}
	// @TODO���������ʼ��
	ClearLight();

	return true;
}

void LightSystem::AddLight(BaseLight * light)
{
	if (std::find(m_Lights.begin(), m_Lights.end(), light) == m_Lights.end()) {
		m_Lights.push_back(light);
	}
}

void LightSystem::RemoveLight(BaseLight * light)
{
	std::vector<BaseLight*>::iterator it = std::find(m_Lights.begin(), m_Lights.end(), light);
	if (it != m_Lights.end()) {
		m_Lights.erase(it);
	}
}

void LightSystem::ClearLight()
{
	m_Lights.clear();
}

void LightSystem::LightBake(Shader * shader)
{
	std::vector<BaseLight*> temp = m_Lights;

	int number_DirectionLight = 0;		// ��ǰ���������
	int number_PointLight = 0;			// ��ǰ���Դ����
	int number_SpotLight = 0;			// ��ǰ�۹������
	for (BaseLight* light : temp) {
		if (light->GetParent() != nullptr && light->IsValiable()) {		// ����ƹ⸺����ĳ���ڵ���ʱ�Ž��еƹ�ļ���
			char uniformPath[128];
			switch (light->GetLightType()) {			// ����ǡ����uniform·��
			case LightType::DIRECTION_LIGHT:
				sprintf_s(uniformPath, "directionLights[%d]", number_DirectionLight);
				number_DirectionLight++;
				break;
			case LightType::POINT_LIGHT:
				sprintf_s(uniformPath, "pointLights[%d]", number_PointLight);
				number_PointLight++;
				break;
			case LightType::SPOT_LIGHT:
				sprintf_s(uniformPath, "spotLights[%d]", number_SpotLight);
				number_SpotLight++;
				break;
			default:
				break;
			}
			light->LoadLight(shader, uniformPath);		// ֱ�ӵ��ù�Դ��LoadLight����
		}

	}
	// ����ɫ������һ���ж��ٸ�����⡢���Դ���۹��
	shader->SetInteger("directionLightNum", number_DirectionLight);
	shader->SetInteger("pointLightNum", number_PointLight);
	shader->SetInteger("spotLightNum", number_SpotLight);
}

std::vector<vec3> LightSystem::GetLightsPosition()
{
	std::vector<vec3> positions;
	for (BaseLight* light : m_Lights) {
		if (light->GetLightType() == LightType::DIRECTION_LIGHT)	continue;
		positions.push_back(light->GetLightPosition());
	}
	return positions;
}
