
// TreapDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "TreapFunc.h"


// CTreapDlg 对话框
class CTreapDlg : public CDialogEx
{
// 构造
public:
	CTreapDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TREAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic;
	int m_value;
	int m_fix;
	Treap_Node *p;
	afx_msg void OnBnClickedButton1();
	void DrawTreap(CDC *pDC, CRect &rectPicture, Treap_Node *p);
	void LinePoints(CDC *pDC, Treap_Node *p, int x, int y, int z);
	void CleanTreap(Treap_Node *&p);
	void FindMaxMin(Treap_Node *p);
	int m_key_del;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedClear();
	CEdit m_max;
	CEdit m_min;
	int m_Max;
	int m_Min;
};
