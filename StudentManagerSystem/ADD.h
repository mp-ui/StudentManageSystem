#pragma once
// ADD 对话框

class ADD : public CDialogEx
{
	DECLARE_DYNAMIC(ADD)

public:
	ADD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ADD();
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ADD_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	CString m_name;
	CString m_id;
	int score1;
	int score2;
	
	afx_msg void OnBnClickedButton1();
	CListBox DATA;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int Search_Score1_Min;
	int Search_Score1_Max;
	int Search_Score2_Min;
	int Search_Score2_Max;
	CString Search_Name;
	CString Search_Id;
	afx_msg void OnBnClickedButton13();
};
