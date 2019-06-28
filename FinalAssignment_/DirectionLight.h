


#ifndef _DIRECTION_LIGHT_H_
#define _DIRECTION_LIGHT_H_
#pragma once

#include"BaseLight.h"

///
///	������࣬�̳���BaseLight
///
class DirectionLight :public BaseLight
{
private:
	vec3 m_DefaultDirection;		// Ĭ�ϳ���λ��Ϊz�Ḻ����ͨ����ת�޸ĳ���
protected:
	DirectionLight();
	virtual bool Init()override;
public:
	~DirectionLight();
	static DirectionLight* Create();

	// ͨ�� BaseLight �̳�
	virtual void LoadLight(Shader * shader, std::string uniformPath) override;

	// ͨ�� BaseLight �̳�
	virtual vec3 GetLightPosition() override;
};


#endif // !_DIRECTION_LIGHT_H_


