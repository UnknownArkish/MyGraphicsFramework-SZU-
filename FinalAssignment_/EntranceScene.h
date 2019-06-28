
#ifndef _ENTRANCE_SCENE_H_
#define _ENTRANCE_SCENE_H_
#pragma once

#include"Scene.h"

class EntranceScene :public Scene
{
private:
	virtual bool Init();
protected:
	EntranceScene();
public:
	~EntranceScene();
public:
	static EntranceScene* Create();
};



#endif // !_ENTRANCE_SCENE_H_


