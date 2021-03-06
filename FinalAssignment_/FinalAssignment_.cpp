// FinalAssignment_.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include"Game.h"

int main(int argc, char** argv)
{
	// @TODO：初始化OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(Config::Screen_Wdith, Config::Screen_Height);
	Game::Window = glutCreateWindow("期末作业_2016150091_黄兆铭");
	glewExperimental = GL_TRUE;

	glewInit();

	// @TODO：程序初始化
	Game::GetInstance()->Init();

	// @TODO：注册Game回调函数，中转使用
	glutDisplayFunc(Game::Display);						// 绘制回调Unsure
	glutIdleFunc(Game::Idle);							// 空闲回调

	glutKeyboardFunc(Game::KeyboardDown);				// 按键按下回调
	glutKeyboardUpFunc(Game::KeyboardUp);				// 按键松开回调
	glutMouseFunc(Game::Mouse);							// 鼠标按下/松开回调
	glutMotionFunc(Game::Motion);						// 鼠标Motion回调(按下某个键拖动鼠标时)
	glutPassiveMotionFunc(Game::Passive);				// 鼠标Passive回调（没有按下键拖动鼠标时）

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Game::GetInstance()->StartGame();					// 开始计时
	glutMainLoop();

	return 0;
}

