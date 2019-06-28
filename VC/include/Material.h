
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#pragma once

#include<Angel.h>

class Material {
public:
	vec4 AmbientColor = { 0.5f,0.5f,0.5f,1.0f };	// ������ǿ�ȷ���
	vec4 DiffuseColor = { 0.5f,0.5f,0.5f,1.0f };	// ������ǿ�ȷ���
	vec4 SpecularColor = { 0.5f,0.5f,0.5f,1.0f };	// ���淴��ǿ�ȷ��� 
	float Shininesss = 50.0f;						// �߹�ϵ��

	float AttenuationConstact = 0.03f;				// ����˥��ϵ��
	float AttenuationLinear = 0.01f;				// ����˥��ϵ��
	float AttenuationQuadratic = 0.05f;				// ����˥��ϵ��

	vec4 Emission = { 0.0f,0.0f,0.0f,1.0f };		// �Է������
};



#endif // !_MATERIAL_H_


