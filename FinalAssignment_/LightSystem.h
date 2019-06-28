
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
	// 保存当前场景所有BaseLight的衍生类
	static std::vector<BaseLight*> m_Lights;
public:
	void AddLight(BaseLight* light);
	void RemoveLight(BaseLight* light);
	void ClearLight();

	// 灯光烘焙，为传参的shader填充LightSystem中的灯光信息
	void LightBake(Shader* shader);
	// 得到所有光源的位置，用以物体产生阴影
	std::vector<vec3> GetLightsPosition();
};


#endif // !_LIGHT_SYSTEM_H_


