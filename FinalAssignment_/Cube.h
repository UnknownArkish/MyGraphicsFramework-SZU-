
#ifndef _CUBE_H_
#define _CUBE_H_
#pragma once

#include"Node.h"
#include"Material.h"
#include"CubeMap.h"

class Cube :public Node
{
protected:
	Material m_Material;						// 方块材质
	CubeMap* m_CubeMap = nullptr;				// 立方体贴图，优先使用立方体贴图
protected:
	Cube();

	virtual bool Render()override;
	virtual bool Init()override;
public:
	~Cube();
	static Cube* Create();

	void SetMaterial(Material material) { this->m_Material = material; }
	void SetCubeMap(CubeMap* map) { m_CubeMap = map; }

	Material GetMaterial() { return m_Material; }
	CubeMap* GetCubeMap() { return m_CubeMap; }
};

#endif // !_CUBE_H_



