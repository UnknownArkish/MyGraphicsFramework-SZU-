
/*
*	������ǰ��д�Ŀ�ܣ����һ������
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

// ����
const Material Ground = Material(vec3(0.849, 0.427f, 0.255f), vec3(0.961, 0.510f, 0.125f), vec3(0.251, 0.110f, 0.267f), 1000.0f);
const Material Grass = Material(vec3(0.416f, 0.420f, 0.255f), vec3(0.213f, 0.601f, 0.212f), vec3(0.618f, 0.725f, 0.200f), 32.0f);
const Material Tree = Material(vec3(0.216f, 0.345f, 0.188f), vec3(0.416f, 0.601f, 0.212f), vec3(0.618f, 0.725f, 0.200f), 32.0f);
const Material Human = Material(vec3(0.267, 0.412, 0.576), vec3(0.733f, 0.314f, 0.365f), vec3(0.980, 0.698f, 0.482f), 128.0f);

const int Size_Of_Ground = 10;						// 10 * 10 ������ɵĵ���


// �������
const int Circle_Num = 4;							// �����Ȧ��
const int Maximum_Fire_Circle_Num = 1;				// ����������
const int Interaval_Num_Fire_Per_Circle = 1;		// ÿȦ���ӵ�����ĸ���
const float Radius_Per_Circle = 0.20f;				// ÿȦ���ӵİ뾶


// ��&�ݴԲ���
const int Grass_Num = 8;							// ���ݸ���

const int GrassPath_Num = 9;						// �ݴԸ���
const int GrassPath_Per_Grass_Num = 5;				// ÿ���ݴԵĲݸ���
const float GrassPathRadius = 1.0f;					// �ݴ԰뾶

const float Dense_Level = 0.76f;					// �ܼ��̶�


// ��ľ����
const int Tree_Num = 17;

// ʯͷ����
const int Stone_Num = 7;

// ��ɫ��������
const float _RShakeFactor = 0.05f;
const float _GShakeFactor = 0.05f;
const float _BShakeFactor = 0.02f;

// �������
const float SittedHuman_Leg_Swing_Range = 10.0f;	// �Ȱڶ�����
const float SwingDurarion = 1.0f;					// ����ʱ��


class MyScene :public Scene, public KeyboardListener
{
private:
	std::vector<Plane*> m_Grounds;
	Node* m_Bondfire;

	DirectionLight* m_AmbienLight;		// ������
	SpotLight* m_FlashLight;			// �ֵ�Ͳ

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
	void InitCameraContoller();			// ��ʼ�������������
	void InitSceneController();			// ��ʼ�������ļ�����
	void InitSkybox();					// ��ʼ����պ�
	void InitAmbientLight();			// ��ʼ��������
	void InitFlashLight();				// ��ʼ���ֵ�Ͳ

	void InitGround();					// ��ʼ������
	void InitFire();					// ��ʼ����
	void InitSnow();					// ��ʼ��ѩ
	void InitRobot();					// ��ʼ��������
	void InitRobotController();			// ��ʼ�������˿��еĿ�����
	void InitModel();					// ��ʼ��ģ��

	// ͨ�� KeyboardListener �̳�
	virtual void OnKeyboardDown(KeyboardEventArgs * args) override;
	virtual void OnKeyboardUp(KeyboardEventArgs * args) override;
};

#endif // !_MY_SCENE_H_


