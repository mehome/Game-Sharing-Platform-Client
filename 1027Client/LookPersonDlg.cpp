// LookPersonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "LookPersonDlg.h"
#include "afxdialogex.h"


// LookPersonDlg 对话框

IMPLEMENT_DYNAMIC(LookPersonDlg, CDialogEx)


extern STRU_LOOKPERSON_RS g_slr;

LookPersonDlg::LookPersonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LookPersonDlg::IDD, pParent)
	, m_WantPersonName(g_slr.m_szWantLookName)
	, m_tel(g_slr.p_id)
	, m_sex(g_slr.sex == 0 ? _T("男"):_T("女"))
	, m_year(g_slr.m_Year)
	, m_month(g_slr.m_Month)
	, m_score(g_slr.m_score)
	, m_level(g_slr.m_level)
	, m_winpercent(g_slr.m_winpercent)
	, m_dayy(g_slr.m_Day)
{

}

LookPersonDlg::~LookPersonDlg()
{
}

void LookPersonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_WantPersonName);
	DDX_Text(pDX, IDC_EDIT2, m_tel);
	DDX_Text(pDX, IDC_EDIT3, m_sex);
	DDX_Text(pDX, IDC_EDIT4, m_year);
	DDX_Text(pDX, IDC_EDIT5, m_month);
	DDX_Text(pDX, IDC_EDIT7, m_score);
	DDX_Text(pDX, IDC_EDIT8, m_level);
	DDX_Text(pDX, IDC_EDIT9, m_winpercent);
	DDX_Text(pDX, IDC_EDIT10, m_dayy);
}


BEGIN_MESSAGE_MAP(LookPersonDlg, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// LookPersonDlg 消息处理程序


void LookPersonDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg_lp = NULL;
	CDialogEx::OnClose();
}
