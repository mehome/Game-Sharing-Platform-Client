#pragma once
#include "afxcmn.h"


// ResultDlgg 对话框

class ResultDlgg : public CDialogEx
{
	DECLARE_DYNAMIC(ResultDlgg)

public:
	ResultDlgg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ResultDlgg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_reslultlist;
public:
	BOOL OnInitDialog();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
};
