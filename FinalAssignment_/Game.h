
#ifndef _GAME_H_
#define _GAME_H_
#pragma once

#include<Angel.h>
#include"Scene.h"

class Game
{
private:
	static Game* m_Instance;
	Game();
	~Game();
public:
	static Game* GetInstance() { return m_Instance; }

private:
	// 描述Game的状态变量
	static GLboolean m_IsStart;			// 是否开始
	static Scene* m_CurrentScene;		// 当前绘制的场景
public:
	// 一些OpenGL变量
	static GLuint Window;				// 窗口索引
	//static GLfloat FPS;					// 帧率
	static GLuint m_BaseTime;			// Game的基准时间
public:
	// @TODO：一些用于OpenGL回调的静态函数
	static void KeyboardDown(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void Motion(int x, int y);
	static void Passive(int x, int y);
	// @TODO：display渲染函数
	static void Display();
	// @TODO：Idle函数
	static void Idle();
private:
	static void Update(Node* node);							// 更新函数，每帧调用一次

	void InitEnvironment();					// 初始化程序运行的环境（如FPS等）
	void InitFramework();					// 初始化程序中的框架系统（摄像机、输入、光照等）
	void InitResources();					// 初始化重要的资源（如着色器等）
	void InitMiscellaneous();				// 初始化杂项
	void InitShader();						// 初始化资源中的着色器
	void InitTexture();						// 初始化资源中的贴图
public:
	void StartGame();
	// 公共初始化入口
	void Init();

	void EnterScene(Scene* scene);			// 进入新的场景函数

	void SetCursorPosition(vec2 pos);		// 设置鼠标在视窗中位置（相对于视窗左上角）
	vec2 GetWindowPosition();				// 获得视窗相对于屏幕左上角的坐标
	vec2 GetWindowSize();					// 获得窗口的大小
	GLuint GetRunTime();					// 获取当前运行时间
};


#endif // !_GAME_H_
