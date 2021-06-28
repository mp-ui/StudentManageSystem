// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "ChildView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern Management m; //需要和ADD.cpp共用一个Management对象，所以这里要声明extern
// CChildView

CChildView::CChildView() {
}

CChildView::~CChildView() {
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DRAWITEM()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) {
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
	                                   ::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
	                                   nullptr);

	return TRUE;
}


void CChildView::OnPaint() {
	CPaintDC dc(this); // 用于绘制的设备上下文
	// TODO: 在此处添加消息处理程序代码
	// 不要为绘制消息而调用 CWnd::OnPaint()
	OnDraw(&dc);
}

//画条状图,db:vector类的集合，里面存放所有要统计的数据
void CChildView::DrawBar(CDC* dc, std::vector<int> db,bool left) const {//left：是否在左边
	CRect rc; //外面的矩形
	GetClientRect(rc); //获取CWnd客户区的尺寸。（让rc占满窗口）
	rc.DeflateRect(30, 15, 10, rc.Height() / 2+15); //x1,y1,x2,y2
	if(left) {
		//如果是左边，相应修改一下x2的值
		rc.right = rc.Width() / 2 - 15;
		dc->TextOutW(rc.left, 0, TEXT("高数课成绩统计"));
	}else {
		rc.left = rc.Width() / 2 + 15;
		dc->TextOutW(rc.left, 0, TEXT("程序课成绩统计"));
	}
	CBrush brush1(HS_BDIAGONAL, RGB(96, 192, 255)); //向下阴影(从左到右)在45度（右斜），蓝色
	CBrush brush2(HS_FDIAGONAL, RGB(96, 192, 255)); //向上阴影(从左到右)在45度（左斜），蓝色
	CPen pen(PS_INSIDEFRAME, 2, RGB(96, 192, 255)); //
	int n = 5; //定义有五个区间
	int width = rc.Width() / n; //一个区间的宽度

	int s[] = {0, 0, 0, 0, 0}; //各区间人数
	//统计各区间人数
	for (int i = 0; i < db.size(); i++) {
		if (db[i] < 60) s[0] ++;
		else if (db[i] >= 60 && db[i] < 70) s[1]++;
		else if (db[i] >= 70 && db[i] < 80) s[2]++;
		else if (db[i] >= 80 && db[i] < 90) s[3]++;
		else s[4]++;
	}

	//找出人数最大的区间
	int max_s = s[0];
	for (int i = 0; i < n; i++)
		if (max_s < s[i]) max_s = s[i];

	int per_Height = rc.Height() / max_s; //算出一个人代表的矩形高度

	CRect ps_rect(rc); //直方图的矩形
	ps_rect.right = ps_rect.left + width;

	dc->SelectObject(&pen); //选择画笔
	CString str[5] = {_T("<60"),_T("60-70"),_T("70-80"),_T("80-90"),_T(">=90")}; //将每个区间的注释先存储
	for (int i = 0; i < n; i++) {
		ps_rect.top = ps_rect.bottom - per_Height * s[i]; //该区间的高度
		if (i % 2) dc->SelectObject(&brush2);
		else dc->SelectObject(&brush1); //每隔一个区间用不同的斜线，左斜或右斜
		dc->Rectangle(ps_rect); //绘制矩形

		if (s[i] > 0) {
			CString str1;
			str1.Format(_T("%d人"), s[i]); //设置str1的内容
			dc->DrawText(str1, ps_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE); //在矩形中间显示人数
		}
		//输出注释在矩形下面
		dc->TextOutW((ps_rect.left + ps_rect.right) / 2 - 15, ps_rect.bottom+5 , str[i]);
		ps_rect.OffsetRect(width, 0); //移动矩形框的位置,水平方向移动width
	}

}

//折线图
void CChildView::DrawLine(CDC* dc, std::vector<int> db,bool left) const {
	CRect rc; //最外面的矩形
	GetClientRect(rc); //让矩形占满窗口
	rc.DeflateRect(30, rc.Height() / 2 + 15, 10, 15); ////x1,y1,x2,y2
	if (left) {
		//如果是左边，相应修改一下x2的值
		rc.right = rc.Width() / 2 - 15;
	}
	else {
		rc.left = rc.Width() / 2 + 15;
	}
	int gridXnums = db.size(); //列数
	int gridYnums = 10; //行数
	int dx = rc.Width() / gridXnums; //每一个格子的宽度
	int dy = rc.Height() / gridYnums; //每一个格子的高度


	CRect gridRect(rc.left, rc.top, rc.left + dx * gridXnums, rc.top + dy * gridYnums);

	CPen gridPen(PS_DASHDOTDOT, 1, RGB(96, 192, 255)); //获取蓝色的点状画笔
	dc->SelectObject(&gridPen); //选择画笔
	//-------------------------------------------------------------------
	//画格子
	for (int i = 0; i <= gridXnums; i++) {
		dc->MoveTo(gridRect.left + i * dx, gridRect.bottom);
		dc->LineTo(gridRect.left + i * dx, gridRect.top);
	}
	for (int j = 0; j <= gridYnums; j++) {
		dc->MoveTo(gridRect.left, gridRect.top + j * dy);
		dc->LineTo(gridRect.right, gridRect.top + j * dy);
		CString str;
		str.Format(_T("%d"), 100 - 10 * j);
		dc->TextOutW(rc.left - 25, gridRect.top + j * dy - 10, str); //标注纵坐标的值
	}
	//-------------------------------------------------------------------

	gridPen.Detach(); //官方解释：从CGdiObject对象分离Windows GDI对象，并将句柄返回给Windows GDI对象。
	//但是不加这一行会报异常

	CPen linePen(PS_SOLID, 2, RGB(255, 0, 0)); //创建一个红色实线画笔，用于画线
	dc->SelectObject(&linePen); //选择画笔

	int nCount = db.size(); //一共多少个数据
	int deta = gridRect.Width() / nCount; //每一个数据所占的宽度
	POINT* pt = new POINT[nCount];

	for (int i = 0; i < nCount; i++) {
		pt[i].x = gridRect.left + i * deta;
		pt[i].y = gridRect.bottom - (int)(db[i] / 100.0 * gridRect.Height());

		CString score;
		score.Format(_T("%d"), db[i]); //设置score的内容
		// dc->TextOutW(pt[i].x - 5, gridRect.bottom + 5, score); //显示分数(在下面)
	}
	dc->Polyline(pt, nCount); //画线
	delete[] pt;
	pt = nullptr;
}


void CChildView::OnDraw(CDC* pDC) {
	vector<int> programmingScores = m.getProgrammingScores();
	vector<int> mathScores = m.getMathScores();
	

	if (!mathScores.empty() && !programmingScores.empty()) {
		//只有数据不为空了才去画图
		DrawBar(pDC, mathScores,true); //左边条形图画高数
		DrawBar(pDC, programmingScores,false); //右边条形图画程序
		DrawLine(pDC, mathScores,true); //左边折线图画高数
		DrawLine(pDC, programmingScores,false); //右边折线图画程序
	}
}

//左
void CChildView::OnLButtonDown(UINT nFlags, CPoint point) {

	CWnd::OnLButtonDown(nFlags, point);

	//弹出对话框
	add.DoModal();

	//重绘统计图
	Invalidate(); // 重画窗口。
	OnPaint();


}


