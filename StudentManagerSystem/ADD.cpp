// ADD.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagerSystem.h"
#include "afxdialogex.h"
#include "ADD.h"
#include "ChildView.h"
#include<ctime>
#include <vector>


Management m; //创建Management对象

// ADD 对话框

IMPLEMENT_DYNAMIC(ADD, CDialogEx)

ADD::ADD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ADD_STUDENT, pParent)
	  , m_name(_T(""))
	  , m_id(_T(""))
	  , score1(60)
	  , score2(60), Search_Score1_Min(0)
	  , Search_Score1_Max(100)
	  , Search_Score2_Min(0)
	  , Search_Score2_Max(100)
	  , Search_Name(_T(""))
	  , Search_Id(_T("")) {
}

ADD::~ADD() = default;


void ADD::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_id);
	DDX_Text(pDX, IDC_EDIT3, score1);
	DDX_Text(pDX, IDC_EDIT4, score2);

	DDX_Control(pDX, IDC_LIST1, DATA);
	DDX_Text(pDX, IDC_EDIT7, Search_Score1_Min);
	DDX_Text(pDX, IDC_EDIT8, Search_Score1_Max);
	DDX_Text(pDX, IDC_EDIT9, Search_Score2_Min);
	DDX_Text(pDX, IDC_EDIT10, Search_Score2_Max);
	DDX_Text(pDX, IDC_EDIT5, Search_Name);
	DDX_Text(pDX, IDC_EDIT6, Search_Id);
}


BEGIN_MESSAGE_MAP(ADD, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ADD::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &ADD::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &ADD::OnBnClickedButton2)
	ON_LBN_SELCHANGE(IDC_LIST1, &ADD::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON3, &ADD::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ADD::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &ADD::OnBnClickedButton5)
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_BUTTON7, &ADD::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &ADD::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &ADD::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &ADD::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &ADD::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &ADD::OnBnClickedButton12)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON13, &ADD::OnBnClickedButton13)
END_MESSAGE_MAP()


// ADD 消息处理程序

// 添加按钮
void ADD::OnBnClickedButton1() {

	//判断输入的内容是否为空
	//我这样做的原因是：如果先UpdateData，那数字输入框如果为空，会弹窗
	CString cstr1;
	CString cstr2;
	CString cstr3;
	CString cstr4;
	GetDlgItem(IDC_EDIT1)->GetWindowText(cstr1);
	GetDlgItem(IDC_EDIT2)->GetWindowText(cstr2);
	GetDlgItem(IDC_EDIT3)->GetWindowText(cstr3);
	GetDlgItem(IDC_EDIT4)->GetWindowText(cstr4);
	if (cstr1 == _T("") || cstr2 == _T("") || cstr3 == _T("") || cstr4 == _T("")) {
		MessageBox(TEXT("输入的内容不能为空！"));
		return;
	}
	//==================================================================
	UpdateData(TRUE); //将控件中的数据更新到变量
	//==================================================================
	//判断输入的内容是否包含空格
	int a = m_name.Find(TEXT(" ")); //m_name空格所在的索引
	int b = m_id.Find(TEXT(" ")); //查找空格所在的索引
	if (a != -1 || b != -1) {
		//如果索引不是-1，代表输入的东西一定包含空格
		MessageBox(TEXT("输入的内容请不要包含空格！"));
		return;
	}

	//==================================================================
	//判断学号是否全为数字，并且长度为10
	if (m_id.GetLength() == 10) {
		//如果长度为10，再判断是否每一位都是数字
		for (int i = 0; i < 10; ++i) {
			if (!(m_id.GetAt(i) >= '0' && m_id.GetAt(i) <= '9')) {
				//只要碰到一个字符不是数字，添加失败
				MessageBox(TEXT("学号必须由数字组成"));
				return;
			}
		}
	}
	else {
		//如果长度不为10，添加失败
		MessageBox(TEXT("学号的长度必须为10"));
		return;
	}
	//==================================================================
	//判断成绩是否符合范围
	if (score1 < 0 || score1 > 100 || score2 < 0 || score2 > 100) {
		MessageBox(TEXT("分数必须在0到100分之间"));
		return;
	}
	//==================================================================
	//判断要添加的学号是否存在
	if (m.hasId(m_id)) {
		MessageBox(TEXT("该学号已重复"));
		return;
	}
	//==================================================================
	//以上条件都满足后，添加成功
	Student stu(m_name, m_id, score1, score2);
	m.add(stu);
	DATA.AddString(m_id + "==" + m_name); //让ListBox添加一条数据
	MessageBox(TEXT("添加成功"));
	DATA.SetCurSel(DATA.GetCount() - 1); //添加之后让ListBox选中刚刚添加的数据
	OnLbnSelchangeList1(); //手动触发ListBox的Change事件

}


