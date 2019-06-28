
/*
*	利用以前所写的框架，搭的一个场景
*/

#ifndef _MY_SCENE_H_
#define _MY_SCENE_H_
#pragma once

#include<vector>

#include"Scene.h"
#include"KeyboardListener.h"
#include"Fire.h"
#include"Plane.h"
#include"DirectionLight.h"
#include"Robot.h"
#include"SpotLight.h"


const vec3 EnvironmentAmbient = vec3(0.067f, 0.149f, 0.310f);
const vec3 EnvironmentDiffuse = vec3(0.0f, 0.0f, 0.0f);
const vec3 EnvironmentSpecular = vec3(0.0f, 0.0f, 0.0f);

const vec3 FixLightAmbient = vec3(0.681, 0.447f, 0.722f);
const vec3 FixLightDiffuse = vec3(0.953f, 0.443f, 0.361f);
const vec3 FixLightSpecular = vec3(0.686f, 0.875f, 0.894f);

// 地面
const Material Ground = Material(vec3(0.849, 0.427f, 0.255f), vec3(0.961, 0.510f, 0.125f), vec3(0.251, 0.110f, 0.267f), 1000.0f);
const Material Grass = Material(vec3(0.416f, 0.420f, 0.255f), vec3(0.213f, 0.601f, 0.212f), vec3(0.618f, 0.725f, 0.200f), 32.0f);
const Material Tree = Material(vec3(0.216f, 0.345f, 0.188f), vec3(0.416f, 0.601f, 0.212f), vec3(0.618f, 0.725f, 0.200f), 32.0f);
const Material Human = Material(vec3(0.267, 0.412, 0.576), vec3(0.733f, 0.314f, 0.365f), vec3(0.980, 0.698f, 0.482f), 128.0f);

const int Size_Of_Ground = 10;						// 10 * 10 方块组成的地面


// 篝火参数
const int Circle_Num = 4;							// 篝火的圈数
const int Maximum_Fire_Circle_Num = 1;				// 真火的最多层数
const int Interaval_Num_Fire_Per_Circle = 1;		// 每圈增加的篝火的个数
const float Radius_Per_Circle = 0.20f;				// 每圈增加的半径


// 草&草丛参数
const int Grass_Num = 8;							// 单草个数

const int GrassPath_Num = 9;						// 草丛个数
const int GrassPath_Per_Grass_Num = 5;				// 每个草丛的草个数
const float GrassPathRadius = 1.0f;					// 草丛半径

const float Dense_Level = 0.76f;					// 密集程度


// 树木参数
const int Tree_Num = 17;

// 石头参数
const int Stone_Num = 7;

// 颜色噪音参数
const float _RShakeFactor = 0.05f;
const float _GShakeFactor = 0.05f;
const float _BShakeFactor = 0.02f;

// 人物参数
const float SittedHuman_Leg_Swing_Range = 10.0f;	// 腿摆动幅度
const float SwingDurarion = 1.0f;					// 持续时间


class MyScene :public Scene, public KeyboardListener
{
private:
	std::vector<Plane*> m_Grounds;
	Node* m_Bondfire;

	DirectionLight* m_AmbienLight;		// 环境光
	SpotLight* m_FlashLight;			// 手电筒

	Robot* m_Human_Sitted;
	Robot* m_Human_Stand;
protected:
	MyScene();
	virtual bool Init()override;
public:
	~MyScene();

	static MyScene* Create();

	virtual void Update(float deltaTime)override;
private:
	void InitCameraContoller();			// 初始化摄像机控制器
	void InitSceneController();			// 初始化场景的监听器
	void InitSkybox();					// 初始化天空盒
	void InitAmbientLight();			// 初始化环境光
	void InitFlashLight();				// 初始化手电筒

	void InitGround();					// 初始化地面
	void InitFire();					// 初始化火
	void InitSnow();					// 初始化雪
	void InitRobot();					// 初始化机器人
	void InitRobotController();			// 初始化机器人空闲的控制器
	void InitModel();					// 初始化模型

	// 通过 KeyboardListener 继承
	virtual void OnKeyboardDown(KeyboardEventArgs * args) override;
	virtual void OnKeyboardUp(KeyboardEventArgs * args) override;
};

#endif // !_MY_SCENE_H_


