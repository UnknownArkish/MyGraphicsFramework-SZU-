#include "ModelNode.h"

bool ModelNode::Init(ModelResource* modelResource)
{
	if (!Node::Init()) {
		return false;
	}

	m_ModelResource = modelResource;

	return true;
}

ModelNode * ModelNode::Create(ModelResource* modelResource)
{
	ModelNode* pRet = new(std::nothrow)ModelNode();
	if (pRet && pRet->Init(modelResource)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}
