
#ifndef _MOUSE_EVENT_ARGS_H_
#define _MOUSE_EVENT_ARGS_H_
#pragma once

#include<Angel.h>

class MouseEventArgs
{
public:
	vec2 OriginLocation;				// ��ʼλ�ã�Passive����Location��ͬ��
	vec2 Location;						// ��ǰλ��
	int Button;							// ���µļ�λ
};




#endif // !_MOUSE_EVENT_ARGS_H_

