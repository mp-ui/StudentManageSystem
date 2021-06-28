#pragma once

class Student {
public:	
	CString m_name;//姓名
	CString m_id;//学号(唯一)
	int score1;//程序课
	int score2;//高数课

	//全参构造
	Student(const CString& m_name, const CString& m_id, int score1, int score2);
	//默认构造
	Student();
};

