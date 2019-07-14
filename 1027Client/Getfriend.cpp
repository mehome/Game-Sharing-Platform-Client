// Getfriend.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "Getfriend.h"
#include "afxdialogex.h"


// CGetfriend 对话框

IMPLEMENT_DYNAMIC(CGetfriend, CDialogEx)

CGetfriend::CGetfriend(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetfriend::IDD, pParent)
{

}

CGetfriend::~CGetfriend()
{
}

void CGetfriend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGetfriend, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetfriend::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CGetfriend::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CGetfriend::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CGetfriend::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CGetfriend::OnBnClickedButton6)
END_MESSAGE_MAP()


// CGetfriend 消息处理程序

extern CString friend_str;
extern CString dlgname;

void CGetfriend::OnBnClickedButton1()
{
	STRU_GETFRIEND_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETFRIEND_RQ;
	WideCharToMultiByte(CP_ACP,0,friend_str,-1,sgr.m_friendName,sizeof(sgr.m_friendName),0,0);
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_szName,sizeof(sgr.m_szName),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	// TODO: 在此添加控件通知处理程序代码
}


//查看大厅在线玩家资料
void CGetfriend::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_LOOKPERSON_RQ slr;
	slr.m_nType = _DEF_PROTOCOL_LOOKPERSON_RQ;
	WideCharToMultiByte(CP_ACP,0,friend_str,-1,slr.m_szWantLookName,sizeof(slr.m_szWantLookName),0,0);
	theApp.GetKernel()->SendData((char*)&slr,sizeof(slr));
}


extern CString delete_str;
void CGetfriend::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_DELETEFRIEND_RQ sdr;

	sdr.m_nType=_DEF_PROTOCOL_DELETEFRIEND_RQ;
	WideCharToMultiByte(CP_ACP,0,delete_str,-1,sdr.m_deleteName,sizeof(sdr.m_deleteName),0,0);
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sdr.m_szName,sizeof(sdr.m_szName),0,0);

	theApp.GetKernel()->SendData((char*)&sdr,sizeof(sdr));
}


//私信
void CGetfriend::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.m_pMainWnd->PostMessage(UM_PERSONCHATMSG,0,0);
}


extern int inroom_id;
//邀请大厅在线的玩家游戏
//已经在房间里的玩家才可以邀请大厅里的玩家
void CGetfriend::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_INVITEPLAYER_RQ sir;
	sir.m_nType = _DEF_PROTOCOL_INVITEPLAYER_RQ;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sir.m_szName,sizeof(sir.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,friend_str,-1,sir.m_szNameInvite,sizeof(sir.m_szNameInvite),0,0);
	sir.m_roomid = inroom_id;

	theApp.GetKernel()->SendData((char*)&sir,sizeof(sir));
}
