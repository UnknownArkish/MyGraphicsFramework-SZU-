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
	Clear();		// É¾³ýOpenGL¶ÔÏó
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
