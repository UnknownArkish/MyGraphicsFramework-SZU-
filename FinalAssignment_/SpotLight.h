
#ifndef _SPOT_LIGHT_H_
#define _SPOT_LIGHT_H_
#pragma once

#include"BaseLight.h"

const float DEFAULT_CUT_OFF = 12.5f;
const float DEFAULT_OUTER_CUT_OFF = 17.5f;

///
///	聚光灯
///
class SpotLight :public BaseLight
{
private:
	vec3 m_DefaultDirection;				// 光源朝向，一般通过旋转实现转向
											// 默认朝向z轴负方向
	// 边缘模糊系数
	float m_CutOff;							// 内半径系数
	float m_OuterCutOff;					// 外半径系数
	AttenuationFactor m_Factor;				// 衰减因子系数
protected:
	SpotLight();
	virtual bool Init()override;
public:
	~SpotLight();
	static SpotLight* Create();

	void SetDirection(vec3 direction) { m_DefaultDirection = direction; }

	// 衰减因子Setter
	void SetFactor(AttenuationFactor factor) { m_Factor = factor; }
	void SetConstant(float constant) { m_Factor.Constant = constant; }
	void SetLinear(float linear) { m_Factor.Linear = linear; }
	void SetQuadratic(float quadratic) { m_Factor.Quadratic = quadratic; }
	// 模糊系数Setter
	void SetCutOff(float cutOff) { m_CutOff = cutOff; }
	void SetOuterCutOff(float cutOff) { m_OuterCutOff = cutOff; }

	// 衰减因子Getter
	AttenuationFactor GetFactor() { return m_Factor; }
	float GetConstant() { return m_Factor.Constant; }
	float GetLinear() { return m_Factor.Linear; }
	float GetQuadratic() { return m_Factor.Quadratic; }
	// 模糊系数Getter
	float GetCutOff() { return m_CutOff; }
	float GetOuterCutOff() { return m_OuterCutOff; }

	// 通过 BaseLight 继承
	virtual void LoadLight(Shader * shader, std::string uniformPath) override;

	// 通过 BaseLight 继承
	virtual vec3 GetLightPosition() override;
};


#endif // !_SPOT_LIGHT_H_


