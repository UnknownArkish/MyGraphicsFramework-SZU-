#include "Renderer.h"



Renderer::Renderer()
{

}


Renderer::~Renderer()
{
}

bool Renderer::Init()
{
	if (!Ref::Init()) {
		return false;
	}

	this->LoadModel();
	this->InitData();
	this->InitShader();
	this->BindObject();
	return true;
}
