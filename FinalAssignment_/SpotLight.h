
#ifndef _SPOT_LIGHT_H_
#define _SPOT_LIGHT_H_
#pragma once

#include"BaseLight.h"

const float DEFAULT_CUT_OFF = 12.5f;
const float DEFAULT_OUTER_CUT_OFF = 17.5f;

///
///	�۹��
///
class SpotLight :public BaseLight
{
private:
	vec3 m_DefaultDirection;				// ��Դ����һ��ͨ����תʵ��ת��
											// Ĭ�ϳ���z�Ḻ����
	// ��Եģ��ϵ��
	float m_CutOff;							// �ڰ뾶ϵ��
	float m_OuterCutOff;					// ��뾶ϵ��
	AttenuationFactor m_Factor;				// ˥������ϵ��
protected:
	SpotLight();
	virtual bool Init()override;
public:
	~SpotLight();
	static SpotLight* Create();

	void SetDirection(vec3 direction) { m_DefaultDirection = direction; }

	// ˥������Setter
	void SetFactor(AttenuationFactor factor) { m_Factor = factor; }
	void SetConstant(float constant) { m_Factor.Constant = constant; }
	void SetLinear(float linear) { m_Factor.Linear = linear; }
	void SetQuadratic(float quadratic) { m_Factor.Quadratic = quadratic; }
	// ģ��ϵ��Setter
	void SetCutOff(float cutOff) { m_CutOff = cutOff; }
	void SetOuterCutOff(float cutOff) { m_OuterCutOff = cutOff; }

	// ˥������Getter
	AttenuationFactor GetFactor() { return m_Factor; }
	float GetConstant() { return m_Factor.Constant; }
	float GetLinear() { return m_Factor.Linear; }
	float GetQuadratic() { return m_Factor.Quadratic; }
	// ģ��ϵ��Getter
	float GetCutOff() { return m_CutOff; }
	float GetOuterCutOff() { return m_OuterCutOff; }

	// ͨ�� BaseLight �̳�
	virtual void LoadLight(Shader * shader, std::string uniformPath) override;

	// ͨ�� BaseLight �̳�
	virtual vec3 GetLightPosition() override;
};


#endif // !_SPOT_LIGHT_H_


