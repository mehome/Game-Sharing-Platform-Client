#pragma once


// CGetfriend �Ի���

class CGetfriend : public CDialogEx
{
	DECLARE_DYNAMIC(CGetfriend)

public:
	CGetfriend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetfriend();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
