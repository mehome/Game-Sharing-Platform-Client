// RoomDlgg.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "RoomDlgg.h"
#include "afxdialogex.h"
#include <string.h>
using namespace std;


// CRoomDlgg 对话框

IMPLEMENT_DYNAMIC(CRoomDlgg, CDialogEx)

CRoomDlgg::CRoomDlgg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRoomDlgg::IDD, pParent)
	, m_roomchatstr(_T(""))
	//, m_clock(0)
{
	flag = false;
	resdlg = NULL;

	m_hBitmapReady = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP11)); 
	m_hBitmapWait = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP10)); 
	flag_ready = false; //未准备 可以点击准备
}

CRoomDlgg::~CRoomDlgg()
{
}

void CRoomDlgg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_inroomlst);
	DDX_Text(pDX, IDC_EDIT1, m_roomchatstr);
	DDX_Control(pDX, IDC_LIST2, m_chatroombox);
	//DDX_Text(pDX, IDC_EDIT2, m_clock);
}


BEGIN_MESSAGE_MAP(CRoomDlgg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRoomDlgg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3, &CRoomDlgg::OnBnClickedButton3)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON2, &CRoomDlgg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON6, &CRoomDlgg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CRoomDlgg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CRoomDlgg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON9, &CRoomDlgg::OnBnClickedButton9)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRoomDlgg 消息处理程序

extern int inroom_id;
extern CString dlgname;
extern int sitidc;
extern int sitid;

//离开房间
void CRoomDlgg::OnBnClickedButton1()
{
	flag = false;
	// TODO: 在此添加控件通知处理程序代码
	STRU_QUITROOM_RQ sqr;
	sqr.m_nType = _DEF_PROTOCOL_QUITROOM_RQ;
	sqr.m_roomid = inroom_id;
	sqr.sitidc = sitidc;
	sqr.sitid = sitid;
	sqr.flag_ready = flag_ready;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sqr.m_szName,sizeof(sqr.m_szName),0,0);

	//清空计时器 清空对话框
	KillTimer(START_GAME_TIMER_ID);
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_myclock = 0;
	CEdit * edt = (CEdit*)GetDlgItem(IDC_EDIT2);
	char buf[3];
	memset(buf,0,sizeof(buf));
	_itoa_s(m_myclock,buf,10);
	CString sss;
	sss = buf;
	edt->SetWindowText(sss);
	m_chatroombox.ResetContent();

	theApp.GetKernel()->SendData((char*)&sqr,sizeof(sqr));
}

//关闭房间窗口
void CRoomDlgg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDOK);
	CDialogEx::OnClose();
}


//房间里的发送按钮
void CRoomDlgg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	STRU_CHATROOM_RQ scr;
	scr.m_nType = _DEF_PROTOCOL_CHATROOM_RQ;
	scr.m_roomid = inroom_id;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,scr.m_szName,sizeof(scr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_roomchatstr,-1,scr.m_chatbuf,sizeof(scr.m_chatbuf),0,0);
	scr.flag = flag;

	//获取当前时间 并且拼接在名字的后面
	SYSTEMTIME systime;
	GetLocalTime(&systime);

	char timebuf[5] = {0};
	_itoa_s(systime.wYear,timebuf,10);
	strcat_s(scr.m_szName," ");
	strcat_s(scr.m_szName,timebuf);
	strcat_s(scr.m_szName,"-");
	
	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wMonth,timebuf,10);
	strcat_s(scr.m_szName,timebuf);
	strcat_s(scr.m_szName,"-");

	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wDay,timebuf,10);
	strcat_s(scr.m_szName,timebuf);
	strcat_s(scr.m_szName," ");

	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wHour,timebuf,10);
	strcat_s(scr.m_szName,timebuf);
	strcat_s(scr.m_szName,":");

	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wMinute,timebuf,10);
	strcat_s(scr.m_szName,timebuf);
	strcat_s(scr.m_szName,":");

	memset(timebuf,0,sizeof(timebuf));
	_itoa_s(systime.wSecond,timebuf,10);
	strcat_s(scr.m_szName,timebuf);

	//清空编辑框
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));

	theApp.GetKernel()->SendData((char*)&scr,sizeof(scr));
}


//绘图
void CRoomDlgg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pointMouseDown = point;
	m_bFlag = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CRoomDlgg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bFlag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CRoomDlgg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bFlag == true && flag == true)
	{
		//发生了鼠标移动就发包
		STRU_GETPOINT_RQ sgr;
		
		CClientDC dc(this);
		CPen pen(PS_SOLID,5,color);   //  创建一个画笔
		dc.SelectObject(pen);
		dc.MoveTo(pointMouseDown);
		dc.LineTo(point);
		
		sgr.movepoint = pointMouseDown;
		sgr.point = point;
		
		sgr.m_nType = _DEF_PROTOCOL_GETPOINT_RQ;
		WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_szName,sizeof(sgr.m_szName),0,0);
		sgr.m_roomid = inroom_id;

		sgr.color = color;
		theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
		
		pointMouseDown = point;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


