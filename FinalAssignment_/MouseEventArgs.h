
#ifndef _MOUSE_EVENT_ARGS_H_
#define _MOUSE_EVENT_ARGS_H_
#pragma once

#include<Angel.h>

class MouseEventArgs
{
public:
	vec2 OriginLocation;				// 初始位置（Passive下与Location相同）
	vec2 Location;						// 当前位置
	int Button;							// 按下的键位
};




#endif // !_MOUSE_EVENT_ARGS_H_

