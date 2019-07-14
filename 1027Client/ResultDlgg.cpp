// ResultDlgg.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "ResultDlgg.h"
#include "afxdialogex.h"


// ResultDlgg 对话框

IMPLEMENT_DYNAMIC(ResultDlgg, CDialogEx)

ResultDlgg::ResultDlgg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ResultDlgg::IDD, pParent)
{

}

ResultDlgg::~ResultDlgg()
{
}

void ResultDlgg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_reslultlist);
}


BEGIN_MESSAGE_MAP(ResultDlgg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ResultDlgg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ResultDlgg 消息处理程序

BOOL ResultDlgg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_reslultlist.InsertColumn(0,_T("玩家姓名"),LVCFMT_LEFT,100,50);
	m_reslultlist.InsertColumn(1,_T("分数"),LVCFMT_LEFT,100,50);

	return TRUE;  // return TRUE unless you set the focus to a control
}



//确定 置回标志位
void ResultDlgg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//关闭结算对话框
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg->OnClose();
}


void ResultDlgg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDOK);
	CDialogEx::OnClose();
}