// 删除按钮
void ADD::OnBnClickedButton2() {

	CString id;
	int i = DATA.GetCurSel(); //获取ListBox正在选中的索引
	if (i != -1) {

		DATA.GetText(i, id);
		const int index = id.Find(_T("==")); //‘==’在字符串里的位置
		id = id.Mid(0, index); //列表里显示的格式为 学号==姓名，读取==前面的，就是学号
		if (m.del(id) /*删除数据，如果学号不存在将返回false*/) {
			DATA.DeleteString(i); //列表删除对应的项
			MessageBox(TEXT("删除成功"));
			DATA.SetCurSel(i == 0 ? 0 : i - 1); //手动让ListBox选中被删除的前面一项
			OnLbnSelchangeList1(); //手动触发ListBox的Change事件
		}
		else {
			MessageBox(TEXT("该学号不存在！可能是由于数据未更新所致，请刷新列表！"));
		}
	}
	else {
		//-1代表没选中
		MessageBox(TEXT("当前没有选中任何学生，请先在左边列表中选择！"));
	}

}

/**
 * ListBox的Change事件
 * 功能：当列表框选中某些项的时候，右边显示这个学生的信息
 */
void ADD::OnLbnSelchangeList1() {
	// TODO: 在此添加控件通知处理程序代码
	int i = DATA.GetCurSel(); //获取当前ListBox选中的索引
	if (i != -1) {
		CString id;
		DATA.GetText(i, id);
		i = id.Find(_T("=="));
		id = id.Mid(0, i); //列表里显示的格式为 学号==姓名，读取==前面的，就是学号
		if (m.hasId(id)) {
			m_name = m.getName(id);
			m_id = id;
			score1 = m.getS1(id);
			score2 = m.getS2(id);
			UpdateData(FALSE); //将变量的值同步到控件
		}
		else {
			MessageBox(TEXT("该学号不存在！可能是由于数据未更新所致，请刷新列表！"));
		}
	}
}


//编辑按钮
void ADD::OnBnClickedButton3() {
	//获取ListBox当前选中的内容，以获取学号信息
	CString id; //学号
	int i = DATA.GetCurSel(); //当前列表框选中的索引
	if (i == -1) {
		MessageBox(TEXT("当前没有选中任何学生，请先在左边列表中选择！"));
		return;
	}
	DATA.GetText(i, id);
	const int index = id.Find(_T("==")); //‘==’在字符串里的位置
	id = id.Mid(0, index); //列表里显示的格式为 学号==姓名，读取==前面的，就是学号
	//==================================================================
	//检查空格和学号格式是否正确，这部分和添加数据里面的代码是一样的。
	//==================================================================
	//判断输入的内容是否为空
	//我这样做的原因是：如果先UpdateData，那数字输入框如果为空，会弹窗
	CString cstr1;
	CString cstr2;
	CString cstr3;
	CString cstr4;
	GetDlgItem(IDC_EDIT1)->GetWindowText(cstr1);
	GetDlgItem(IDC_EDIT2)->GetWindowText(cstr2);
	GetDlgItem(IDC_EDIT3)->GetWindowText(cstr3);
	GetDlgItem(IDC_EDIT4)->GetWindowText(cstr4);
	if (cstr1 == _T("") || cstr2 == _T("") || cstr3 == _T("") || cstr4 == _T("")) {
		MessageBox(TEXT("输入的内容不能为空！"));
		return;
	}
	//==================================================================
	UpdateData(TRUE); //将控件中的数据更新到变量
	//==================================================================
	//判断输入的内容是否包含空格
	int a = m_name.Find(TEXT(" ")); //m_name空格所在的索引
	int b = m_id.Find(TEXT(" ")); //查找空格所在的索引
	if (a != -1 || b != -1) {
		//如果索引不是-1，代表输入的东西一定包含空格
		MessageBox(TEXT("输入的内容请不要包含空格！"));
		return;
	}

	//==================================================================
	//判断学号是否全为数字，并且长度为10
	if (m_id.GetLength() == 10) {
		//如果长度为10，再判断是否每一位都是数字
		for (int i = 0; i < 10; ++i) {
			if (!(m_id.GetAt(i) >= '0' && m_id.GetAt(i) <= '9')) {
				//只要碰到一个字符不是数字，添加失败
				MessageBox(TEXT("学号必须由数字组成"));
				return;
			}
		}
	}
	else {
		//如果长度不为10，添加失败
		MessageBox(TEXT("学号的长度必须为10"));
		return;
	}
	//==================================================================
	//判断成绩是否符合范围
	if (score1 < 0 || score1 > 100 || score2 < 0 || score2 > 100) {
		MessageBox(TEXT("分数必须在0到100分之间"));
		return;
	}
	//==================================================================
	//判断是否需要修改学号
	//不需要：m_id和当前的学号一致，不作修改
	//需要：m_id和当前的学号不一致，下一步还需判断修改后的学号是否重复
	if (m_id != id && m.hasId(m_id)) {
		//如果m_id != id，代表希望修改学号，但是修改学号需要判断学号有没有重复
		MessageBox(TEXT("该学号已重复"));
		return;
	}
	//===================================================================
	//以上条件都满足之后，
	//1.原来的学号存在：修改成功
	//2.原来的学号不存在：修改失败
	if (m.changeData(id, m_name, m_id, score1, score2)) {
		//修改数据，如果学号不存在将返回false

		OnBnClickedButton6(); //手动触发“刷新列表”的单击事件
		MessageBox(TEXT("修改成功"));

		//刷新列表之后，ListBox又会变为不选中状态
		//自动选回刚刚选中的那个
		for (int j = 0; j < DATA.GetCount(); j++) {
			CString cs;
			DATA.GetText(j, cs);
			if (cs.Mid(0, cs.Find(_T("=="))) == m_id) {
				DATA.SetCurSel(j);
				break;
			}
		}
	}
	else {
		MessageBox(TEXT("该学号不存在！可能是由于数据未更新所致，请刷新列表！"));
	}

}


