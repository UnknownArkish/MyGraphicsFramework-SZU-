#include"RobotController.h"

#include"Game.h"
#include"GameModel.h"

RobotController::RobotController()
{
}

bool RobotController::Init(Robot * robot)
{
	if (!BaseController::Init()) {
		return false;
	}

	// 设置初始鼠标信息
	vec2 screenSize = Game::GetInstance()->GetWindowSize();
	m_LastMouseX = screenSize.x / 2;
	m_LastMouseY = screenSize.y / 2;
	// 更新移动以后的鼠标位置
	Game::GetInstance()->SetCursorPosition(screenSize / 2);

	// 设置持有的robot和摄像机系统
	m_Robot = robot;
	m_CameraSystem = CameraSystem::GetInstance();

	return true;
}


RobotController::~RobotController()
{
}

RobotController * RobotController::Create(Robot * robot)
{
	RobotController* pRet = new(std::nothrow)RobotController();
	if (pRet && pRet->Init(robot)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void RobotController::OnKeyboardDown(KeyboardEventArgs * args)
{
	// @TODO：在这里设置robot的移动以及动画
	switch (tolower(args->Key))
	{
	case 'w':
		m_Robot->ToTranslate(m_Robot->GetGlobalZ()*GameModel::DeltaTime);
		break;
	default:
		break;
	}


}

void RobotController::OnKeyboardUp(KeyboardEventArgs * args)
{
	// @TODO：在这里恢复robot的动画状态信息

}

void RobotController::OnMousePassive(MouseEventArgs * args)
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

	if (m_Robot) {
		m_Robot->ToRotate(vec3(0.0f, -dx, 0.0f));
	}

	MyCamera* camera = CameraSystem::GetInstance()->GetMainCamera();
}

bool RobotController::OnMouseDown(MouseEventArgs * args)
{
	return false;
}

void RobotController::OnMouseMotion(MouseEventArgs * args)
{
}

void RobotController::OnMouseUp(MouseEventArgs * args)
{
}
