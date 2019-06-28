#include "Fire.h"

#include"LightSystem.h"
#include"Game.h"

Fire::Fire()
{
}

bool Fire::Init(Animation animation)
{
	if (!Animator2_5D::Init(animation)) {		// ��ʼ������
		return false;
	}
	// @TODO����ʼ����Դ
	m_MainLight = PointLight::Create();
	m_MainLight->SetVisiable(false);
	// ����Ĭ�ϵĻ�Ĺ���ϵ��
	m_MainLight->SetAmbient(DEFAULT_FIRE_AMBIENT);
	m_MainLight->SetDiffuse(DEFAULT_FIRE_DIFFUSE);
	m_MainLight->SetSpecular(DEFAULT_FIRE_SPECULAR);
	m_MainLight->SetAnchor(vec3(0.0f, -0.5f, 0.0f));
	// ����˥������
	m_MainLight->SetFactor(AttrnuationFactorPreset::FACTOR_32);
	// ���ù�Դע�ᵽLightSystem����
	LightSystem::GetInstance()->AddLight(m_MainLight);
	this->AddChildren(m_MainLight);

	m_AssitLigh = PointLight::Create();
	m_AssitLigh->SetVisiable(false);
	m_AssitLigh->SetAmbient(DEFAULT_FIRE_AMBIENT );
	m_AssitLigh->SetDiffuse(DEFAULT_FIRE_DIFFUSE);
	m_AssitLigh->SetSpecular(DEFAULT_FIRE_SPECULAR );
	m_AssitLigh->SetFactor(AttrnuationFactorPreset::FACTOR_13);
	LightSystem::GetInstance()->AddLight(m_AssitLigh);
	this->AddChildren(m_AssitLigh);

	m_DeltaTime = 0.0f;
	this->Start();
	return true;
}

void Fire::Update(float deltaTime)
{
	m_DeltaTime += deltaTime;
	if (m_DeltaTime >= this->GetDeltaTime()) {
		m_DeltaTime = 0.0f;

		// ����λ�ñ仯�����ֵ
		float _cos = cos(
			Degree2Radians(Game::GetInstance()->GetRunTime()* Tools::GetInstance()->_Random(-RandomFactor, RandomFactor)));
		float _sin = sin(
			Degree2Radians(Game::GetInstance()->GetRunTime()* Tools::GetInstance()->_Random(-RandomFactor, RandomFactor)));
		// ʹλ�÷����仯
		m_AssitLigh->SetPosition(vec3(_cos / XShakeFactor, _sin / YShakeFactor, _sin / ZShakeFactor));		
		// �����仯��ɫ�����ֵ
		float r = cos(Degree2Radians(Game::GetInstance()->GetRunTime())) * Tools::GetInstance()->_Random(-RShakeFactor, RShakeFactor);
		float g = sin(Degree2Radians(Game::GetInstance()->GetRunTime())) * Tools::GetInstance()->_Random(-GShakeFactor, GShakeFactor);
		float b = cos(Degree2Radians(Game::GetInstance()->GetRunTime())) * Tools::GetInstance()->_Random(-BShakeFactor, BShakeFactor);
		// ʹ��Դ��ɫ�����仯
		m_AssitLigh->SetAmbient(DEFAULT_FIRE_AMBIENT + vec3(r, g, b));
		m_AssitLigh->SetDiffuse(DEFAULT_FIRE_DIFFUSE + vec3(r, g, b));
		m_AssitLigh->SetSpecular(DEFAULT_FIRE_SPECULAR + vec3(r, g, b));
	}
}


Fire::~Fire()
{
}

Fire * Fire::Create(Animation animation)
{
	Fire* pRet = new(std::nothrow)Fire();
	if (pRet && pRet->Init(animation)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

PointLight * Fire::GetMainLight()
{
	return m_MainLight;
}

PointLight * Fire::GetAssitLight()
{
	return m_AssitLigh;
}

void Fire::SetLight(PointLight * light)
{
	if (light == nullptr)	return;
	m_AssitLigh = light;
}
