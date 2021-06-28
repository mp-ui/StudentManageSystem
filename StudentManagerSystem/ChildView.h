
// ChildView.h: CChildView 类的接口
//


#pragma once
#include "ADD.h"
#include "Management.h"
#include<vector>
using namespace std;


// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();
	ADD add;

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void DrawBar(CDC *dc, std::vector<int> db,bool left = true) const;
	void DrawLine(CDC *dc, std::vector<int> db,bool left = true) const;
	void OnDraw(CDC* pDC);
};

