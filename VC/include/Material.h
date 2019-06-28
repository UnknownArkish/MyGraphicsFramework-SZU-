
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#pragma once

#include<Angel.h>

class Material {
public:
	vec4 AmbientColor = { 0.5f,0.5f,0.5f,1.0f };	// 环境光强度分量
	vec4 DiffuseColor = { 0.5f,0.5f,0.5f,1.0f };	// 漫反射强度分量
	vec4 SpecularColor = { 0.5f,0.5f,0.5f,1.0f };	// 镜面反射强度分量 
	float Shininesss = 50.0f;						// 高光系数

	float AttenuationConstact = 0.03f;				// 常量衰减系数
	float AttenuationLinear = 0.01f;				// 常量衰减系数
	float AttenuationQuadratic = 0.05f;				// 常量衰减系数

	vec4 Emission = { 0.0f,0.0f,0.0f,1.0f };		// 自发光分量
};



#endif // !_MATERIAL_H_


