// MyDlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "MyDlgMain.h"
#include "afxdialogex.h"

#include<iostream>
#include<windows.h>
#include<string.h>
using namespace std;

// CMyDlgMain 对话框

extern CString dlgname;

IMPLEMENT_DYNAMIC(CMyDlgMain, CDialogEx)

CMyDlgMain::CMyDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDlgMain::IDD, pParent)
	, m_edtname(_T(""))
	, m_chatstr(_T(""))
{
	m_hBitmap1 = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP3)); 
	m_hBitmapW = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP5));
	m_hBitmapB = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP6));
	m_hBitmapSit = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP4));
	m_hBitmapSitYes = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP9));

	dlg = NULL;
	dlg_p = NULL;
	dlg_lp = NULL;
}

CMyDlgMain::~CMyDlgMain()
{
	
}

void CMyDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_edtname);
	DDX_Control(pDX, IDC_LIST3, m_lstonline);
	DDX_Text(pDX, IDC_EDIT2, m_chatstr);
	DDX_Control(pDX, IDC_LIST4, m_chatbox);
	DDX_Control(pDX, IDC_LIST5, m_friendlist);
}


BEGIN_MESSAGE_MAP(CMyDlgMain, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON24, &CMyDlgMain::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON39, &CMyDlgMain::OnBnClickedButton39)
	ON_BN_CLICKED(IDC_BUTTON40, &CMyDlgMain::OnBnClickedButton40)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON38, &CMyDlgMain::OnBnClickedButton38)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(UM_CREATEROOMMSG,&CMyDlgMain::CreateRoomDlg)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDlgMain::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON14, &CMyDlgMain::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON10, &CMyDlgMain::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON13, &CMyDlgMain::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlgMain::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON25, &CMyDlgMain::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyDlgMain::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON17, &CMyDlgMain::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON11, &CMyDlgMain::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON15, &CMyDlgMain::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyDlgMain::OnBnClickedButton3)
	ON_MESSAGE(UM_CREATERESROOMMSG,&CMyDlgMain::CreateResRoomDlg) //结算弹窗
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &CMyDlgMain::OnNMRClickList3)
	ON_MESSAGE(UM_ISGETFRIENDMSG,&CMyDlgMain::IsAgreeFriend) //自定义弹出是否同意添加好友窗口
	ON_MESSAGE(UM_LOOKPERSONMSG,&CMyDlgMain::IsLookPersonDlg)
	ON_NOTIFY(NM_RCLICK, IDC_LIST5, &CMyDlgMain::OnNMRClickList5)
	ON_MESSAGE(UM_PERSONCHATMSG,&CMyDlgMain::PersonChatDlg) //私信
	ON_MESSAGE(UM_PLAYERPLAYMSG,&CMyDlgMain::PlayerPlayDlg) //私信
	ON_BN_CLICKED(IDC_BUTTON41, &CMyDlgMain::OnBnClickedButton41)
END_MESSAGE_MAP()


// CMyDlgMain 消息处理程序


