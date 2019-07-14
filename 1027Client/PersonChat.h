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


// PersonChat 对话框
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
	PersonChat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PersonChat();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	//文件
	static string GetFileMD5(const string &file);
	afx_msg void OnBnClickedButton1();
	CStatic m_picture;
};
