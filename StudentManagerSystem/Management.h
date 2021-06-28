#pragma once
#include<fstream>
#include "Student.h"
#include <string>
#include "ADD.h"
#include <vector>
using namespace std;
constexpr auto INIT_SIZE = 10;	//Ĭ�ϴ�С��10��;
constexpr auto INCREASE_SIZE = 10;	//�����������������;

class Management {
public:
	Student* all = NULL; //���ѧ�����ݵ�����,�ڹ��캯���ж����ʼ��
	int capacity = 0;   //���鵱ǰ����
	int size = 0;       //��ǰ��С
	//--------------------------------------------------------
	//��������
	void add(Student stu);    //�������
	bool del(CString id);     //����IDɾ������
	bool hasId(CString id);   //�ж�id�Ƿ����
	void sortByScore1(bool = false);      //������γɼ�����false������true�����򣬲�����Ĭ�ϲ�����Ĭ�Ͻ���
	void sortByScore2(bool = false);      //�������γɼ�����false������true������Ĭ�Ͻ���
	void sortById(bool = false);		//��ѧ������false������true������Ĭ�Ͻ���
	//---------------------------------------------------------
	//����id��ȡ���֡�����
	CString getName(CString id);
	int getS1(CString id);	//��ȡ����γɼ�
	int getS2(CString id);    //��ȡ�����γɼ�
	//---------------------------------------------------------
	//����id���޸���Ϣ
	bool changeData(CString oldId, CString newName, CString newId, int S1, int S2) const;
	//---------------------------------------------------------
	//�������������
	Management();
	~Management();
	//--------------------------------------------------------
	//��ȡ�����ͳ���ε�vector���ϣ����ڻ�ͳ��ͼ��
	vector<int> getMathScores() const;
	vector<int> getProgrammingScores() const;
};

