
#ifndef _OBJ_INFO_H_
#define _OBJ_INFO_H_

#pragma once

#include"Angel.h"
#include<vector>

class FaceNode {
public:
	int PositionIndex;
	int NormalIndex;
	int TextureCoordinateIndex;
	
	FaceNode() {
		PositionIndex = NormalIndex = TextureCoordinateIndex = -1;
	}
	FaceNode(int posIndex, int normalIndex, int textureCoordinateIndex) {
		PositionIndex = PositionIndex;
		NormalIndex = normalIndex;
		TextureCoordinateIndex = textureCoordinateIndex;
	}
};

class FaceIndex {
public:
	FaceNode* a;
	FaceNode* b;
	FaceNode* c;

	FaceIndex(FaceNode* aa, FaceNode* bb, FaceNode* cc) {
		a = aa;
		b = bb;
		c = cc;
	}
	~FaceIndex() {
		delete a;
		delete b;
		delete c;
	}
};


class ObjMesh {
public:
	std::string FilePath;							// �ļ�·��������IDֵ

	std::vector<vec3> VerticesPosition;				// ������������
	std::vector<vec3> VerticesNormal;				// ���㷨��������
	std::vector<vec3> TextureCoordinate;			// ������������
	std::vector<FaceIndex*> Faces;					// ��Ƭ����

	ObjMesh() {
	}
	~ObjMesh() {
	}

	int GetVertexNum() { return VerticesPosition.size(); }
	int GetFaceNum() { return Faces.size(); }

	void Clear() {
		VerticesPosition.clear();
		VerticesNormal.clear();
		TextureCoordinate.clear();
		Faces.clear();
	}
};

#endif // !_OBJ_INFO_H_


