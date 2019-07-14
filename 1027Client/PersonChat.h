#pragma once
#include "afxcmn.h"
#include <map>
#include<iostream>
#include<fstream>
#include "afxwin.h"
#include "md5.h"  
using namespace std;

#include "ocx1.h"
#include "Myffmpeg.h"
#include "CWMPPlayer4.h"
#include "CWMPControls.h"
#include "CWMPMedia.h"
#include "CWMPSettings.h"


// PersonChat �Ի���
typedef struct FileUpLoadInfo
{
	FILE *pfile;
	long long m_llpos;
	long long m_llfilesize;
	char m_szFileName[MAX_PATH];

}FileDownloadInfo;

class PersonChat : public CDialogEx
{
	DECLARE_DYNAMIC(PersonChat)

public:
	PersonChat(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PersonChat();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_personchat;
	afx_msg void OnBnClickedButton3();
	CListBox m_;
	afx_msg void OnBnClickedButton4();

public:
	Myffmpeg m_ffmpeg;
	CWMPPlayer4 m_player;

public:
	//�ļ�
	static string GetFileMD5(const string &file);
	afx_msg void OnBnClickedButton1();
	CStatic m_picture;
};
