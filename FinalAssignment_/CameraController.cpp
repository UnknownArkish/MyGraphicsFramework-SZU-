#include"stdafx.h"
#include "CameraController.h"

#include"Game.h"
#include"GameModel.h"

CameraController::CameraController()
{
	if (m_CameraSystem == nullptr) {
		m_CameraSystem = CameraSystem::GetInstance();
	}
}

CameraController::~CameraController()
{
}

CameraController * CameraController::Create()
{
	CameraController* pRet = new(std::nothrow)CameraController();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	return nullptr;
}

bool CameraController::Init()
{
	if (!BaseController::Init()) {
		return false;
	}
	m_IsFirstKeyDown = true;
	m_LastMouseX = Config::Screen_Wdith / 2;
	m_LastMouseY = Config::Screen_Height / 2;
	return true;
}

void CameraController::OnKeyboardDown(KeyboardEventArgs * args)
{
	//if (m_IsFirstKeyDown) {
	//	m_IsFirstKeyDown = false;
	//	return;
	//}

	// @TODO：前后左右移动
	MyCamera* camera = m_CameraSystem->GetMainCamera();
	if (camera) {
		GLfloat deltaTime = GameModel::DeltaTime;
		if (InputSystem::Keys['w']) {
			camera->ProcessKeyboard(My_Camera_Movement::Forward, deltaTime);
		}
		if (InputSystem::Keys['s']) {
			camera->ProcessKeyboard(My_Camera_Movement::Backward, deltaTime);
		}
		if (InputSystem::Keys['a']) {
			camera->ProcessKeyboard(My_Camera_Movement::Left, deltaTime);
		}
		if (InputSystem::Keys['d']) {
			camera->ProcessKeyboard(My_Camera_Movement::Right, deltaTime);
		}
	}
}

void CameraController::OnKeyboardUp(KeyboardEventArgs * args)
{
	//if (InputSystem::Keys['w'] || InputSystem::Keys['s'] || InputSystem::Keys['a'] || InputSystem::Keys['d']) {
	//	return;
	//}
	//m_IsFirstKeyDown = true;
	//return;
}

void CameraController::OnMousePassive(MouseEventArgs * args)
{
	vec2 loc = args->Location;

	int dx = loc.x - m_LastMouseX;
	int dy = m_LastMouseY - loc.y;

	// 获得屏幕大小
	vec2 screenSize = Game::GetInstance()->GetWindowSize();
	m_LastMouseX = screenSize.x / 2;
	m_LastMouseY = screenSize.y / 2;
	// 更新移动以后的鼠标位置
	Game::GetInstance()->SetCursorPosition(screenSize / 2);

	MyCamera* camera = m_CameraSystem->GetMainCamera();
	camera->ProcessMouseMovement(dx, dy);
	//vec3 rotation = camera->GetRotation();
	//vec3 globalRotation = camera->GetGlobalRotation();

	//float temp = globalRotation.y;
	//while (temp < 0)	temp += 360.0f;
	//while (temp >= 360.0f)	temp -= 360.0f;

	//if (temp < 180.0f)	rotation.x -= dy;
	//else	rotation.x += dy;
	//if (rotation.x > 89.0f)	rotation.x = 89.0f;
	//if (rotation.x < -89.0f)	rotation.x = -89.0f;
	//camera->SetRotation(rotation);
}

bool CameraController::OnMouseDown(MouseEventArgs * args)
{
	return true;
}

void CameraController::OnMouseMotion(MouseEventArgs * args)
{
	OnMousePassive(args);
}

void CameraController::OnMouseUp(MouseEventArgs * args)
{
}


