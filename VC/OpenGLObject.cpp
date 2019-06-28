#include "include/OpenGLObject.h"

OpenGLObject::OpenGLObject()
{
	this->VertexPosition.clear();
	this->VertexColor.clear();
	this->TextureCoordinate.clear();
	this->VertexNormal.clear();
}

OpenGLObject::~OpenGLObject()
{
	Clear();		// ɾ��OpenGL����
}

void OpenGLObject::Init()
{
}

void OpenGLObject::Clear()
{
	glDeleteVertexArrays(1, &vao);

	this->VertexPosition.clear();
	this->VertexColor.clear();
	this->TextureCoordinate.clear();
	this->VertexNormal.clear();
}
