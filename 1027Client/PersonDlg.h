#pragma once


// PersonDlg �Ի���

class PersonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PersonDlg)

public:
	PersonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PersonDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString p_name;
	LONGLONG p_id;
	CString p_sex;

	int p_year;
	int p_month;
	int m_day;

	BOOL m_yespw;
	CString m_oldpw;
	CString m_newpw;
	CString m_newpw2;
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
};
