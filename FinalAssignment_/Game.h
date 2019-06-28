
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
	// ����Game��״̬����
	static GLboolean m_IsStart;			// �Ƿ�ʼ
	static Scene* m_CurrentScene;		// ��ǰ���Ƶĳ���
public:
	// һЩOpenGL����
	static GLuint Window;				// ��������
	//static GLfloat FPS;					// ֡��
	static GLuint m_BaseTime;			// Game�Ļ�׼ʱ��
public:
	// @TODO��һЩ����OpenGL�ص��ľ�̬����
	static void KeyboardDown(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void Motion(int x, int y);
	static void Passive(int x, int y);
	// @TODO��display��Ⱦ����
	static void Display();
	// @TODO��Idle����
	static void Idle();
private:
	static void Update(Node* node);							// ���º�����ÿ֡����һ��

	void InitEnvironment();					// ��ʼ���������еĻ�������FPS�ȣ�
	void InitFramework();					// ��ʼ�������еĿ��ϵͳ������������롢���յȣ�
	void InitResources();					// ��ʼ����Ҫ����Դ������ɫ���ȣ�
	void InitMiscellaneous();				// ��ʼ������
	void InitShader();						// ��ʼ����Դ�е���ɫ��
	void InitTexture();						// ��ʼ����Դ�е���ͼ
public:
	void StartGame();
	// ������ʼ�����
	void Init();

	void EnterScene(Scene* scene);			// �����µĳ�������

	void SetCursorPosition(vec2 pos);		// ����������Ӵ���λ�ã�������Ӵ����Ͻǣ�
	vec2 GetWindowPosition();				// ����Ӵ��������Ļ���Ͻǵ�����
	vec2 GetWindowSize();					// ��ô��ڵĴ�С
	GLuint GetRunTime();					// ��ȡ��ǰ����ʱ��
};


#endif // !_GAME_H_
