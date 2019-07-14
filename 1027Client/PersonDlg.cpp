// PersonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "PersonDlg.h"
#include "afxdialogex.h"


// PersonDlg 对话框

IMPLEMENT_DYNAMIC(PersonDlg, CDialogEx)

extern CString dlgname;

PersonDlg::PersonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PersonDlg::IDD, pParent)
	, p_name(dlgname)
	, p_id(0)
	, p_sex(_T("男"))
	, p_year(2000)
	, p_month(1)
	, m_day(1)
	, m_yespw(FALSE)
	, m_oldpw(_T(""))
	, m_newpw(_T(""))
	, m_newpw2(_T(""))
{
}

PersonDlg::~PersonDlg()
{
}

void PersonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, p_name);
	DDX_Text(pDX, IDC_EDIT2, p_id);
	DDX_Text(pDX, IDC_EDIT3, p_sex);
	DDX_Text(pDX, IDC_EDIT4, p_year);
	DDX_Text(pDX, IDC_EDIT5, p_month);
	DDX_Text(pDX, IDC_EDIT6, m_day);
	DDX_Check(pDX, IDC_CHECK1, m_yespw);
	DDX_Text(pDX, IDC_EDIT7, m_oldpw);
	DDX_Text(pDX, IDC_EDIT8, m_newpw);
	DDX_Text(pDX, IDC_EDIT9, m_newpw2);
}


BEGIN_MESSAGE_MAP(PersonDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &PersonDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &PersonDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &PersonDlg::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// PersonDlg 消息处理程序

//设置头像
void PersonDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

//取消修改 关闭对话框
void PersonDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	PersonDlg::OnClose();
}

//确定修改
void PersonDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	STRU_ALTERPERSON_RQ spr;
	spr.m_nType = _DEF_PROTOCOL_ALTERPERSON_RQ;
	
	//用户名：不可修改
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,spr.m_szName,sizeof(spr.m_szName),0,0);
	//1.手机号：不改变存0
	if(p_id == 0)
		spr.m_tel = 0;
	else 
		spr.m_tel = p_id;
	//2.性别：男0女1
	if(p_sex == _T("男"))
		spr.sex = 0;
	else if(p_sex == _T("女"))
		spr.sex = 1;
	//3.出生日期
	spr.m_Year = p_year;
	spr.m_Month = p_month;
	spr.m_Day = m_day;
	//4.是否修改密码
	if(m_yespw == FALSE)
	{
		spr.b_yespw = m_yespw;
		memset(spr.m_szoldpw,0,_DEF_SIZE);
		memset(spr.m_sznewpw,0,_DEF_SIZE);
		memset(spr.m_sznewpw2,0,_DEF_SIZE);
	}
	else 
	{
		spr.b_yespw = m_yespw;
		WideCharToMultiByte(CP_ACP,0,m_oldpw,-1,spr.m_szoldpw,sizeof(spr.m_szoldpw),0,0);
		WideCharToMultiByte(CP_ACP,0,m_newpw,-1,spr.m_sznewpw,sizeof(spr.m_sznewpw),0,0);
		WideCharToMultiByte(CP_ACP,0,m_newpw2,-1,spr.m_sznewpw2,sizeof(spr.m_sznewpw2),0,0);
	}

	theApp.GetKernel()->SendData((char*)&spr,sizeof(spr));
}




void PersonDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDOK);
	CDialogEx::OnClose();
}
