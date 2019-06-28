
#ifndef _PLANE_H_
#define _PLANE_H_
#pragma once

#include"Node.h"
#include<Texture_GLUT.h>
#include"Material.h"

class Plane :public Node
{
private:
	Texture * m_Texture;				// 利用这个Texture进行绘制
	Material m_Material;				// 材质信息
	bool m_IsLighted;					// 是否需要光照烘焙
	bool m_IsAnimator;					// 是否为动画机
protected:
	Plane();

	virtual bool Init()override;
	virtual bool Render()override;
public:
	~Plane();
	static Plane* Create();

	void SetIsAnimator(bool flag) { m_IsAnimator = flag; }
	bool IsAnimator() { return m_IsAnimator; }

	void SetIsLighted(bool flag) { m_IsLighted = flag; }
	bool IsLighted() { return m_IsLighted; }

	void SetMaterial(Material material) { m_Material = material; }
	Material GetMaterial() { return m_Material; }

	void SetTexture(Texture* texture);
	Texture* GetTexture() { return m_Texture; }
};



#endif // !_PLANE_H_


