#pragma once

class Student {
public:	
	CString m_name;//����
	CString m_id;//ѧ��(Ψһ)
	int score1;//�����
	int score2;//������

	//ȫ�ι���
	Student(const CString& m_name, const CString& m_id, int score1, int score2);
	//Ĭ�Ϲ���
	Student();
};

