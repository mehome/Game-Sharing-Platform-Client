// IsAgreeFriend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1027Client.h"
#include "IsAgreeFriend.h"
#include "afxdialogex.h"

extern bool is_invite;
extern CString invite_name;
extern int invite_roomid;
// CIsAgreeFriend �Ի���

IMPLEMENT_DYNAMIC(CIsAgreeFriend, CDialogEx)

CIsAgreeFriend::CIsAgreeFriend(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIsAgreeFriend::IDD, pParent)
	, m_invitor(is_invite == true ? invite_name:_T(""))
	, m_inviteroomid(is_invite == true ? invite_roomid:0)
{

}

CIsAgreeFriend::~CIsAgreeFriend()
{
}

void CIsAgreeFriend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_invitor);
	DDX_Text(pDX, IDC_EDIT2, m_inviteroomid);
}


BEGIN_MESSAGE_MAP(CIsAgreeFriend, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CIsAgreeFriend::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CIsAgreeFriend::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CIsAgreeFriend::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CIsAgreeFriend::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CIsAgreeFriend::OnBnClickedButton6)
END_MESSAGE_MAP()


// CIsAgreeFriend ��Ϣ�������

extern char m_friendname[_DEF_SIZE];

//��Ӻ��ѣ�ͬ�ⰴť
void CIsAgreeFriend::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	STRU_GETFRIEND_RS sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETFRIEND_RS;
	sgr.m_isagree=0;
	strcpy_s(sgr.m_friendName,m_friendname);
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_szName,sizeof(sgr.m_szName),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));

}



//ͬ�⣺��������
void CIsAgreeFriend::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	STRU_INVITEPLAYERYN_RQ sir;
	sir.m_nType = _DEF_PROTOCOL_INVITEPLAYERYN_RQ;
	WideCharToMultiByte(CP_ACP,0,invite_name,-1,sir.m_szName,sizeof(sir.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sir.m_szNameInvite,sizeof(sir.m_szNameInvite),0,0);
	sir.m_roomid = invite_roomid;
	sir.szResult = _inviteplayer_agree;

	theApp.GetKernel()->SendData((char*)&sir,sizeof(sir));
}


//�ܾ����룺��ȥ
void CIsAgreeFriend::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	STRU_INVITEPLAYERYN_RQ sir;
	sir.m_nType = _DEF_PROTOCOL_INVITEPLAYERYN_RQ;
	WideCharToMultiByte(CP_ACP,0,invite_name,-1,sir.m_szName,sizeof(sir.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sir.m_szNameInvite,sizeof(sir.m_szNameInvite),0,0);
	sir.m_roomid = invite_roomid;
	sir.szResult = _inviteplayer_refuse;

	theApp.GetKernel()->SendData((char*)&sir,sizeof(sir));
}

extern CString delete_str;
//��Ƶ��ͬ��
void CIsAgreeFriend::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	STRU_INVITEVEDIO_RS sir;
	sir.m_nType = _DEF_PROTOCOL_INVITEVEDIO_RS;
	WideCharToMultiByte(CP_ACP,0,delete_str,-1,sir.m_szName,sizeof(sir.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sir.m_szNameInvite,sizeof(sir.m_szNameInvite),0,0);
	sir.szResult = _invitevedio_agree;
	theApp.GetKernel()->SendData((char*)&sir,sizeof(sir));
}

//��Ƶ���ܾ�
void CIsAgreeFriend::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	STRU_INVITEVEDIO_RS sir;
	sir.m_nType = _DEF_PROTOCOL_INVITEVEDIO_RS;
	WideCharToMultiByte(CP_ACP,0,delete_str,-1,sir.m_szName,sizeof(sir.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sir.m_szNameInvite,sizeof(sir.m_szNameInvite),0,0);
	sir.szResult = _invitevedio_refuse;
	theApp.GetKernel()->SendData((char*)&sir,sizeof(sir));
}
