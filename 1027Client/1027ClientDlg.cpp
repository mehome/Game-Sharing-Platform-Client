
// 1027ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "1027ClientDlg.h"
#include "afxdialogex.h"
#include "MyDlgMain.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMy1027ClientDlg 对话框



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


// CMy1027ClientDlg 消息处理程序

extern CString dlgname;


LRESULT CMy1027ClientDlg::LoginMsg(WPARAM w,LPARAM l)
{
	CMyDlgMain dlg;
	theApp.m_pMainWnd = &dlg;
	EndDialog(IDOK);
	dlg.m_edtname = dlgname; //用户名显示的控件变量名
	dlg.DoModal();

	return 0;
}

BOOL CMy1027ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy1027ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	
	}
	else
	{
		CDialogEx::OnPaint();
	
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy1027ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//注册按钮
void CMy1027ClientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	//11位
	if(m_edttelphone <=9999999999 || m_edttelphone >100000000000)
	{
		MessageBox(_T("请输入正确的手机号码"));
		return;
	}

	int nlen = m_edtusername.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("用户名请输入6-16位有效字符"));
		return;
	}
	
	nlen = m_edtpassword.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("密码请输入6-16位有效字符"));
		return;
	}

	STRU_REGISTER_RQ srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
	srr.m_tel = m_edttelphone;
	WideCharToMultiByte(CP_ACP,0,m_edtusername,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_edtpassword,-1,srr.m_szPassword,sizeof(srr.m_szPassword),0,0);
	//注 当前程序是unicode 但是传过来的数据时char型  需要将宽字符集转成多字节 

	theApp.GetKernel()->SendData((char*)&srr,sizeof(srr));
}

//登录按钮
void CMy1027ClientDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	int nlen = m_edtusername.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("用户名请输入6-16位有效字符"));
		return;
	}
	 nlen = m_edtpassword.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("密码请输入6-16位有效字符"));
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
