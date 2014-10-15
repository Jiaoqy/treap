
// TreapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Treap.h"
#include "TreapDlg.h"
#include "TreapFunc.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTreapDlg �Ի���



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


// CTreapDlg ��Ϣ�������

BOOL CTreapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTreapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTreapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTreapDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	Treap_Insert(p, m_value, m_fix);
	FindMaxMin(p);
	//m_Max = p->value;
	UpdateData(FALSE);

	CRect rectPicture;
	m_pic.GetClientRect(&rectPicture);

	CBrush newBrush;   // ���ڴ����»�ˢ   
	CBrush *pOldBrush; // ���ڴ�žɻ�ˢ

	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(255,255,255));   
	// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
	pOldBrush = m_pic.GetDC()->SelectObject(&newBrush);   
	// �Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����   
	m_pic.GetDC()->Rectangle(rectPicture);   
	// �ָ��ɻ�ˢ   
	m_pic.GetDC()->SelectObject(pOldBrush);   
	// ɾ���»�ˢ   
	newBrush.DeleteObject(); 

	DrawTreap(m_pic.GetDC(), rectPicture, p);
}

void CTreapDlg::DrawTreap(CDC *pDC, CRect &rectPicture, Treap_Node * p){
	CPen newPen;       // ���ڴ����»���   
	CPen *pOldPen;     // ���ڴ�žɻ���  

	// ����ʵ�Ļ��ʣ��ֶ�Ϊ1����ɫΪ��ɫ   
	newPen.CreatePen(PS_SOLID, 1, RGB(0,0,0));   
	// ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽pOldPen   
	pOldPen = pDC->SelectObject(&newPen);

	int x = rectPicture.left + (rectPicture.left + rectPicture.right)/2;
	int y = rectPicture.top + 40;
	pDC->MoveTo(x, y);

	LinePoints(pDC, p, x, y, x*0.5);

	// �ָ��ɻ���   
	pDC->SelectObject(pOldPen);   
	// ɾ���»���   
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	Treap_Delete(p, m_key_del);
	FindMaxMin(p);
	UpdateData(FALSE);

	CRect rectPicture;
	m_pic.GetClientRect(&rectPicture);

	CBrush newBrush;   // ���ڴ����»�ˢ   
	CBrush *pOldBrush; // ���ڴ�žɻ�ˢ

	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(255,255,255));   
	// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
	pOldBrush = m_pic.GetDC()->SelectObject(&newBrush);   
	// �Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����   
	m_pic.GetDC()->Rectangle(rectPicture);   
	// �ָ��ɻ�ˢ   
	m_pic.GetDC()->SelectObject(pOldBrush);   
	// ɾ���»�ˢ   
	newBrush.DeleteObject(); 

	DrawTreap(m_pic.GetDC(), rectPicture, p);
}


void CTreapDlg::OnBnClickedClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CleanTreap(p);
	UpdateData(TRUE);
	m_Max = 0;
	m_Min = 0;
	UpdateData(FALSE);
	CRect rectPicture;
	m_pic.GetClientRect(&rectPicture);

	CBrush newBrush;   // ���ڴ����»�ˢ   
	CBrush *pOldBrush; // ���ڴ�žɻ�ˢ

	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(255,255,255));   
	// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
	pOldBrush = m_pic.GetDC()->SelectObject(&newBrush);   
	// �Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����   
	m_pic.GetDC()->Rectangle(rectPicture);   
	// �ָ��ɻ�ˢ   
	m_pic.GetDC()->SelectObject(pOldBrush);   
	// ɾ���»�ˢ   
	newBrush.DeleteObject(); 

	DrawTreap(m_pic.GetDC(), rectPicture, p);
}
