
#ifndef _LIGHT_SYSTEM_H_
#define _LIGHT_SYSTEM_H_
#pragma once

#include"BaseLight.h"
#include"Ref.h"
#include<Shader_GLUT.h>

class LightSystem :public Ref
{
private:
	static LightSystem* m_Instance;
	LightSystem();
	~LightSystem();
public:
	static LightSystem* GetInstance() { return m_Instance; }
	static LightSystem* Create();
private:
	virtual bool Init();
private:
	// ���浱ǰ��������BaseLight��������
	static std::vector<BaseLight*> m_Lights;
public:
	void AddLight(BaseLight* light);
	void RemoveLight(BaseLight* light);
	void ClearLight();

	// �ƹ�決��Ϊ���ε�shader���LightSystem�еĵƹ���Ϣ
	void LightBake(Shader* shader);
	// �õ����й�Դ��λ�ã��������������Ӱ
	std::vector<vec3> GetLightsPosition();
};


#endif // !_LIGHT_SYSTEM_H_