//按程序课降序按钮
void ADD::OnBnClickedButton4() {

	m.sortByScore1(); //排序
	CString id;
	int i = DATA.GetCurSel(); //记住排序之前选中的索引
	OnBnClickedButton6(); //刷新列表
	//刷新列表之后，ListBox又会变为不选中状态
	//需要自动选回刚刚选中的那个（如果i==-1，代表原来并没有选择）
	if (i != -1) {
		DATA.GetText(i, id);
		for (int j = 0; j < DATA.GetCount(); j++) {
			CString cs;
			DATA.GetText(j, cs);
			if (cs.Mid(0, cs.Find(_T("=="))) == m_id) {
				DATA.SetCurSel(j);
				break;
			}
		}
	}
	OnLbnSelchangeList1(); //触发ListBox的事件，让右边能显示选中的学生的个人信息
}

//按高数课降序按钮（这部分代码和按程序课降序的一样，唯一不同的地方是第一行的排序函数不同）
void ADD::OnBnClickedButton5() {
	m.sortByScore2();
	CString id;
	int i = DATA.GetCurSel();
	OnBnClickedButton6();
	if (i != -1) {
		DATA.GetText(i, id);
		for (int j = 0; j < DATA.GetCount(); j++) {
			CString cs;
			DATA.GetText(j, cs);
			if (cs.Mid(0, cs.Find(_T("=="))) == m_id) {
				DATA.SetCurSel(j);
				break;
			}
		}
	}
	OnLbnSelchangeList1();
}

//刷新列表按钮
void ADD::OnBnClickedButton6() {
	DATA.ResetContent(); //清空列表
	for (int i = 0; i < m.size; i++) {
		CString str;
		str = m.all[i].m_id;
		str += "==";
		str += m.all[i].m_name;
		DATA.AddString(str); //读取数组，逐个插入数据
	}
}

//窗口激活消息（显示窗口后刷新列表）
void ADD::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
	srand((unsigned long)time(NULL)); //随机数种子
	OnBnClickedButton6();
}


//按程序课升序（这部分代码和降序的一样，唯一不同的地方是第一行的排序函数给了true参数）
void ADD::OnBnClickedButton7() {
	m.sortByScore1(true); //排序
	CString id;
	int i = DATA.GetCurSel(); //记住排序之前选中的索引
	OnBnClickedButton6(); //刷新列表
	//刷新列表之后，ListBox又会变为不选中状态
	//自动选回刚刚选中的那个（如果i==-1，代表原来并没有选择）
	if (i != -1) {
		DATA.GetText(i, id);
		for (int j = 0; j < DATA.GetCount(); j++) {
			CString cs;
			DATA.GetText(j, cs);
			if (cs.Mid(0, cs.Find(_T("=="))) == m_id) {
				DATA.SetCurSel(j);
				break;
			}
		}
	}
	OnLbnSelchangeList1(); //触发ListBox的事件，让右边能显示选中的学生的个人信息
}


//按高数课降序（这部分代码和降序的一样，唯一不同的地方是第一行的排序函数给了true参数）
void ADD::OnBnClickedButton8() {
	m.sortByScore2(true);
	CString id;
	int i = DATA.GetCurSel();
	OnBnClickedButton6();
	if (i != -1) {
		DATA.GetText(i, id);
		for (int j = 0; j < DATA.GetCount(); j++) {
			CString cs;
			DATA.GetText(j, cs);
			if (cs.Mid(0, cs.Find(_T("=="))) == m_id) {
				DATA.SetCurSel(j);
				break;
			}
		}
	}
	OnLbnSelchangeList1();
}


