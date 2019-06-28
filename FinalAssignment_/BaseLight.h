
#ifndef _BASE_LIGHT_H_
#define _BASE_LIGHT_H_
#pragma once

#include<Shader_GLUT.h>
#include"Node.h"

// �ƹ�����
enum LightType {
	DIRECTION_LIGHT,		// �����
	POINT_LIGHT,			// ���Դ
	SPOT_LIGHT				// �۹��
};

const vec3 DEFAULT_AMBIENT = vec3(0.8f);					// Ĭ�ϻ��������
const vec3 DEFAULT_DIFFUSE = vec3(0.5f);					// Ĭ�����������
const vec3 DEFAULT_SPECULAR = vec3(0.3f);					// Ĭ�Ͼ��淴�����

const vec3 DEFAULT_DIRECTION = vec3(0.0f, 0.0f, -1.0f);		// Ĭ�ϳ���Ϊz�Ḻ����

// ˥������ϵ��
const float CONSTANT = 1.0f;
const float LINEAR = 0.22f;
const float QUADRATIC = 0.20f;

// ˥�����ӽṹ��
struct AttenuationFactor {
	float Constant;											// ������
	float Linear;											// ������
	float Quadratic;										// ������

	AttenuationFactor() :Constant(CONSTANT), Linear(LINEAR), Quadratic(QUADRATIC) {}
	AttenuationFactor(float c, float l, float q) :Constant(c), Linear(l), Quadratic(q) {}
};

namespace AttrnuationFactorPreset {
	// һЩ˥�����ӵĳ���
	// ��������ݱ�ʾ��Զ�����䵽�ľ���
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
	bool m_Valiable;			// �Ƿ���Ч
	LightType m_Type;			// ��Դ������

	vec3 m_Ambient;				// ��������ɫǿ��
	vec3 m_Diffuse;				// ��������ɫǿ��
	vec3 m_Specular;			// ���淴����ɫǿ��
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

	// @TODO���̳�BaseLight�ĵƹ�����Լ���װ�����ɫ���Ķ�Ӧuniform·��
	// BaseLightֻ������乲�еĵƹ����ԣ��绷���⡢�����䡢���淴��ǿ�ȵ�
	virtual void LoadLight(Shader* shader, std::string uniformPath);
	virtual vec3 GetLightPosition() = 0;
};


#endif // !_BASE_LIGHT_H_



