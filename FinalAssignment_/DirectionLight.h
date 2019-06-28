


#ifndef _DIRECTION_LIGHT_H_
#define _DIRECTION_LIGHT_H_
#pragma once

#include"BaseLight.h"

///
///	方向光类，继承自BaseLight
///
class DirectionLight :public BaseLight
{
private:
	vec3 m_DefaultDirection;		// 默认朝向位置为z轴负方向，通过旋转修改朝向
protected:
	DirectionLight();
	virtual bool Init()override;
public:
	~DirectionLight();
	static DirectionLight* Create();

	// 通过 BaseLight 继承
	virtual void LoadLight(Shader * shader, std::string uniformPath) override;

	// 通过 BaseLight 继承
	virtual vec3 GetLightPosition() override;
};


#endif // !_DIRECTION_LIGHT_H_