//请求开始游戏
void CRoomDlgg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	STRU_START_RQ ssr;
	ssr.m_nType = _DEF_PROTOCOL_START_RQ;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,ssr.m_szName,sizeof(ssr.m_szName),0,0);
	ssr.m_roomid = inroom_id;

	GetDlgItem(IDC_STATIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC)->ShowWindow(TRUE);

	theApp.GetKernel()->SendData((char*)&ssr,sizeof(ssr));
}


BOOL CRoomDlgg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_inroomlst.InsertColumn(0,_T("玩家姓名"),LVCFMT_LEFT,100,50);
	m_inroomlst.InsertColumn(1,_T("分数"),LVCFMT_LEFT,100,50);

	return TRUE;  // return TRUE unless you set the focus to a control
}


CBitmap* pBitmap;
int second;
extern char Drawplayername[_DEF_SIZE];

void CRoomDlgg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nIDEvent)
	{
	case START_GAME_TIMER_ID:
	{
		CEdit * edt = (CEdit*)GetDlgItem(IDC_EDIT2);

		char buf[3];
		memset(buf,0,sizeof(buf));
		_itoa_s(m_myclock,buf,10);

		CString sss;
		sss = buf;

		edt->SetWindowText(sss);
		if(m_myclock > -1)
		{
			m_myclock --;
		}
		if(m_myclock == -1)
		{
			KillTimer(START_GAME_TIMER_ID);

			//弹窗图片
			GetPicture();
			if(p_dlg == NULL)
			{
				p_dlg = new CPictureDlg;
				p_dlg->Create(IDD_DIALOG3);
			}
			p_dlg->ShowWindow(SW_SHOW);
			SetTimer(CLOSE_DLG_TIMER_ID,1000,NULL);
			second = 0;
			
		}
		break;
	}

	case CLOSE_DLG_TIMER_ID:
	{
		if(second < 6)
			second ++;
		if(second == 6)
		{
			second = 0;
			KillTimer(CLOSE_DLG_TIMER_ID);
			p_dlg->OnClose();

			char m_szName[_DEF_SIZE] = {0};
			WideCharToMultiByte(CP_ACP,0,dlgname,-1,m_szName,sizeof(m_szName),0,0);
			if(strncmp(m_szName,Drawplayername,_DEF_SIZE) == 0)
			{
				OnBnClickedButton2();
				//flag = true;
			}
		}

		/*STRU_START_RQ sssr;
		sssr.m_nType = _DEF_PROTOCOL_START_RQ;
		sssr.m_roomid = inroom_id;
		sssr.m_szName[0] = '\0';*/

	}

	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);

}


void CRoomDlgg::GetPicture()
{
	//获取窗口的图片  保存起来
	CClientDC dc(this);
	CDC cdc;
	cdc.CreateCompatibleDC(&dc);
	pBitmap = new CBitmap;
	pBitmap->CreateCompatibleBitmap(&dc,800,400);
	cdc.SelectObject(pBitmap);

	cdc.BitBlt(0,0,800,400,&dc,0,0,SRCCOPY);

}


//点击弹出色板 更换画笔颜色
void CRoomDlgg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;   // 调色板
	if(dlg.DoModal() == IDOK)
	{
		color = dlg.GetColor();
	}
}


//来个全局变量 记录橡皮擦之前的颜色
COLORREF g_color;

//橡皮擦按钮
void CRoomDlgg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	g_color = color;
	color = RGB(240,240,240);
}

//返回画刷
void CRoomDlgg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	color = g_color;
}


//准备和 取消准备按钮
void CRoomDlgg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	if(flag_ready == false) //未准备 -> 准备
	{
		STRU_READY_RQ srr;
		srr.m_nType = _DEF_PROTOCOL_READY_RQ;
		srr.flag_ready = true; //玩家请求准备
		srr.m_roomid = inroom_id;

		theApp.GetKernel()->SendData((char*)&srr,sizeof(srr));
	}
	else if(flag_ready == true) //准备 -> 未准备
	{
		STRU_READY_RQ srr;
		srr.m_nType = _DEF_PROTOCOL_READY_RQ;
		srr.flag_ready = false; //玩家请求取消准备
		srr.m_roomid = inroom_id;
		
		theApp.GetKernel()->SendData((char*)&srr,sizeof(srr));
	}
}



void CRoomDlgg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	
	if(flag_ready == false)
		((CButton*)GetDlgItem(IDC_BUTTON9))->SetBitmap(m_hBitmapReady);
	else 
		((CButton*)GetDlgItem(IDC_BUTTON9))->SetBitmap(m_hBitmapWait);
}

