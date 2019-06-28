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
		std::cout << "ERROR::Tools::ReadOFF::�ļ�������Ϊ�գ�" << std::endl;
		return;
	}

	if (mesh == nullptr) {
		std::cout << "ERROR::Tools::ReadOFF::Mesh���ܴ��ݿղ�����" << std::endl;
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
	std::getline(fin, line);					// ��ȡ��һ���ַ��� OFF
	fin >> vertexNum >> faceNum >> edgeNum;		// ��ȡ�����������Ƭ�������߸���

	mesh->m_VertexNum = vertexNum;
	mesh->m_FaceNum = faceNum;
	mesh->m_EdgeNum = edgeNum;
	for (unsigned int i = 0; i < vertexNum; i++) {
		std::getline(fin, line);
		fin >> x >> y >> z;						// ��ȡ������Ϣ
		mesh->m_vertices.push_back(vec3(x, y, z));
	}
	for (unsigned int i = 0; i < faceNum; i++) {
		std::getline(fin, line);
		fin >> number >> ia >> ib >> ic;		// ��ȡ����������Ϣ
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
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(folderPath).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
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
