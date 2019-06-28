#include "CameraSystem.h"

CameraSystem* CameraSystem::m_Instance = nullptr;
MyCamera* CameraSystem::m_MainCamera = nullptr;

CameraSystem::CameraSystem()
{
}


CameraSystem::~CameraSystem()
{
}

CameraSystem * CameraSystem::Create()
{
	if (m_Instance == nullptr) {
		m_Instance = new (std::nothrow)CameraSystem();
		if (m_Instance && m_Instance->Init()) {
			return m_Instance;
		}
		else {
			delete m_Instance;
			m_Instance = nullptr;
			return nullptr;
		}

	}
	return m_Instance;
}

bool CameraSystem::Init()
{
	if (!Ref::Init()) {
		return false;
	}
	return true;
}

void CameraSystem::SetMainCamera(MyCamera * camera)
{
	if (camera == nullptr) {
		return;
	}
	m_MainCamera = camera;
}
