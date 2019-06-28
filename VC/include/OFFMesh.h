

#ifndef _OFF_MESH_H_
#define _OFF_MESH_H_

#pragma once

#include<Angel.h>
#include<vector>

typedef struct vIndex {
	unsigned int a, b, c;
	vIndex(int ia, int ib, int ic) :a(ia), b(ib), c(ic) {}
} vec3i;

class OFFMesh {
public:
	int m_VertexNum;						// 顶点个数
	int m_FaceNum;							// 面片个数
	int m_EdgeNum;							// 边个数

	std::vector<vec3> m_vertices;			// 顶点数组
	std::vector<vec3i> m_faces;		// 面片上点的索引值
};


#endif // !_OFF_MESH_H_


