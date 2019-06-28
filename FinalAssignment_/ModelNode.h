
#ifndef _MODEL_NODE_H_
#define _MODEL_NODE_H_
#pragma once

#include"Node.h"
#include"ModelMesh.h"
#include"ModelResource.h"

class ModelNode : public Node {
private:
	ModelResource* m_ModelResource;
protected:
	virtual bool Init(ModelResource* modelResource);
public:
	static ModelNode* Create(ModelResource* modelResource);
};

#endif // !_MODEL_NODE_H_



