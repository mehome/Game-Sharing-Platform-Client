#pragma once


// CGetfriend 对话框

class CGetfriend : public CDialogEx
{
	DECLARE_DYNAMIC(CGetfriend)

public:
	CGetfriend(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetfriend();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
