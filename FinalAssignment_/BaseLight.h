
#ifndef _BASE_LIGHT_H_
#define _BASE_LIGHT_H_
#pragma once

#include<Shader_GLUT.h>
#include"Node.h"

// 灯光类型
enum LightType {
	DIRECTION_LIGHT,		// 方向光
	POINT_LIGHT,			// 点光源
	SPOT_LIGHT				// 聚光灯
};

const vec3 DEFAULT_AMBIENT = vec3(0.8f);					// 默认环境光分量
const vec3 DEFAULT_DIFFUSE = vec3(0.5f);					// 默认漫反射分量
const vec3 DEFAULT_SPECULAR = vec3(0.3f);					// 默认镜面反射分量

const vec3 DEFAULT_DIRECTION = vec3(0.0f, 0.0f, -1.0f);		// 默认朝向为z轴负方向

// 衰减因子系数
const float CONSTANT = 1.0f;
const float LINEAR = 0.22f;
const float QUADRATIC = 0.20f;

// 衰减因子结构体
struct AttenuationFactor {
	float Constant;											// 常数项
	float Linear;											// 线性项
	float Quadratic;										// 二次项

	AttenuationFactor() :Constant(CONSTANT), Linear(LINEAR), Quadratic(QUADRATIC) {}
	AttenuationFactor(float c, float l, float q) :Constant(c), Linear(l), Quadratic(q) {}
};

namespace AttrnuationFactorPreset {
	// 一些衰减因子的常量
	// 后面的数据表示最远能照射到的距离
	const AttenuationFactor FACTOR_7 = AttenuationFactor(1.0f, 0.7f, 1.8f);
	const AttenuationFactor FACTOR_13 = AttenuationFactor(1.0f, 0.35f, 0.44f);
	const AttenuationFactor FACTOR_20 = AttenuationFactor(1.0f, 0.22f, 0.20f);
	const AttenuationFactor FACTOR_32 = AttenuationFactor(1.0f, 0.14f, 0.07f);
	const AttenuationFactor FACTOR_50 = AttenuationFactor(1.0f, 0.09f, 0.032f);
	const AttenuationFactor FACTOR_65 = AttenuationFactor(1.0f, 0.07f, 0.017f);
	const AttenuationFactor FACTOR_100 = AttenuationFactor(1.0f, 0.045f, 0.0075f);
	const AttenuationFactor FACTOR_160 = AttenuationFactor(1.0f, 0.027f, 0.0028f);
	const AttenuationFactor FACTOR_200 = AttenuationFactor(1.0f, 0.022f, 0.0019f);
	const AttenuationFactor FACTOR_325 = AttenuationFactor(1.0f, 0.014f, 0.0007f);
	const AttenuationFactor FACTOR_600 = AttenuationFactor(1.0f, 0.007f, 0.0002f);
	const AttenuationFactor FACTOR_3250 = AttenuationFactor(1.0f, 0.0014f, 0.000007f);
}


class BaseLight :public Node
{
protected:
	bool m_Valiable;			// 是否有效
	LightType m_Type;			// 光源的类型

	vec3 m_Ambient;				// 环境光颜色强度
	vec3 m_Diffuse;				// 漫反射颜色强度
	vec3 m_Specular;			// 镜面反射颜色强度
protected:
	virtual bool Init()override;
	virtual bool Render()override;
public:
	LightType GetLightType() { return m_Type; }

	void SetAmbient(vec3 ambient) { m_Ambient = ambient; }
	void SetDiffuse(vec3 diffuse) { m_Diffuse = diffuse; }
	void SetSpecular(vec3 specular) { m_Specular = specular; }

	vec3 GetAmbient() { return m_Ambient; }
	vec3 GetDiffuse() { return m_Diffuse; }
	vec3 GetSpecular() { return m_Specular; }

	void SetValiable(bool flag) { m_Valiable = flag; }
	bool IsValiable() { return m_Valiable; }

	// @TODO：继承BaseLight的灯光解释自己，装填进着色器的对应uniform路径
	// BaseLight只负责填充共有的灯光属性，如环境光、漫反射、镜面反射强度等
	virtual void LoadLight(Shader* shader, std::string uniformPath);
	virtual vec3 GetLightPosition() = 0;
};


#endif // !_BASE_LIGHT_H_