void CMyDlgMain::OnPaint()
{
	CPaintDC dc(this); 
	// device context for painting
    // TODO: 在此处添加消息处理程序代
	// 不为绘图消息调用 CDialogEx::OnPaint()

	CDC *cDC=this->GetDC();
	CDC m_bgcDC;
	m_bgcDC.CreateCompatibleDC(cDC); 
	
	m_bgcDC.SelectObject(m_hBitmap1); 
	cDC->BitBlt(0,0,2500,1208,&m_bgcDC,0,0,SRCCOPY); 


	//遍历链表加入Bitmap
	int i=75;
	int j=65;
	list<Room*>::iterator ite=m_listtable.begin();
	while(ite != m_listtable.end())
	{
		(*ite)->point.x=i;
		(*ite)->point.y=j;
	     
		 if(i<=700)
		 {
			 m_bgcDC.SelectObject(m_hBitmapW); 
		     cDC->BitBlt((*ite)->point.x,(*ite)->point.y,200,189,&m_bgcDC,0,0,SRCAND); 

		     m_bgcDC.SelectObject(m_hBitmapB); 
		     cDC->BitBlt((*ite)->point.x,(*ite)->point.y,200,189,&m_bgcDC,0,0,SRCPAINT); 
		     i=i+265;
		 }
		 if(i>700)
		 {
			 i=75;
			 j=j+320;
		 }
		 ++ite;
	}

	//桌1
	((CButton*)GetDlgItem(IDC_BUTTON24))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON2))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON14))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON10))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON13))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON1))->SetBitmap(m_hBitmapSit);
	
	((CButton*)GetDlgItem(IDC_BUTTON3))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON4))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON5))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON6))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON7))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON8))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON9))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON11))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON12))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON15))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON16))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON17))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON18))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON19))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON20))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON21))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON22))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON23))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON25))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON26))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON27))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON28))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON29))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON30))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON31))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON32))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON33))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON34))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON35))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON37))->SetBitmap(m_hBitmapSit);
	((CButton*)GetDlgItem(IDC_BUTTON36))->SetBitmap(m_hBitmapSit);

	ReleaseDC(cDC);

}



BOOL CMyDlgMain::OnInitDialog()
{
	m_font.CreatePointFont(150,_T("宋体"));
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC)->SetFont(&m_font);
	UpdateData(FALSE);

	for(int i=0;i<6;i++)
	{
		Room* m_room;
		m_room= new Room;
		m_room->m_curplayer=0;
		m_room->m_maxplayer=6;
		list<Player>::iterator ite=m_room->m_listplayer.begin();
		while(ite!=m_room->m_listplayer.end())
		{
			(*ite).m_grade=0;
			(*ite).m_role=1;
		
		}
		
		m_listtable.push_back(m_room);
	}
	
	CDialogEx::OnInitDialog();
	return true;
}


HBRUSH CMyDlgMain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_STATIC|CTLCOLOR_EDIT )
	  {
		  pDC->SetBkMode(TRANSPARENT);//设置背景透明
		  pDC->SetTextColor(RGB(203,16,26));//设置字体为黄色
		 
		  return (HBRUSH)::GetStockObject(NULL_BRUSH);
	 }
    
	return hbr;
}


void CMyDlgMain::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

//---------------------------------------------------------------------------------------------


//编辑个人信息弹窗
void CMyDlgMain::OnBnClickedButton39()
{
	// TODO: 在此添加控件通知处理程序代码
	if(dlg_p == NULL)
	{
		dlg_p = new PersonDlg;
		dlg_p->Create(IDD_DIALOG4);
	}
	dlg_p->ShowWindow(SW_SHOW);

}


//点击退出大厅
void CMyDlgMain::OnBnClickedButton40()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_QUIT_RQ sqr;
	sqr.m_nType = _DEF_PROTOCOL_QUIT_RQ;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sqr.m_szName,sizeof(sqr.m_szName),0,0);

	theApp.GetKernel()->SendData((char*)&sqr,sizeof(sqr));
}

//重写关闭
void CMyDlgMain::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDOK);
	CDialogEx::OnClose();
}

//发送消息按钮
void CMyDlgMain::OnBnClickedButton38()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	STRU_CHAT_RQ scr;
	scr.m_nType = _DEF_PROTOCOL_CHAT_RQ;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,scr.m_szName,sizeof(scr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_chatstr,-1,scr.m_chatbuf,sizeof(scr.m_chatbuf),0,0);

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
	GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));

	theApp.GetKernel()->SendData((char*)&scr,sizeof(scr));
}

//自定义消息 点击座位弹框
afx_msg LRESULT CMyDlgMain::CreateRoomDlg(WPARAM ,LPARAM)
{
	if(dlg == NULL)
	{
		dlg = new CRoomDlgg;
		dlg->Create(IDD_DIALOG1);
	}
	dlg->ShowWindow(SW_SHOW);

	return 0;
}


struct PlayerSortNode
{
	char m_playername[_DEF_SIZE];
	int m_playerscore;
};
PlayerSortNode m_playerSort[_DEF_ROOMNUM];


