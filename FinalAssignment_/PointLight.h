
#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_
#pragma once

#include"BaseLight.h"


///
///	点光源，在BaseLight的基础上加上衰减因子参数
///
class PointLight :public BaseLight
{
private:
	AttenuationFactor m_Factor;					// 衰减因子系数
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

	// 通过 BaseLight 继承
	virtual void LoadLight(Shader * shader, std::string uniformPath) override;

	// 通过 BaseLight 继承
	virtual vec3 GetLightPosition() override;
};





#endif // !_POINT_LIGHT_H_

