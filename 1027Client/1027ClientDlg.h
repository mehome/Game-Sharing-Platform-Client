
// 1027ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"

extern CString dlgname;

// CMy1027ClientDlg �Ի���
class CMy1027ClientDlg : public CDialogEx
{
// ����
public:
	CMy1027ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY1027CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	LONGLONG m_edttelphone;
	CString m_edtusername;
	CString m_edtpassword;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

public:
	LRESULT LoginMsg(WPARAM w,LPARAM l);

};
