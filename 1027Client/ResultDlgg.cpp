// ResultDlgg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1027Client.h"
#include "ResultDlgg.h"
#include "afxdialogex.h"


// ResultDlgg �Ի���

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


// ResultDlgg ��Ϣ�������

BOOL ResultDlgg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_reslultlist.InsertColumn(0,_T("�������"),LVCFMT_LEFT,100,50);
	m_reslultlist.InsertColumn(1,_T("����"),LVCFMT_LEFT,100,50);

	return TRUE;  // return TRUE unless you set the focus to a control
}



//ȷ�� �ûر�־λ
void ResultDlgg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//�رս���Ի���
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg->OnClose();
}


void ResultDlgg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(IDOK);
	CDialogEx::OnClose();
}
