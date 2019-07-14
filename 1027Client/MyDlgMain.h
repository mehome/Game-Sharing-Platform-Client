#pragma once
#include "1027ClientDlg.h"
#include "Packdef.h"
#include "RoomDlgg.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "PersonDlg.h"
#include "LookPersonDlg.h"
#include "Getfriend.h"
#include "IsAgreeFriend.h"
#include "PersonChat.h"
// CMyDlgMain 对话框

class CMyDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDlgMain)

public:
	CMyDlgMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDlgMain();

// 对话框数据
	enum { IDD = IDD_DIGMAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CMy1027ClientDlg my_ClientDlg;
	CString m_edtname;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	CFont m_font;
	list<Room*>  m_listtable;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton24();

public:
	Player m_player;
	CString m_playername;

public:
	HBITMAP m_hBitmap1;
	HBITMAP m_hBitmapW;
	HBITMAP m_hBitmapB;
	HBITMAP m_hBitmapSit;
	HBITMAP m_hBitmapSitYes;
	afx_msg void OnBnClickedButton39();

public:
	CListCtrl m_lstonline;
	afx_msg void OnBnClickedButton40();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton38();
	CString m_chatstr; //获取到的聊天内容
	CListBox m_chatbox; //显示聊天内容的控件
	CListCtrl m_friendlist;

public:
	afx_msg LRESULT CreateRoomDlg(WPARAM ,LPARAM);
	afx_msg LRESULT CreateResRoomDlg(WPARAM ,LPARAM);
	afx_msg LRESULT IsAgreeFriend(WPARAM ,LPARAM);
	afx_msg LRESULT IsLookPersonDlg(WPARAM ,LPARAM);
	afx_msg LRESULT PersonChatDlg(WPARAM ,LPARAM);
	afx_msg LRESULT PlayerPlayDlg(WPARAM ,LPARAM);
	
	CRoomDlgg* dlg;
	PersonDlg* dlg_p;
	CGetfriend * GetF_dlg;
	CIsAgreeFriend* m_isagreefriend;
	LookPersonDlg* dlg_lp;
	PersonChat* dlg_pc;

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMRClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton41();
};
