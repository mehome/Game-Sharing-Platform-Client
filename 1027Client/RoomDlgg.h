#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ResultDlgg.h"
#include "PictureDlg.h"

// CRoomDlgg �Ի���

class CRoomDlgg : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomDlgg)

public:
	CRoomDlgg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomDlgg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_inroomlst;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3();
	CString m_roomchatstr;
	CListBox m_chatroombox;

public:
	//��ͼ
	CPoint pointMouseDown;   //  ��¼���µĵ�
	bool m_bFlag;              //  �Ƿ��ͼ
	COLORREF color;            //  ��ɫ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	//����ͼƬ����
	void GetPicture();
	CPictureDlg* p_dlg;

	//��ʼ��Ϸ
	bool flag;
	int m_myclock;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//int m_clock;
	
	//���㵯��
	ResultDlgg* resdlg;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton9();

	//׼����ȡ��׼�� ����
	//0Ϊû��׼���� ��������ͼӦ����go
	//1Ϊ׼������ ����ȡ��׼�� ���Ե����ʼ ��������ͼӦ����wait
	bool flag_ready; 
	HBITMAP m_hBitmapReady;
	HBITMAP m_hBitmapWait;
	afx_msg void OnPaint();

};
