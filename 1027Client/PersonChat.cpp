// PersonChat.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "PersonChat.h"
#include "afxdialogex.h"



// PersonChat 对话框

IMPLEMENT_DYNAMIC(PersonChat, CDialogEx)

PersonChat::PersonChat(CWnd* pParent /*=NULL*/)
	: CDialogEx(PersonChat::IDD, pParent)
	, m_personchat(_T(""))
{

}

PersonChat::~PersonChat()
{
}

void PersonChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_personchat);
	DDX_Control(pDX, IDC_LIST1, m_);
	DDX_Control(pDX, IDC_OCX1, m_player);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}


BEGIN_MESSAGE_MAP(PersonChat, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &PersonChat::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &PersonChat::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &PersonChat::OnBnClickedButton1)
END_MESSAGE_MAP()


// PersonChat 消息处理程序

extern CString dlgname;
extern CString delete_str;
extern int delete_id;
void PersonChat::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	STRU_PERSONCHAT_RQ spr;
	spr.m_nType = _DEF_PROTOCOL_PERSONCHAT_RQ;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,spr.m_szName,sizeof(spr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,delete_str,-1,spr.m_szNameChat,sizeof(spr.m_szNameChat),0,0);
	WideCharToMultiByte(CP_ACP,0,m_personchat,-1,spr.m_chatbuf,sizeof(spr.m_chatbuf),0,0);

	//获取当前时间 并且拼接在名字的后面
	SYSTEMTIME systime;
	GetLocalTime(&systime);

	char timebuf[5] = {0};
	_itoa_s(systime.wYear,timebuf,10);
	strcat_s(spr.m_szName," ");
	strcat_s(spr.m_szName,timebuf);
	strcat_s(spr.m_szName,"-");
	
	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wMonth,timebuf,10);
	strcat_s(spr.m_szName,timebuf);
	strcat_s(spr.m_szName,"-");

	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wDay,timebuf,10);
	strcat_s(spr.m_szName,timebuf);
	strcat_s(spr.m_szName," ");

	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wHour,timebuf,10);
	strcat_s(spr.m_szName,timebuf);
	strcat_s(spr.m_szName,":");

	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wMinute,timebuf,10);
	strcat_s(spr.m_szName,timebuf);
	strcat_s(spr.m_szName,":");

	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wSecond,timebuf,10);
	strcat_s(spr.m_szName,timebuf);

	//清空编辑框
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));

	theApp.GetKernel()->SendData((char*)&spr,sizeof(spr));
}


//询问对方是否接受视频通话
void PersonChat::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_INVITEVEDIO_RQ spr;
	spr.m_nType = _DEF_PROTOCOL_INVITEVEDIO_RQ;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,spr.m_szName,sizeof(spr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,delete_str,-1,spr.m_szNameInvite,sizeof(spr.m_szNameInvite),0,0);
	theApp.GetKernel()->SendData((char*)&spr,sizeof(spr));
}


//传文件
string PersonChat::GetFileMD5(const string &file) 
{  
	using std::fstream;
    ifstream in(file.c_str(), std::ios::binary);  
    if (!in)  
        return "";  
  
    MD5 md5;  
    std::streamsize length;  
    char buffer[1024];  
    while (!in.eof()) {  
        in.read(buffer, 1024);  
        length = in.gcount();  
        if (length > 0)  
            md5.update(buffer, length);  
    }  
    in.close();  
    return md5.toString();  
}  

FileDownloadInfo info;
void PersonChat::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE);
	if(IDOK == dlg.DoModal())
	{
		//dlg.GetPathName()="C:\\Users\\lenovo\\Desktop\\20190425\\你画我猜2.0.txt";

		STRU_SENDFILE_RQ ssr;
		ssr.m_nType=_DEF_PROTOCOL_SENDFILE_RQ;
		ZeroMemory(ssr.m_szMD5,sizeof(ssr.m_szMD5));
		WideCharToMultiByte(CP_ACP,0,dlgname,-1,ssr.m_szName,sizeof(ssr.m_szName),0,0);
		WideCharToMultiByte(CP_ACP,0,delete_str,-1,ssr.m_szNameChat,sizeof(ssr.m_szNameChat),0,0);
		WideCharToMultiByte(CP_ACP,0,dlg.GetFileName(),-1,ssr.m_szFileName,sizeof(ssr.m_szFileName),0,0);
		


		{CFile file(dlg.GetPathName(),CFile::modeRead);
		ssr.m_lFileSize = file.GetLength();}

		char temp[1024]={0};
		WideCharToMultiByte(CP_ACP,0,dlg.GetPathName(),-1,temp,sizeof(temp),0,0);
		string strFile = (char*)temp;
		if(ssr.m_lFileSize > MAX_STHRESH)
		{
			
			//sur.m_szMD5=
			memcpy(ssr.m_szMD5, GetFileMD5(strFile).c_str(),sizeof(ssr.m_szMD5));
		}

		info.m_llfilesize = ssr.m_lFileSize;
		info.m_llpos = 0;
		memcpy(info.m_szFileName,ssr.m_szFileName,sizeof(info.m_szFileName));
		
		int a;
		a=fopen_s(&info.pfile,(char*)temp,"rb");
		if(info.pfile != NULL)
		{
				theApp.GetKernel()->SendData((char*)&ssr,sizeof(ssr));
		}

		//发送上传文件的请求
		
	
	}
}
