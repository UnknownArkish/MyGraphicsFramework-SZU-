
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
	std::string FilePath;							// 文件路径，用作ID值

	std::vector<vec3> VerticesPosition;				// 顶点坐标数组
	std::vector<vec3> VerticesNormal;				// 顶点法向量数组
	std::vector<vec3> TextureCoordinate;			// 纹理坐标数组
	std::vector<FaceIndex*> Faces;					// 面片数组

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