//结算窗口弹窗
afx_msg LRESULT CMyDlgMain::CreateResRoomDlg(WPARAM w,LPARAM l)
{
	memset(m_playerSort,0,sizeof(m_playerSort));
	for(int j=0;j<_DEF_ROOMNUM;j++)
	{
		m_playerSort[j].m_playerscore = -1;
	}

	if(((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg == NULL)
	{
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg = new ResultDlgg;
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg->Create(IDD_DIALOG2);
	}
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg->ShowWindow(SW_SHOW);
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg->m_reslultlist.DeleteAllItems();
	
	int count = ((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.GetItemCount();
	for(int index = 0;index<count;index++)
	{
		CString player_name = ((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.GetItemText(index,0);
		CString player_score = ((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.GetItemText(index,1);
		
		char name[_DEF_SIZE] = {0};
		WideCharToMultiByte(CP_ACP,0,player_name,-1,name,sizeof(name),0,0);
		char score[_DEF_SIZE] = {0};
		WideCharToMultiByte(CP_ACP,0,player_score,-1,score,sizeof(score),0,0);
		int player_score_int = atoi(score);

		if(m_playerSort[0].m_playerscore == -1)
		{
			strncpy_s(m_playerSort[0].m_playername,name,_DEF_SIZE);
			m_playerSort[0].m_playerscore = player_score_int;
		}
		else if(m_playerSort[0].m_playerscore != -1)
		{
			//排序
			for(int p=0;p<_DEF_ROOMNUM;p++)
			{
				if(m_playerSort[p].m_playerscore <= player_score_int)
				{
					for(int q=4;q>=p;q--)
					{
						if(m_playerSort[q].m_playerscore != -1)
						{
							strncpy_s(m_playerSort[q+1].m_playername,m_playerSort[q].m_playername,_DEF_SIZE);
							m_playerSort[q+1].m_playerscore = m_playerSort[q].m_playerscore;
						}
					}
					strncpy_s(m_playerSort[p].m_playername,name,_DEF_SIZE);
					m_playerSort[p].m_playerscore = player_score_int;
					break;
				}
			}
		}
	}

	//显示
	CString player_name; 
	CString player_score;
	for(int index = 0;index<count;index++)
	{
		player_name = (char*)m_playerSort[index].m_playername;
		char score_[_DEF_SIZE] = {0};
		_itoa_s(m_playerSort[index].m_playerscore,score_,10);
		player_score = (char*)score_;
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg->m_reslultlist.InsertItem(index,player_name);
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->resdlg->m_reslultlist.SetItemText(index,1,player_score);
	}
	
	return 0;
}



CString friend_str;

void CMyDlgMain::OnNMRClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	//1.判断列表控件中是否为空，空不做响应
	//2.不为空判断是否有选项被选中，没有选中不做响应
	//3.有选中开始加载菜单，如果加载菜单句柄为空不做响应
	//4.获取鼠标点击的位置在当前的位置中弹出右键菜单
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	 //在列表为空时不显示
    if (m_lstonline.GetItemCount() <= 0)
    {
        return;
    }
    //没有列被选中不显示
    if (m_lstonline.GetSelectedCount() > 0)
    {
		
		int index=m_lstonline.GetSelectionMark();
		if(GetF_dlg == NULL)
		{
			GetF_dlg = new CGetfriend;
			GetF_dlg->Create(IDD_DIALOG6);
		}
		GetF_dlg->ShowWindow(SW_SHOW);

		friend_str=m_lstonline.GetItemText(index,0);
      
    }
    else
    {
        return;
    }

}


afx_msg LRESULT CMyDlgMain::IsAgreeFriend(WPARAM w,LPARAM l)
{
	if(m_isagreefriend == NULL)
	{
		m_isagreefriend = new CIsAgreeFriend;
		m_isagreefriend->Create(IDD_DIALOG5);
	}
	m_isagreefriend->ShowWindow(SW_SHOW);
	return 0;
}



afx_msg LRESULT CMyDlgMain::IsLookPersonDlg(WPARAM w,LPARAM l)
{
	if(dlg_lp == NULL)
	{
		dlg_lp = new LookPersonDlg;
		dlg_lp->Create(IDD_DIALOG7);
	}

	dlg_lp->ShowWindow(SW_SHOW);

	return 0;
}


afx_msg LRESULT CMyDlgMain::PersonChatDlg(WPARAM w,LPARAM l)
{
	if(dlg_pc == NULL)
	{
		dlg_pc = new PersonChat;
		dlg_pc->Create(IDD_DIALOG8);
	}
	dlg_pc->ShowWindow(SW_SHOW);
	return 0;
}

extern CString playerfilename;
afx_msg LRESULT CMyDlgMain::PlayerPlayDlg(WPARAM ,LPARAM)
{
	dlg_pc->m_player.put_URL(playerfilename);
	return 0;
}

CString delete_str;
int delete_id;
void CMyDlgMain::OnNMRClickList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	  if (m_friendlist.GetItemCount() <= 0)
    {
        return;
    }
    //没有列被选中不显示
	  if (m_friendlist.GetSelectedCount() > 0)
    {
		
		int index=m_friendlist.GetSelectionMark();
		delete_id=index;
		if(GetF_dlg == NULL)
		{
			GetF_dlg = new CGetfriend;
			GetF_dlg->Create(IDD_DIALOG6);
		}
		GetF_dlg->ShowWindow(SW_SHOW);

		delete_str=m_friendlist.GetItemText(index,0);
      
    }
    else
    {
        return;
    }
}

//--------------------------------------------------------------------------------------------------

int sitidc;
int sitid;

//房间1的1号座位 点击座位坐下
void CMyDlgMain::OnBnClickedButton24()
{
	// TODO: 在此添加控件通知处理程序代码
    
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=1; //房间编号
	sgr.m_sitid=1;
	sgr.m_buttonid=IDC_BUTTON24;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//房间1的2号座位 点击座位坐下
void CMyDlgMain::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=1; //房间编号
	sgr.m_sitid=2;
	sgr.m_buttonid=IDC_BUTTON2;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//房间1的3号座位 点击座位坐下
void CMyDlgMain::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=1; //房间编号
	sgr.m_sitid=3;
	sgr.m_buttonid=IDC_BUTTON14;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//1-4
void CMyDlgMain::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=1; //房间编号
	sgr.m_sitid=4;
	sgr.m_buttonid=IDC_BUTTON10;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//1-5
void CMyDlgMain::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=1; //房间编号
	sgr.m_sitid=5;
	sgr.m_buttonid=IDC_BUTTON13;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//1-6
void CMyDlgMain::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=1; //房间编号
	sgr.m_sitid=6;
	sgr.m_buttonid=IDC_BUTTON1;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//2-1
void CMyDlgMain::OnBnClickedButton25()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=2; //房间编号
	sgr.m_sitid=1;
	sgr.m_buttonid=IDC_BUTTON25;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//2-2
void CMyDlgMain::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=2; //房间编号
	sgr.m_sitid=2;
	sgr.m_buttonid=IDC_BUTTON4;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//2-3
void CMyDlgMain::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=2; //房间编号
	sgr.m_sitid=3;
	sgr.m_buttonid=IDC_BUTTON17;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//2-4
void CMyDlgMain::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=2; //房间编号
	sgr.m_sitid=4;
	sgr.m_buttonid=IDC_BUTTON11;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//2-5
void CMyDlgMain::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=2; //房间编号
	sgr.m_sitid=5;
	sgr.m_buttonid=IDC_BUTTON15;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}

//2-6
void CMyDlgMain::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETINTOROOM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
	sgr.m_roomid=2; //房间编号
	sgr.m_sitid=6;
	sgr.m_buttonid=IDC_BUTTON3;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);

	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	sitidc = sgr.m_buttonid;sitid = sgr.m_sitid;
}






void CMyDlgMain::OnBnClickedButton41()
{
	// TODO: 在此添加控件通知处理程序代码
	STRU_GETTEAM_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETTEAM_RQ;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_szName,sizeof(sgr.m_szName),0,0);
	theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
}
