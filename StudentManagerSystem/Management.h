#pragma once
#include<fstream>
#include "Student.h"
#include <string>
#include "ADD.h"
#include <vector>
using namespace std;
constexpr auto INIT_SIZE = 10;	//默认大小是10个;
constexpr auto INCREASE_SIZE = 10;	//数组满后扩充的容量;

class Management {
public:
	Student* all = NULL; //存放学生数据的数组,在构造函数中对其初始化
	int capacity = 0;   //数组当前容量
	int size = 0;       //当前大小
	//--------------------------------------------------------
	//基本功能
	void add(Student stu);    //添加数据
	bool del(CString id);     //根据ID删除数据
	bool hasId(CString id);   //判断id是否存在
	void sortByScore1(bool = false);      //按程序课成绩排序（false：降序，true：升序，采用了默认参数，默认降序）
	void sortByScore2(bool = false);      //按高数课成绩排序（false：降序，true：升序，默认降序）
	void sortById(bool = false);		//按学号排序（false：降序，true：升序，默认降序）
	//---------------------------------------------------------
	//根据id获取名字、分数
	CString getName(CString id);
	int getS1(CString id);	//获取程序课成绩
	int getS2(CString id);    //获取高数课成绩
	//---------------------------------------------------------
	//根据id来修改信息
	bool changeData(CString oldId, CString newName, CString newId, int S1, int S2) const;
	//---------------------------------------------------------
	//构造和析构函数
	Management();
	~Management();
	//--------------------------------------------------------
	//获取高数和程序课的vector集合（用于画统计图）
	vector<int> getMathScores() const;
	vector<int> getProgrammingScores() const;
};

