
#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_
#pragma once

#include"BaseLight.h"


///
///	���Դ����BaseLight�Ļ����ϼ���˥�����Ӳ���
///
class PointLight :public BaseLight
{
private:
	AttenuationFactor m_Factor;					// ˥������ϵ��
protected:
	PointLight();
	virtual bool Init()override;
public:
	~PointLight();

	static PointLight* Create();

	void SetFactor(AttenuationFactor factor) { m_Factor = factor; }
	void SetConstant(float constant) { m_Factor.Constant = constant; }
	void SetLinear(float linear) { m_Factor.Linear = linear; }
	void SetQuadratic(float quadratic) { m_Factor.Quadratic = quadratic; }

	AttenuationFactor GetFactor() { return m_Factor; }
	float GetConstant() { return m_Factor.Constant; }
	float GetLinear() { return m_Factor.Linear; }
	float GetQuadratic() { return m_Factor.Quadratic; }

	// ͨ�� BaseLight �̳�
	virtual void LoadLight(Shader * shader, std::string uniformPath) override;

	// ͨ�� BaseLight �̳�
	virtual vec3 GetLightPosition() override;
};





#endif // !_POINT_LIGHT_H_

