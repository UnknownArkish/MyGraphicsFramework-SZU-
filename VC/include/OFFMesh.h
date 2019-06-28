

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
	int m_VertexNum;						// �������
	int m_FaceNum;							// ��Ƭ����
	int m_EdgeNum;							// �߸���

	std::vector<vec3> m_vertices;			// ��������
	std::vector<vec3i> m_faces;		// ��Ƭ�ϵ������ֵ
};


#endif // !_OFF_MESH_H_


