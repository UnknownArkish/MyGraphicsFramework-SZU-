#include "CubeMap.h"

#include<stb_image.h>

CubeMap::CubeMap()
{
}

bool CubeMap::Init(std::vector<std::string> faces)
{
	if (!Ref::Init()) {
		return false;
	}

	InitCubeMap(faces);

	return true;
}

CubeMap::~CubeMap()
{
}

CubeMap * CubeMap::Create(std::vector<std::string> faces)
{
	CubeMap* pRet = new(std::nothrow)CubeMap();
	if (pRet && pRet->Init(faces)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

void CubeMap::Bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void CubeMap::InitCubeMap(std::vector<std::string> faces)
{
	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &ID);								// 创建一个贴图索引
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);				// 绑定为立方体贴图对象

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {	// 迭代绑定每个面的贴图
		// 调用库加载图片data
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format;
			if (nrChannels == 1)	format = GL_RED;
			else if (nrChannels == 3)	format = GL_RGB;
			else if (nrChannels == 4)	format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
