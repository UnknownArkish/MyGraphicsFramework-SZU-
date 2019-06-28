

#ifndef _TOOLS_H_
#define _TOOLS_H_
#pragma once

#include<OFFMesh.h>

#include<string>
#include<random>

#define Random(min,max){return Tools::GetInstance()->_Random(min,max);}
#define RandomWithinX(min,max,x){return Random(min,max)%x;}

/*
*	工具类，单例模式实现
*	提供一些常用的函数
*/
class Tools
{
private:
	static Tools* m_Instance;
	Tools();
	~Tools();
private:
	std::random_device rd;		// 种子
	std::mt19937* gen;
public:
	static Tools* GetInstance() { return m_Instance; }

	void ReadOFF(std::string filePath, OFFMesh* mesh);
	double _Random(double min = 0.0, double max = MAXDWORD64);

	std::vector<std::string> GetFileNameInFolder(std::string folderPath);
private:
	void GetFileNameInFolder(std::string folderPath, std::vector<std::string>& dest);
	//void Inverse(float* matrix);

};



#endif // !_TOOLS_H_

