
#ifndef _MODEL_RESOURCE_H_
#define _MODEL_RESOURCE_H_
#pragma once

#include<assimp\scene.h>

class ModelResource {
public:
	aiScene * ModelScene;
	std::string Directory;
};


#endif // !_MODEL_RESOURCE_H_


