#pragma once


// LookPersonDlg �Ի���

class LookPersonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LookPersonDlg)

public:
	LookPersonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LookPersonDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_WantPersonName;
	CString m_tel;
	CString m_sex;
	int m_year;
	int m_month;
	int m_score;
	int m_level;
	float m_winpercent;
	int m_dayy;
	afx_msg void OnClose();
};
