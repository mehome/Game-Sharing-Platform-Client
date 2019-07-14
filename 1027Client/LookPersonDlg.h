#pragma once


// LookPersonDlg 对话框

class LookPersonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LookPersonDlg)

public:
	LookPersonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LookPersonDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
