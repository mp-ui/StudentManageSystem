#include "pch.h"
#include "Management.h"


//�������
void Management::add(Student stu) {

	if (size >= capacity) {
		//�����ǰ���������
		capacity += INCREASE_SIZE;
		Student* temp = new Student[capacity]; //���´���һ���������������
		for (int i = 0; i < size; i++) {
			temp[i] = all[i]; //�Ѿ����������Ǩ�Ƶ�������
		}
		delete[] all; //�Ѿ�����Ŀռ��ͷŵ�
		all = temp; //��allָ��ָ��������
	}
	all[size++] = stu; //��������
}

//ɾ������
bool Management::del(CString id) {
	for (int i = 0; i < size; i++) {
		//Ѱ��ָ��id
		if (id == all[i].m_id) {
			//�ú����Ԫ����ǰ�ƣ���м䱻ɾ�����ȱ��λ��
			for (int j = i; j < size - 1; ++j) {
				all[j] = all[j + 1];
			}
			--size;
			return true;
		}
	}
	//����Ҳ���ָ����id��ɾ��ʧ��
	return false;
}

//�ж��Ƿ����ָ����id
bool Management::hasId(CString id) {
	for (int i = 0; i < size; i++) {
		if (id == all[i].m_id)
			return true;
	}
	return false;
}


//���ճ���γɼ�����false������true�����򣬲���Ĭ�ϲ�����Ĭ�Ͻ���
void Management::sortByScore1(bool tag) {
	//����ð�������㷨
	if (tag) {
		//����
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].score1 > all[j + 1].score1) {
					Student temp = all[j];
					all[j] = all[j + 1];
					all[j + 1] = temp;
				}
			}
		}
	}else {
		//����
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].score1 < all[j + 1].score1) {//������Ĳ�ͬ������< ,���� >
					Student temp = all[j];
					all[j] = all[j + 1];
					all[j + 1] = temp;
				}
			}
		}
	}

}

//���ո����γɼ�����false������true������Ĭ�Ͻ���
void Management::sortByScore2(bool tag) {
	//����ð�������㷨�����������ĺ���һ����ֻ�ǰ�score1�ĳ�score2���ѣ�
	if (tag) {
		//����
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].score2 > all[j + 1].score2) {
					Student temp = all[j];
					all[j] = all[j + 1];
					all[j + 1] = temp;
				}
			}
		}
	}
	else {
		//����
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].score2 < all[j + 1].score2) {//������Ĳ�ͬ������< ,���� >
					Student temp = all[j];
					all[j] = all[j + 1];
					all[j + 1] = temp;
				}
			}
		}
	}
}

//��ѧ������false������true������Ĭ�Ͻ���
void Management::sortById(bool tag)
{
	//����ð�������㷨������Ͱ����������ĺ���һ����ֻ�ǰ�score1�ĳ�m_id���ѣ�
	if (tag) {
		//����
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].m_id > all[j + 1].m_id) {
					Student temp = all[j];
					all[j] = all[j + 1];
					all[j + 1] = temp;
				}
			}
		}
	}
	else {
		//����
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].m_id < all[j + 1].m_id) {//������Ĳ�ͬ������< ,���� >
					Student temp = all[j];
					all[j] = all[j + 1];
					all[j + 1] = temp;
				}
			}
		}
	}
}


CString Management::getName(CString id) {
	for (int i = 0; i < size; i++) {
		if (id == all[i].m_id)

			return all[i].m_name;
	}
	return TEXT("");
}

//��ȡ����γɼ�
int Management::getS1(CString id) {
	for (int i = 0; i < size; i++) {
		if (id == all[i].m_id)

			return all[i].score1;
	}
	return 0;
}

//��ȡ�����γɼ�
int Management::getS2(CString id) {
	for (int i = 0; i < size; i++) {
		if (id == all[i].m_id)

			return all[i].score2;
	}
	return 0;
}

//�޸���Ϣ��ѧ�Ų����ڷ���false��
bool Management::changeData(CString oldId, CString newName, CString newId, int S1, int S2) const {
	for (int i = 0; i < size; i++) {
		if (oldId == all[i].m_id) {
			all[i].m_name = newName;
			all[i].m_id = newId;
			all[i].score1 = S1;
			all[i].score2 = S2;
			return true;
		}
	}
	return false;
}



//���캯��
Management::Management() {
	all = new Student[INIT_SIZE]; //��ʼ������
	capacity = INIT_SIZE; //��������
	//��ȡ�ļ�
	ifstream ifs("data.txt", ios::in);
	if (ifs.is_open() && ifs.peek() != EOF) {
		//ȷ���ļ��Ѿ��򿪣����Ҳ��ǿ�

		while (ifs.peek() != EOF) {
			//һֱ������βΪֹ
			string name, id;
			int score1, score2;
			ifs >> name >> id >> score1 >> score2; //�����ȡ����
			CString m_name(name.c_str());
			CString m_id(id.c_str());
			Student stu(m_name, m_id, score1, score2); //�½�һ��Student
			add(stu); //��Student��ӵ�����
		}
	}
	ifs.close(); //�ͷ���Դ
}

//����
Management::~Management() {
	//�����ļ�
	ofstream ofs("data.txt", ios::out);
	if (ofs.is_open()) {
		for (int i = 0; i < size; i++) {
			Student stu = all[i];
			string name(CT2A(all[i].m_name.GetBuffer())); //��CStringתΪstring
			string id(CT2A(all[i].m_id.GetBuffer()));

			ofs << name << " " << id << " " << stu.score1 << " " << stu.score2;
			if (i != size - 1) ofs << endl;
			//���һ������֮��Ҫ���У������´ζ�ȡ��ʱ����ȡ��һ��������
		}

	}
	ofs.close();
	delete[] all;
}


vector<int> Management::getMathScores() const {
	vector<int> datas;
	for (int i = 0; i < size; i++) {
		datas.push_back(all[i].score2);
	}
	return datas;
}


vector<int> Management::getProgrammingScores() const {
	vector<int> datas;
	for (int i = 0; i < size; i++) {
		datas.push_back(all[i].score1);
	}
	return datas;
}
