
/*
*	火焰类，本质上是一个2.5D的动画组件
*	带有一个点光源信息
*/

#ifndef _FIRE_H_
#define _FIRE_H_
#pragma once

#include"Animator2_5D.h"
#include"PointLight.h"

const vec3 DEFAULT_FIRE_AMBIENT = vec3(0.416f, 0.184f, 0.246f);
const vec3 DEFAULT_FIRE_DIFFUSE = vec3(0.846f, 0.396f, 0.264f);
const vec3 DEFAULT_FIRE_SPECULAR = vec3(0.071f, 0.180f, 0.161f);

const float XShakeFactor = 9.0f;
const float YShakeFactor = 3.0f;
const float ZShakeFactor = 9.0f;
const float RandomFactor = 32.0f;

const float RShakeFactor = 0.05f;
const float GShakeFactor = 0.08f;
const float BShakeFactor = 0.15f;

class Fire :public Animator2_5D
{
private:
	PointLight * m_MainLight;							// 主要光源
	PointLight * m_AssitLigh;							// 闪烁光源
	float m_DeltaTime;
protected:
	Fire();
	virtual bool Init(Animation animation);
	virtual void Update(float deltaTime);
public:
	~Fire();

	static Fire* Create(Animation animation);

	PointLight* GetMainLight();
	PointLight* GetAssitLight();
	void SetLight(PointLight* light);
};



#endif // !_FIRE_H_


