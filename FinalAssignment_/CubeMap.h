
#ifndef _CUBE_MAP_H_
#define  _CUBE_MAP_H_
#pragma once

#include"Ref.h"
#include"TextureInfo.h"

class CubeMap :public Ref
{
public:
	GLuint ID;			// CubeMapµÄË÷ÒýÖµ
protected:
	CubeMap();
	virtual bool Init(std::vector<std::string> facess);
public:
	~CubeMap();
	static CubeMap* Create(std::vector<std::string> faces);

	void Bind()const;
private:
	void InitCubeMap(std::vector<std::string> faces);
};

#endif // !_CUBE_MAP_H_




