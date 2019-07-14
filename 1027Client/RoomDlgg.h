#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ResultDlgg.h"
#include "PictureDlg.h"

// CRoomDlgg 对话框

class CRoomDlgg : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomDlgg)

public:
	CRoomDlgg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRoomDlgg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_inroomlst;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3();
	CString m_roomchatstr;
	CListBox m_chatroombox;

public:
	//绘图
	CPoint pointMouseDown;   //  记录按下的点
	bool m_bFlag;              //  是否绘图
	COLORREF color;            //  颜色
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	//个人图片弹窗
	void GetPicture();
	CPictureDlg* p_dlg;

	//开始游戏
	bool flag;
	int m_myclock;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//int m_clock;
	
	//结算弹窗
	ResultDlgg* resdlg;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton9();

	//准备和取消准备 定义
	//0为没有准备好 贴出来的图应该是go
	//1为准备好了 可以取消准备 可以点击开始 贴出来的图应该是wait
	bool flag_ready; 
	HBITMAP m_hBitmapReady;
	HBITMAP m_hBitmapWait;
	afx_msg void OnPaint();

};
