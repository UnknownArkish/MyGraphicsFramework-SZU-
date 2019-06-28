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

	// ���ó�ʼ�����Ϣ
	vec2 screenSize = Game::GetInstance()->GetWindowSize();
	m_LastMouseX = screenSize.x / 2;
	m_LastMouseY = screenSize.y / 2;
	// �����ƶ��Ժ�����λ��
	Game::GetInstance()->SetCursorPosition(screenSize / 2);

	// ���ó��е�robot�������ϵͳ
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
	// @TODO������������robot���ƶ��Լ�����
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
	// @TODO��������ָ�robot�Ķ���״̬��Ϣ

}

void RobotController::OnMousePassive(MouseEventArgs * args)
{
	vec2 loc = args->Location;

	int dx = loc.x - m_LastMouseX;
	int dy = m_LastMouseY - loc.y;

	// �����Ļ��С
	vec2 screenSize = Game::GetInstance()->GetWindowSize();
	m_LastMouseX = screenSize.x / 2;
	m_LastMouseY = screenSize.y / 2;
	// �����ƶ��Ժ�����λ��
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
