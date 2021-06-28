#include "pch.h"
#include "Management.h"


//添加数据
void Management::add(Student stu) {

	if (size >= capacity) {
		//如果当前数组存满了
		capacity += INCREASE_SIZE;
		Student* temp = new Student[capacity]; //重新创建一个容量更大的数组
		for (int i = 0; i < size; i++) {
			temp[i] = all[i]; //把旧数组的数据迁移到新数组
		}
		delete[] all; //把旧数组的空间释放掉
		all = temp; //让all指针指向新数组
	}
	all[size++] = stu; //插入数据
}

//删除数据
bool Management::del(CString id) {
	for (int i = 0; i < size; i++) {
		//寻找指定id
		if (id == all[i].m_id) {
			//让后面的元素往前移，填补中间被删除后空缺的位置
			for (int j = i; j < size - 1; ++j) {
				all[j] = all[j + 1];
			}
			--size;
			return true;
		}
	}
	//如果找不到指定的id，删除失败
	return false;
}

//判断是否存在指定的id
bool Management::hasId(CString id) {
	for (int i = 0; i < size; i++) {
		if (id == all[i].m_id)
			return true;
	}
	return false;
}


//按照程序课成绩排序（false：降序，true：升序，采用默认参数，默认降序）
void Management::sortByScore1(bool tag) {
	//采用冒泡排序算法
	if (tag) {
		//升序
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
		//降序
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].score1 < all[j + 1].score1) {//和上面的不同是这里< ,上面 >
					Student temp = all[j];
					all[j] = all[j + 1];
					all[j + 1] = temp;
				}
			}
		}
	}

}

//按照高数课成绩排序（false：降序，true：升序，默认降序）
void Management::sortByScore2(bool tag) {
	//采用冒泡排序算法（代码和上面的函数一样，只是把score1改成score2而已）
	if (tag) {
		//升序
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
		//降序
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].score2 < all[j + 1].score2) {//和上面的不同是这里< ,上面 >
					Student temp = all[j];
					all[j] = all[j + 1];
					all[j + 1] = temp;
				}
			}
		}
	}
}

//按学号排序（false：降序，true：升序，默认降序）
void Management::sortById(bool tag)
{
	//采用冒泡排序算法（代码和按程序课排序的函数一样，只是把score1改成m_id而已）
	if (tag) {
		//升序
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
		//降序
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - i - 1; ++j) {
				if (all[j].m_id < all[j + 1].m_id) {//和上面的不同是这里< ,上面 >
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

//获取程序课成绩
int Management::getS1(CString id) {
	for (int i = 0; i < size; i++) {
		if (id == all[i].m_id)

			return all[i].score1;
	}
	return 0;
}

//获取高数课成绩
int Management::getS2(CString id) {
	for (int i = 0; i < size; i++) {
		if (id == all[i].m_id)

			return all[i].score2;
	}
	return 0;
}

//修改信息（学号不存在返回false）
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



//构造函数
Management::Management() {
	all = new Student[INIT_SIZE]; //初始化数组
	capacity = INIT_SIZE; //更新容量
	//读取文件
	ifstream ifs("data.txt", ios::in);
	if (ifs.is_open() && ifs.peek() != EOF) {
		//确保文件已经打开，并且不是空

		while (ifs.peek() != EOF) {
			//一直读到结尾为止
			string name, id;
			int score1, score2;
			ifs >> name >> id >> score1 >> score2; //逐个读取数据
			CString m_name(name.c_str());
			CString m_id(id.c_str());
			Student stu(m_name, m_id, score1, score2); //新建一个Student
			add(stu); //将Student添加到数组
		}
	}
	ifs.close(); //释放资源
}

//析构
Management::~Management() {
	//保存文件
	ofstream ofs("data.txt", ios::out);
	if (ofs.is_open()) {
		for (int i = 0; i < size; i++) {
			Student stu = all[i];
			string name(CT2A(all[i].m_name.GetBuffer())); //将CString转为string
			string id(CT2A(all[i].m_id.GetBuffer()));

			ofs << name << " " << id << " " << stu.score1 << " " << stu.score2;
			if (i != size - 1) ofs << endl;
			//最后一个数据之后不要换行，否则下次读取的时候会读取多一条空数据
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
