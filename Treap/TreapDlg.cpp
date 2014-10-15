
// TreapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Treap.h"
#include "TreapDlg.h"
#include "TreapFunc.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTreapDlg 对话框



CTreapDlg::CTreapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTreapDlg::IDD, pParent)
	, m_value(0)
	, m_fix(0)
	, p(0)
	, m_key_del(0)
	, m_Max(0)
	, m_Min(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYPIC, m_pic);
	DDX_Text(pDX, IDC_EDIT_KEY, m_value);
	DDX_Text(pDX, IDC_EDIT_PRIORITY, m_fix);
	DDV_MinMaxInt(pDX, m_fix, 0, 100);
	DDX_Text(pDX, IDC_EDIT_DKEY, m_key_del);
	DDX_Control(pDX, IDC_EDIT_MAX, m_max);
	DDX_Control(pDX, IDC_EDIT_MIN, m_min);
	DDX_Text(pDX, IDC_EDIT_MAX, m_Max);
	DDX_Text(pDX, IDC_EDIT_MIN, m_Min);
}

BEGIN_MESSAGE_MAP(CTreapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTreapDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTreapDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CLEAR, &CTreapDlg::OnBnClickedClear)
END_MESSAGE_MAP()


// CTreapDlg 消息处理程序

BOOL CTreapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTreapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTreapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTreapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTreapDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Treap_Insert(p, m_value, m_fix);
	FindMaxMin(p);
	//m_Max = p->value;
	UpdateData(FALSE);

	CRect rectPicture;
	m_pic.GetClientRect(&rectPicture);

	CBrush newBrush;   // 用于创建新画刷   
	CBrush *pOldBrush; // 用于存放旧画刷

	// 创建黑色新画刷   
	newBrush.CreateSolidBrush(RGB(255,255,255));   
	// 选择新画刷，并将旧画刷的指针保存到pOldBrush   
	pOldBrush = m_pic.GetDC()->SelectObject(&newBrush);   
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景   
	m_pic.GetDC()->Rectangle(rectPicture);   
	// 恢复旧画刷   
	m_pic.GetDC()->SelectObject(pOldBrush);   
	// 删除新画刷   
	newBrush.DeleteObject(); 

	DrawTreap(m_pic.GetDC(), rectPicture, p);
}

void CTreapDlg::DrawTreap(CDC *pDC, CRect &rectPicture, Treap_Node * p){
	CPen newPen;       // 用于创建新画笔   
	CPen *pOldPen;     // 用于存放旧画笔  

	// 创建实心画笔，粗度为1，颜色为黑色   
	newPen.CreatePen(PS_SOLID, 1, RGB(0,0,0));   
	// 选择新画笔，并将旧画笔的指针保存到pOldPen   
	pOldPen = pDC->SelectObject(&newPen);

	int x = rectPicture.left + (rectPicture.left + rectPicture.right)/2;
	int y = rectPicture.top + 40;
	pDC->MoveTo(x, y);

	LinePoints(pDC, p, x, y, x*0.5);

	// 恢复旧画笔   
	pDC->SelectObject(pOldPen);   
	// 删除新画笔   
	newPen.DeleteObject();
}

void CTreapDlg::LinePoints(CDC *pDC, Treap_Node *p, int x, int y, int z){
	if (p)
	{
		pDC->LineTo(x, y);

		int v = p->value;
		int f = p->fix;
		CString str ;
		str.Format(_T("%d | %d"), v, f);
		pDC->TextOutW(x, y-15, str);

		pDC->MoveTo(x, y);
		LinePoints(pDC, p->left, x-z, y+40, z*0.5);
		pDC->MoveTo(x, y);
		LinePoints(pDC, p->right, x+z, y+40, z*0.5);
	}
}

void CTreapDlg::CleanTreap(Treap_Node *&p){
	if (p)
	{
		CleanTreap(p->left);
		CleanTreap(p->right);
		delete p;
	}
	p = 0;
}

void CTreapDlg::FindMaxMin(Treap_Node *p){
	//UpdateData(TRUE);
	Treap_Node *t = p;
	if(!t)
		return;
	while (NULL != (t->left))
	{
		t = t->left;
	}
	m_Min = t->value;
	while (NULL != (p->right))
	{
		p = p->right;
	}
	//UpdateData(TRUE);
	m_Max = p->value;
	//UpdateData(FALSE);
}

void CTreapDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Treap_Delete(p, m_key_del);
	FindMaxMin(p);
	UpdateData(FALSE);

	CRect rectPicture;
	m_pic.GetClientRect(&rectPicture);

	CBrush newBrush;   // 用于创建新画刷   
	CBrush *pOldBrush; // 用于存放旧画刷

	// 创建黑色新画刷   
	newBrush.CreateSolidBrush(RGB(255,255,255));   
	// 选择新画刷，并将旧画刷的指针保存到pOldBrush   
	pOldBrush = m_pic.GetDC()->SelectObject(&newBrush);   
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景   
	m_pic.GetDC()->Rectangle(rectPicture);   
	// 恢复旧画刷   
	m_pic.GetDC()->SelectObject(pOldBrush);   
	// 删除新画刷   
	newBrush.DeleteObject(); 

	DrawTreap(m_pic.GetDC(), rectPicture, p);
}


void CTreapDlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	CleanTreap(p);
	UpdateData(TRUE);
	m_Max = 0;
	m_Min = 0;
	UpdateData(FALSE);
	CRect rectPicture;
	m_pic.GetClientRect(&rectPicture);

	CBrush newBrush;   // 用于创建新画刷   
	CBrush *pOldBrush; // 用于存放旧画刷

	// 创建黑色新画刷   
	newBrush.CreateSolidBrush(RGB(255,255,255));   
	// 选择新画刷，并将旧画刷的指针保存到pOldBrush   
	pOldBrush = m_pic.GetDC()->SelectObject(&newBrush);   
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景   
	m_pic.GetDC()->Rectangle(rectPicture);   
	// 恢复旧画刷   
	m_pic.GetDC()->SelectObject(pOldBrush);   
	// 删除新画刷   
	newBrush.DeleteObject(); 

	DrawTreap(m_pic.GetDC(), rectPicture, p);
}
