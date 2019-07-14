// RoomDlgg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1027Client.h"
#include "RoomDlgg.h"
#include "afxdialogex.h"
#include <string.h>
using namespace std;


// CRoomDlgg �Ի���

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
	flag_ready = false; //δ׼�� ���Ե��׼��
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


// CRoomDlgg ��Ϣ�������

extern int inroom_id;
extern CString dlgname;
extern int sitidc;
extern int sitid;

//�뿪����
void CRoomDlgg::OnBnClickedButton1()
{
	flag = false;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	STRU_QUITROOM_RQ sqr;
	sqr.m_nType = _DEF_PROTOCOL_QUITROOM_RQ;
	sqr.m_roomid = inroom_id;
	sqr.sitidc = sitidc;
	sqr.sitid = sitid;
	sqr.flag_ready = flag_ready;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sqr.m_szName,sizeof(sqr.m_szName),0,0);

	//��ռ�ʱ�� ��նԻ���
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

//�رշ��䴰��
void CRoomDlgg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(IDOK);
	CDialogEx::OnClose();
}


//������ķ��Ͱ�ť
void CRoomDlgg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	STRU_CHATROOM_RQ scr;
	scr.m_nType = _DEF_PROTOCOL_CHATROOM_RQ;
	scr.m_roomid = inroom_id;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,scr.m_szName,sizeof(scr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_roomchatstr,-1,scr.m_chatbuf,sizeof(scr.m_chatbuf),0,0);
	scr.flag = flag;

	//��ȡ��ǰʱ�� ����ƴ�������ֵĺ���
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

	//��ձ༭��
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));

	theApp.GetKernel()->SendData((char*)&scr,sizeof(scr));
}


//��ͼ
void CRoomDlgg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	pointMouseDown = point;
	m_bFlag = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CRoomDlgg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bFlag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CRoomDlgg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bFlag == true && flag == true)
	{
		//����������ƶ��ͷ���
		STRU_GETPOINT_RQ sgr;
		
		CClientDC dc(this);
		CPen pen(PS_SOLID,5,color);   //  ����һ������
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


//����ʼ��Ϸ
void CRoomDlgg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

	m_inroomlst.InsertColumn(0,_T("�������"),LVCFMT_LEFT,100,50);
	m_inroomlst.InsertColumn(1,_T("����"),LVCFMT_LEFT,100,50);

	return TRUE;  // return TRUE unless you set the focus to a control
}


CBitmap* pBitmap;
int second;
extern char Drawplayername[_DEF_SIZE];

void CRoomDlgg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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

			//����ͼƬ
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
	//��ȡ���ڵ�ͼƬ  ��������
	CClientDC dc(this);
	CDC cdc;
	cdc.CreateCompatibleDC(&dc);
	pBitmap = new CBitmap;
	pBitmap->CreateCompatibleBitmap(&dc,800,400);
	cdc.SelectObject(pBitmap);

	cdc.BitBlt(0,0,800,400,&dc,0,0,SRCCOPY);

}


//�������ɫ�� ����������ɫ
void CRoomDlgg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog dlg;   // ��ɫ��
	if(dlg.DoModal() == IDOK)
	{
		color = dlg.GetColor();
	}
}


//����ȫ�ֱ��� ��¼��Ƥ��֮ǰ����ɫ
COLORREF g_color;

//��Ƥ����ť
void CRoomDlgg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_color = color;
	color = RGB(240,240,240);
}

//���ػ�ˢ
void CRoomDlgg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	color = g_color;
}


//׼���� ȡ��׼����ť
void CRoomDlgg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(flag_ready == false) //δ׼�� -> ׼��
	{
		STRU_READY_RQ srr;
		srr.m_nType = _DEF_PROTOCOL_READY_RQ;
		srr.flag_ready = true; //�������׼��
		srr.m_roomid = inroom_id;

		theApp.GetKernel()->SendData((char*)&srr,sizeof(srr));
	}
	else if(flag_ready == true) //׼�� -> δ׼��
	{
		STRU_READY_RQ srr;
		srr.m_nType = _DEF_PROTOCOL_READY_RQ;
		srr.flag_ready = false; //�������ȡ��׼��
		srr.m_roomid = inroom_id;
		
		theApp.GetKernel()->SendData((char*)&srr,sizeof(srr));
	}
}



void CRoomDlgg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	
	if(flag_ready == false)
		((CButton*)GetDlgItem(IDC_BUTTON9))->SetBitmap(m_hBitmapReady);
	else 
		((CButton*)GetDlgItem(IDC_BUTTON9))->SetBitmap(m_hBitmapWait);
}

