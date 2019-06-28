#include "stdafx.h"
#include "Tools.h"

#include<fstream>
#include<io.h>

Tools* Tools::m_Instance = new Tools();

Tools::Tools()
{
	gen = new std::mt19937(rd());
}


Tools::~Tools()
{
}

void Tools::ReadOFF(std::string filePath, OFFMesh * mesh)
{
	if (filePath.empty()) {
		std::cout << "ERROR::Tools::ReadOFF::文件名不能为空！" << std::endl;
		return;
	}

	if (mesh == nullptr) {
		std::cout << "ERROR::Tools::ReadOFF::Mesh不能传递空参数！" << std::endl;
		return;
	}

	mesh->m_faces.clear();
	mesh->m_vertices.clear();

	std::ifstream fin;
	std::string line;
	GLuint vertexNum, faceNum, edgeNum;
	GLdouble x, y, z;
	GLuint number, ia, ib, ic;

	fin.open(filePath);
	std::getline(fin, line);					// 读取第一行字符换 OFF
	fin >> vertexNum >> faceNum >> edgeNum;		// 读取顶点个数、面片个数、边个数

	mesh->m_VertexNum = vertexNum;
	mesh->m_FaceNum = faceNum;
	mesh->m_EdgeNum = edgeNum;
	for (unsigned int i = 0; i < vertexNum; i++) {
		std::getline(fin, line);
		fin >> x >> y >> z;						// 读取顶点信息
		mesh->m_vertices.push_back(vec3(x, y, z));
	}
	for (unsigned int i = 0; i < faceNum; i++) {
		std::getline(fin, line);
		fin >> number >> ia >> ib >> ic;		// 读取顶点索引信息
		mesh->m_faces.push_back(vec3i(ia, ib, ic));
	}
	fin.close();
}

std::vector<std::string> Tools::GetFileNameInFolder(std::string folderPath)
{
	std::vector<std::string> fileNames;
	GetFileNameInFolder(folderPath, fileNames);
	return fileNames;
}

void Tools::GetFileNameInFolder(std::string folderPath, std::vector<std::string>& dest)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(folderPath).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					GetFileNameInFolder(p.assign(folderPath).append("\\").append(fileinfo.name), dest);
			}
			else
			{
				dest.push_back(p.assign(folderPath).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

double Tools::_Random(double min, double max)
{
	std::uniform_real_distribution<> dis(min, max);
	return dis(*gen);
}
