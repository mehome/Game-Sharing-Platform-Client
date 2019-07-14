
// 1027ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1027Client.h"
#include "1027ClientDlg.h"
#include "afxdialogex.h"
#include "MyDlgMain.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy1027ClientDlg �Ի���



CMy1027ClientDlg::CMy1027ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy1027ClientDlg::IDD, pParent)
	, m_edttelphone(18845791386)
	, m_edtusername(_T("aleialei"))
	, m_edtpassword(_T("123456"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1027ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edttelphone);
	DDX_Text(pDX, IDC_EDIT2, m_edtusername);
	DDX_Text(pDX, IDC_EDIT3, m_edtpassword);
}

BEGIN_MESSAGE_MAP(CMy1027ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy1027ClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy1027ClientDlg::OnBnClickedButton2)
	ON_MESSAGE(UM_LOGINMSG,&CMy1027ClientDlg::LoginMsg)
END_MESSAGE_MAP()


// CMy1027ClientDlg ��Ϣ�������

extern CString dlgname;


LRESULT CMy1027ClientDlg::LoginMsg(WPARAM w,LPARAM l)
{
	CMyDlgMain dlg;
	theApp.m_pMainWnd = &dlg;
	EndDialog(IDOK);
	dlg.m_edtname = dlgname; //�û�����ʾ�Ŀؼ�������
	dlg.DoModal();

	return 0;
}

BOOL CMy1027ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy1027ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy1027ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	
	}
	else
	{
		CDialogEx::OnPaint();
	
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy1027ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//ע�ᰴť
void CMy1027ClientDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	//11λ
	if(m_edttelphone <=9999999999 || m_edttelphone >100000000000)
	{
		MessageBox(_T("��������ȷ���ֻ�����"));
		return;
	}

	int nlen = m_edtusername.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("�û���������6-16λ��Ч�ַ�"));
		return;
	}
	
	nlen = m_edtpassword.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("����������6-16λ��Ч�ַ�"));
		return;
	}

	STRU_REGISTER_RQ srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
	srr.m_tel = m_edttelphone;
	WideCharToMultiByte(CP_ACP,0,m_edtusername,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_edtpassword,-1,srr.m_szPassword,sizeof(srr.m_szPassword),0,0);
	//ע ��ǰ������unicode ���Ǵ�����������ʱchar��  ��Ҫ�����ַ���ת�ɶ��ֽ� 

	theApp.GetKernel()->SendData((char*)&srr,sizeof(srr));
}

//��¼��ť
void CMy1027ClientDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	int nlen = m_edtusername.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("�û���������6-16λ��Ч�ַ�"));
		return;
	}
	 nlen = m_edtpassword.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("����������6-16λ��Ч�ַ�"));
		return;
	}

	STRU_LOGIN_RQ srr;
	srr.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
	WideCharToMultiByte(CP_ACP,0,m_edtusername,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_edtpassword,-1,srr.m_szPassword,sizeof(srr.m_szPassword),0,0);

	theApp.GetKernel()->SendData((char*)&srr,sizeof(srr));

	STRU_GETLISTFRIEND_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETLISTFRIEND_RQ;
	WideCharToMultiByte(CP_ACP,0,m_edtusername,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
}
