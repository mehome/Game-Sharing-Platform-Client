#pragma once


// CIsAgreeFriend �Ի���

class CIsAgreeFriend : public CDialogEx
{
	DECLARE_DYNAMIC(CIsAgreeFriend)

public:
	CIsAgreeFriend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIsAgreeFriend();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_invitor;
	int m_inviteroomid;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