//按学号降序（和上面的排序是一样的）
void ADD::OnBnClickedButton9() {
	m.sortById(); //排序
	CString id;
	int i = DATA.GetCurSel(); //记住排序之前选中的索引
	OnBnClickedButton6(); //刷新列表
	//刷新列表之后，ListBox又会变为不选中状态
	//自动选回刚刚选中的那个（如果i==-1，代表原来并没有选择）
	if (i != -1) {
		DATA.GetText(i, id);
		for (int j = 0; j < DATA.GetCount(); j++) {
			CString cs;
			DATA.GetText(j, cs);
			if (cs.Mid(0, cs.Find(_T("=="))) == m_id) {
				DATA.SetCurSel(j);
				break;
			}
		}
	}
	OnLbnSelchangeList1(); //触发ListBox的事件，让右边能显示选中的学生的个人信息
}

//按学号升序
void ADD::OnBnClickedButton10() {
	m.sortById(true); //排序
	CString id;
	int i = DATA.GetCurSel(); //记住排序之前选中的索引
	OnBnClickedButton6(); //刷新列表
	//刷新列表之后，ListBox又会变为不选中状态
	//自动选回刚刚选中的那个（如果i==-1，代表原来并没有选择）
	if (i != -1) {
		DATA.GetText(i, id);
		for (int j = 0; j < DATA.GetCount(); j++) {
			CString cs;
			DATA.GetText(j, cs);
			if (cs.Mid(0, cs.Find(_T("=="))) == m_id) {
				DATA.SetCurSel(j);
				break;
			}
		}
	}
	OnLbnSelchangeList1(); //触发ListBox的事件，让右边能显示选中的学生的个人信息
}

//面向对象分数随机
void ADD::OnBnClickedButton11() {
	UpdateData(TRUE);
	score1 = rand() % 101; //0-100之间的随机数
	UpdateData(FALSE); //数据更新到控件
}


//高数分数随机
void ADD::OnBnClickedButton12() {
	UpdateData(TRUE);
	score2 = rand() % 101; //0-100之间的随机数
	UpdateData(FALSE); //数据更新到控件
}


int ADD::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

//查询按钮
void ADD::OnBnClickedButton13() {
	//判断输入的成绩范围是不是为空的
	CString cstr1;
	CString cstr2;
	CString cstr3;
	CString cstr4;
	GetDlgItem(IDC_EDIT7)->GetWindowText(cstr1);
	GetDlgItem(IDC_EDIT8)->GetWindowText(cstr2);
	GetDlgItem(IDC_EDIT9)->GetWindowText(cstr3);
	GetDlgItem(IDC_EDIT10)->GetWindowText(cstr4);
	if (cstr1 == _T("") || cstr2 == _T("") || cstr3 == _T("") || cstr4 == _T("")) {
		MessageBox(TEXT("输入的成绩的范围不能为空！"));
		return;
	}
	//==============================================================
	UpdateData(TRUE);
	//进行数据的合法性判断
	if (Search_Score1_Max > 100 || Search_Score1_Max < 0 || Search_Score1_Min > 100 || Search_Score1_Min < 0 ||
		Search_Score2_Max > 100 || Search_Score2_Max < 0 || Search_Score2_Min > 100 || Search_Score2_Min < 0) {
		MessageBox(TEXT("输入的成绩的范围必须在区间[0,100]内！"));
		return;
	}
	if (Search_Score1_Min > Search_Score1_Max || Search_Score2_Min > Search_Score2_Max) {
		MessageBox(TEXT("输入的成绩最小值不能比最大值大！"));
		return;
	}
	//===============================================================
	//开始查询
	std::vector<Student> result;
	for (int i = 0; i < m.size; ++i) {
		Student stu = m.all[i];
		if (stu.m_name.Find(Search_Name) != -1 &&
			stu.m_id.Find(Search_Id) != -1 &&
			stu.score1 >= Search_Score1_Min &&
			stu.score1 <= Search_Score1_Max &&
			stu.score2 >= Search_Score2_Min &&
			stu.score2 <= Search_Score2_Max) {
			//满足条件
			result.push_back(stu);
		}
	}
	CString str;
	for (auto stu : result) {
		CString cScore1;
		CString cScore2;
		cScore1.Format(_T("%d"), stu.score1);
		cScore2.Format(_T("%d"), stu.score2);
		str += _T("学生姓名：") + stu.m_name + _T("\t学号：") + stu.m_id + _T("\t程序课成绩：") + cScore1 + _T("\t高数课成绩：") + cScore2 + _T("\n");
	}
	CString cLength;
	cLength.Format(_T("%d"), result.size());
	MessageBox(str,_T("共查询到") + cLength + _T("条结果"));
}
