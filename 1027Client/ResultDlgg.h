#pragma once
#include "afxcmn.h"


// ResultDlgg �Ի���

class ResultDlgg : public CDialogEx
{
	DECLARE_DYNAMIC(ResultDlgg)

public:
	ResultDlgg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ResultDlgg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_reslultlist;
public:
	BOOL OnInitDialog();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
};
