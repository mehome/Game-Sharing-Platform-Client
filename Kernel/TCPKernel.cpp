#include "stdafx.h"
#include "TCPKernel.h"
#include "1027Client.h"
#include <WinBase.h>
#include <Commctrl.h>

#pragma comment(lib,"Kernel32.lib")

TCPKernel::TCPKernel()
{
	m_pTcpNet = new TCPNet(this);

}

TCPKernel::~TCPKernel()
{
	if(m_pTcpNet)
	{
		delete m_pTcpNet;
		m_pTcpNet = NULL;
	}
}

BEGIN_PROTOCOL_MAP
	PM(_DEF_PROTOCOL_REGISTER_RS,&TCPKernel::RegisterRs)
	PM(_DEF_PROTOCOL_LOGIN_RS,&TCPKernel::LoginRs)
	PM(_DEF_PROTOCOL_ONLINE_RS,&TCPKernel::RecvOnlineListRs)
	PM(_DEF_PROTOCOL_QUIT_RS,&TCPKernel::QuitRs)
	PM(_DEF_PROTOCOL_CHAT_RS,&TCPKernel::ChatRs)
	PM(_DEF_PROTOCOL_GETROOM_RS,&TCPKernel::GetRoomRs) //��ȡ������Ϣ�ظ�
	PM(_DEF_PROTOCOL_QUITROOM_RS,&TCPKernel::QuitRoomRs) //�˳�����ظ�
	PM(_DEF_PROTOCOL_CHATROOM_RS,&TCPKernel::ChatRoomRs) //��������
	PM(_DEF_PROTOCOL_GETPOINT_RS,&TCPKernel::GetPointRs)
	PM(_DEF_PROTOCOL_START_RS,&TCPKernel::StartRs) //��ʼ
	PM(_DEF_PROTOCOL_GETSIT_RS,&TCPKernel::GetSitRs)
	PM(_DEF_PROTOCOL_READY_RS,&TCPKernel::ReadyRs) //׼�� ȡ��׼��
	PM(_DEF_PROTOCOL_GAMEOVER_RS,&TCPKernel::GameOverRs) //�����˶��¶���Ϸ����
	PM(_DEF_PROTOCOL_ALTERPERSON_RS,&TCPKernel::AlterPersonRs) //�޸ĸ�������
	PM(_DEF_PROTOCOL_GETFRIEND_RS,&TCPKernel::GetFriendRs) //��Ӻ���
	PM(_DEF_PROTOCOL_GETLISTFRIEND_RS,&TCPKernel::GetListFriendRs)
	PM(_DEF_PROTOCOL_LOOKPERSON_RS,&TCPKernel::LookPersonRs) //�鿴����
	PM(_DEF_PROTOCOL_DELETEFRIEND_RS,&TCPKernel::DeleteFriendRs)
	PM(_DEF_PROTOCOL_PERSONCHAT_RS,&TCPKernel::PersonChatRs) //˽��
	PM(_DEF_PROTOCOL_INVITEPLAYER_RS,&TCPKernel::InvitePlayerRs) //������Ϸ
	PM(_DEF_PROTOCOL_INVITEPLAYERYN_RS,&TCPKernel::InvitePlayerYnRs)
	PM(_DEF_PROTOCOL_INVITEVEDIO_RQ,&TCPKernel::InviteVedioRq) //������Ƶ
	PM(_DEF_PROTOCOL_INVITEVEDIO_RS,&TCPKernel::InviteVedioRs) 
	PM(_DEF_PROTOCOL_VIDEOSTREAMINFO_RQ,&TCPKernel::GetVedioStreamInfo)
	PM(_DEF_PROTOCOL_VIDEOSTREAM_RQ,&TCPKernel::GetVedioStream)
	PM(_DEF_PROTOCOL_SENDFILE_RS,&TCPKernel::SendFileRs) //�ļ�
	PM(_DEF_PROTOCOL_SENDFILEBLOCK_RS,&TCPKernel::SendFileBlockRs) //�����ļ���
	PM(_DEF_PROTOCOL_RECVFILEBLOCK_RS,&TCPKernel::RecvFileBlockRs) //�����ļ���
	PM(_DEF_PROTOCOL_GETTEAM_RS,&TCPKernel::GetTeamRs) 

END_PROTOCOL_MAP


bool TCPKernel::Open()
{

	if(!m_pTcpNet->InitNetWork())
		return false;
	return true;

}

void TCPKernel::Close()
{
	m_pTcpNet->UnInitNetWork();
	
}

bool TCPKernel::SendData(char* szbuf,int nlen)
{
	if(!m_pTcpNet->SendData(szbuf,nlen))
		return false;
	return true;
}

void TCPKernel::DealData(char* szbuf)
{
	 //��������---Э��ӳ���
	PackType *pType = (PackType *)szbuf;
	int i = 0;
	while(1)
	{
		if(m_ProtocolMapEntries[i].m_nType ==  *pType)
		{
			(this->*m_ProtocolMapEntries[i].m_pfun)(szbuf);
			break;
		}
		else if(m_ProtocolMapEntries[i].m_nType ==0 || m_ProtocolMapEntries[i].m_pfun ==0)
			break;

		i++;
	}

}

//------------------------------------------------------------------------------------------

CString dlgname;

//����ע��ظ�
void TCPKernel::RegisterRs(char* szbuf)
{
	STRU_REGISTER_RS *psrr = (STRU_REGISTER_RS*)szbuf;
	TCHAR *pSzResult = NULL;
	if(psrr->m_szResult == _register_telexists)
		pSzResult = _T("_register_telexists");
	else if(psrr->m_szResult == _register_userexists)
		pSzResult = _T("_register_userexists");
	else if(psrr->m_szResult == _register_success)
	{
		pSzResult = _T("_register_success");
		STRU_INSERTPERSON_RQ sir;
		sir.m_nType = _DEF_PROTOCOL_INSERTPERSON_RQ;
		strcpy_s(sir.m_szName,psrr->m_szName);
		sir.m_tel = psrr->m_tel;
		theApp.GetKernel()->SendData((char*)&sir,sizeof(sir));
	}

	AfxMessageBox(pSzResult);
}


//���յ�¼�ظ�
void TCPKernel::LoginRs(char* szbuf)
{
	STRU_LOGIN_RS *psrr = (STRU_LOGIN_RS*)szbuf;
	TCHAR *pSzResult = NULL;
	if(psrr->m_szResult == _login_usernoexists)
	{
		pSzResult = _T("_login_usernoexists");
			AfxMessageBox(pSzResult);
	}
	else if(psrr->m_szResult == _login_passworderr)
	{
		pSzResult = _T("_login_passworderr");
			AfxMessageBox(pSzResult);
	}
	else if(psrr->m_szResult == _login_success)
	{	
		STRU_SHOWPLAYER_RQ ssr;
	    ssr.m_nType = _DEF_PROTOCOL_ONLINE_RQ;
	    theApp.GetKernel()->SendData((char*)&ssr,sizeof(ssr));

	    DWORD dw = GetLastError();
		dlgname = (char*)psrr->m_szName;
		theApp.m_pMainWnd->PostMessage(UM_LOGINMSG,0,0);
      
	}

	//������ҽ�����Ϸ��ͼƬ������ť���ؾ����
	Sleep(500);
	for(int i=0;i<_DEF_PLAYER;i++)
	{
		if(psrr->sit[i] != 0)
			((CButton*)theApp.m_pMainWnd->GetDlgItem(psrr->sit[i]))->
				SetBitmap(((CMyDlgMain*)theApp.m_pMainWnd)->m_hBitmapSitYes);
	}

}


//����
void TCPKernel::ChatRs(char* szbuf)
{
	STRU_CHAT_RS* scr = (STRU_CHAT_RS*)szbuf;
	DWORD dw = GetLastError();

	//LPCTSTR chat;
	CString chat;
	chat = scr->m_szName;
	((CMyDlgMain*)theApp.m_pMainWnd)->m_chatbox.AddString(chat);
	chat = scr->m_chatbuf;
	((CMyDlgMain*)theApp.m_pMainWnd)->m_chatbox.AddString(chat);

}

//�˳�
void TCPKernel::QuitRs(char* szbuf)
{
	STRU_QUIT_RS *ssr = (STRU_QUIT_RS*)szbuf;

	if(ssr->szResult == _quit_success)
	{
		((CMyDlgMain*)theApp.m_pMainWnd)->OnClose();
	}

}

//����
void TCPKernel::RecvOnlineListRs(char* szbuf)
{
	STRU_SHOWPLAYER_RS *ssr = (STRU_SHOWPLAYER_RS*)szbuf;
	
	if(!((CMyDlgMain*)theApp.m_pMainWnd)->m_lstonline.DeleteAllItems())
			return ;
	
	for(int i=0;i<_DEF_PLAYER;i++)
	{
		if(ssr->online[i].m_szName[0] != NULL)
		{
			WCHAR szname[_DEF_SIZE] = {0};
			MultiByteToWideChar(CP_ACP,0,ssr->online[i].m_szName,-1,szname,sizeof(szname));
			((CMyDlgMain*)theApp.m_pMainWnd)->m_lstonline.InsertItem(0,szname);
		}
		else break;
	}

	return ;
}


int inroom_id = -1;


//���ܷ�����Ϣ��ȡ�ظ���
void TCPKernel::GetRoomRs(char* szbuf)
{
	 STRU_GETINTOROOM_RS* psgr=(STRU_GETINTOROOM_RS*)szbuf;
	 TCHAR *pSzResult = NULL;
	 inroom_id = psgr->m_roomid;
	 
	 if(psgr->szResult == _getroominfo_success)
	 {
		 theApp.m_pMainWnd->PostMessage(UM_CREATEROOMMSG,0,0);
		 
		 Sleep(1000);
		 
		 if( ((CMyDlgMain*)theApp.m_pMainWnd)->dlg != NULL )
		 {
			 ((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.DeleteAllItems();
			 //�ڿؼ������������������������
			 for(int i=0;i<_DEF_ROOMNUM;i++)
			 {
				if(psgr->inroom[i].m_szName[0] != NULL)
				{
					WCHAR szname[_DEF_SIZE] = {0};
					MultiByteToWideChar(CP_ACP,0,psgr->inroom[i].m_szName,-1,szname,sizeof(szname));
					((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.InsertItem(0,szname);
				}
				else break;
			 }
		 }

	 }
	 else if(psgr->szResult == _getroominfo_fail)
	 {
		 pSzResult = _T("_getroominfo_fail");
		 AfxMessageBox(pSzResult);
	 }
 }


//�˳�����ظ�
void TCPKernel::QuitRoomRs(char* szbuf)
{
	STRU_QUITROOM_RS* psgr=(STRU_QUITROOM_RS*)szbuf;

	char my_name[_DEF_SIZE] = {0};
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,my_name,sizeof(my_name),0,0);
	if(strncmp(psgr->m_szName,my_name,_DEF_SIZE)==0 )
		inroom_id = -1;

	TCHAR *pSzResult = NULL;
	if(psgr->szResult == _quit_success)
	{
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.DeleteAllItems();
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->OnClose();
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->flag_ready = false;

	}
	else if(psgr->szResult == _quit_others)
	{
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.DeleteAllItems();
		//��ռ����������������������
		for(int i=0;i<_DEF_ROOMNUM;i++)
		{
			if(psgr->inroom[i].m_szName[0] != NULL)
			{
				WCHAR szname[_DEF_SIZE] = {0};
				MultiByteToWideChar(CP_ACP,0,psgr->inroom[i].m_szName,-1,szname,sizeof(szname));
				((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.InsertItem(0,szname);
			}
			else break;
		}
	}
	else 
	{
		pSzResult = _T("_quitroom_fail");
		AfxMessageBox(pSzResult);
	}
}


//��������
void TCPKernel::ChatRoomRs(char* szbuf)
{
	STRU_CHATROOM_RS* scr = (STRU_CHATROOM_RS*)szbuf;
	DWORD dw = GetLastError();
	
	CString chat;
	chat = scr->m_szName;
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_chatroombox.AddString(chat);
	chat = scr->m_chatbuf;
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_chatroombox.AddString(chat);

	if(scr->m_istrue == true)
	{
		char result[_DEF_SIZE];
		memset(result,0,sizeof(result));
		strcat_s(result,scr->m_szName);
		strcat_s(result,"����Ѿ��¶ԣ�");
		chat = result;
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_chatroombox.AddString(chat);

		char name[_DEF_SIZE] = {0};
		char d_name[_DEF_SIZE] = {0};
		for(int i=0;i<strlen(scr->m_szName);i++)
		{
			if(scr->m_szName[i] != ' ')
			{
				name[i] = scr->m_szName[i];
			}
			else if(scr->m_szName[i] == ' ')
			{
				name[i] = '\0';
				break;
			}
		}
		for(int i=0;i<strlen(scr->m_dszName);i++)
		{
			if(scr->m_dszName[i] != ' ')
			{
				d_name[i] = scr->m_dszName[i];
			}
			else if(scr->m_dszName[i] == ' ')
			{
				d_name[i] = '\0';
				break;
			}
		}


		//�����Ҷ�Ӧ��������ӷ�
		int index;
		for(index = 0;index<(((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.GetItemCount());index++)
		{
			CString player_name = ((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.GetItemText(index,0);
			char* player_name_c;
			USES_CONVERSION;
			player_name_c=T2A(player_name);
			if(strncmp(player_name_c,name,_DEF_SIZE) == 0 )
			{
				//���ҵ�������ȥ�Ҷ�Ӧ���ֵķ���
				CString score = ((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.GetItemText(index,1);
				char score2[_DEF_SIZE] = {0};
				WideCharToMultiByte(CP_ACP,0,score,-1,score2,sizeof(score2),0,0);
				_itoa_s(scr->m_score,score2,10);
				score = (char*)score2;
				((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.SetItemText(index,1,score);
				
			}
			if( strncmp(player_name_c,d_name,_DEF_SIZE) == 0)
			{
				//���ҵ�������ȥ�Ҷ�Ӧ���ֵķ���
				CString score = ((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.GetItemText(index,1);
				char score2[_DEF_SIZE] = {0};
				WideCharToMultiByte(CP_ACP,0,score,-1,score2,sizeof(score2),0,0);
				_itoa_s(scr->m_dscore,score2,10);
				score = (char*)score2;
				((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.SetItemText(index,1,score);
			
			
			}
		}

	}
	//����chatbuf�ڷ�������
}


//�յ�
void TCPKernel::GetPointRs(char* szbuf)
{
	STRU_GETPOINT_RS * psgr = (STRU_GETPOINT_RS*)szbuf;

	CClientDC dc(((CMyDlgMain*)theApp.m_pMainWnd)->dlg);
	CPen pen(PS_SOLID,5,psgr->color);   //  ����һ������	
	dc.SelectObject(pen);
	dc.MoveTo(psgr->movepoint);
	dc.LineTo(psgr->point);

}


char Drawplayername[_DEF_SIZE];
static bool isset_score = false;

//��ʼ
void TCPKernel::StartRs(char* szbuf)
{
	STRU_START_RS * psgr = (STRU_START_RS*)szbuf;
	TCHAR *pSzResult = NULL;
	strncpy_s(Drawplayername,psgr->szDrawplayername,_DEF_SIZE);

	if(psgr->szResult == _start_people)
	{
		pSzResult = _T("����������Ҳſ��Կ�ʼ��Ϸ��");
		AfxMessageBox(pSzResult);
	}
	else if(psgr->szResult == _start_fail)
	{
		pSzResult = _T("�������û��׼����");
		AfxMessageBox(pSzResult);
	}
	else if(psgr->szResult == _start_success)
	{
		//����
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->GetDlgItem(IDC_STATIC)->ShowWindow(FALSE);
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->GetDlgItem(IDC_STATIC)->ShowWindow(TRUE);

		//����˭��˭���ܻ�
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->flag = false;
		char m_szName[_DEF_SIZE] = {0};
		WideCharToMultiByte(CP_ACP,0,dlgname,-1,m_szName,sizeof(m_szName),0,0);
		if(strncmp(m_szName,Drawplayername,_DEF_SIZE) == 0)
		{
			((CMyDlgMain*)theApp.m_pMainWnd)->dlg->flag = true;
		}

		CString chat;
		chat = psgr->m_chatbuf;
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_chatroombox.AddString(chat);

		if(isset_score == false)
		{
			for(int i=0;i<psgr->m_curplayer;i++)
			{
				((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_inroomlst.SetItemText(i,1,_T("0"));
			}
			isset_score = true;
		}

		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_myclock = 99;
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->SetTimer(START_GAME_TIMER_ID,1000,NULL);
	}
	else if(psgr->szResult == _start_end)
	{
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_myclock=0;
		//���㴰�ڵ���
		theApp.m_pMainWnd->PostMessage(UM_CREATERESROOMMSG,0,0);
		
		//����־�û�
		isset_score = false;
		memset(Drawplayername,0,_DEF_SIZE);

		STRU_READY_RQ srr;
		srr.m_nType = _DEF_PROTOCOL_READY_RQ;
		srr.flag_ready = false; //�������ȡ��׼��
		srr.m_roomid = inroom_id;
		((CButton*)((CMyDlgMain*)theApp.m_pMainWnd)->dlg->GetDlgItem(IDC_BUTTON9))->
			SetBitmap(((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_hBitmapReady);
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->flag_ready = false;
		theApp.GetKernel()->SendData((char*)&srr,sizeof(srr));
	}
}


//����
void TCPKernel::GetSitRs(char* szbuf)
{
	STRU_GETSIT_RS * psgr = (STRU_GETSIT_RS*)szbuf;
	if(psgr->flag == true)
		((CButton*)theApp.m_pMainWnd->GetDlgItem(psgr->buttonid))->
			SetBitmap(((CMyDlgMain*)theApp.m_pMainWnd)->m_hBitmapSitYes);

	if(psgr->flag == false)
		((CButton*)theApp.m_pMainWnd->GetDlgItem(psgr->buttonid))->
			SetBitmap(((CMyDlgMain*)theApp.m_pMainWnd)->m_hBitmapSit);
}



//׼�� ȡ��׼��
void TCPKernel::ReadyRs(char* szbuf)
{
	STRU_READY_RS * psgr = (STRU_READY_RS*)szbuf;
	if(psgr->flag_ready == true)
	{
		((CButton*)((CMyDlgMain*)theApp.m_pMainWnd)->dlg->GetDlgItem(IDC_BUTTON9))->
			SetBitmap(((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_hBitmapWait); //���ȡ��׼��
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->flag_ready = true; //�Ѿ�׼��
	}
	if(psgr->flag_ready == false)
	{
		((CButton*)((CMyDlgMain*)theApp.m_pMainWnd)->dlg->GetDlgItem(IDC_BUTTON9))->
			SetBitmap(((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_hBitmapReady);
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg->flag_ready = false;
	}
}


//�������˲¶� ��Ϸ����
void TCPKernel::GameOverRs(char* szbuf)
{
	STRU_GAMEOVER_RS * psgr = (STRU_GAMEOVER_RS*)szbuf;
	((CMyDlgMain*)theApp.m_pMainWnd)->dlg->m_myclock=0;
}


//�޸ĸ�������
void TCPKernel::AlterPersonRs(char* szbuf)
{
	STRU_ALTERPERSON_RS * psgr = (STRU_ALTERPERSON_RS*)szbuf;
	TCHAR *pSzResult = NULL;
	if(psgr->szResult == _alterperson_success)
	{
		pSzResult = _T("_alterperson_success");
	}
	else if(psgr->szResult == _alterperson_pwfail)
	{
		pSzResult = _T("_alterperson_pwfail");
	}

	AfxMessageBox(pSzResult);
}


//��Ӻ���
char m_friendname[_DEF_SIZE];
void TCPKernel::GetFriendRs(char *szbuf)
{
	STRU_GETFRIEND_RS * psgr=(STRU_GETFRIEND_RS*)szbuf;
	TCHAR *pSzResult = NULL;
	if(psgr->m_isagree ==2)
	{
		strcpy_s(m_friendname,psgr->m_szName);
		theApp.m_pMainWnd->PostMessage(UM_ISGETFRIENDMSG,0,0);
	}
	if(psgr->m_isagree ==0)
	{
		//�Ѻ��ѵ��������ں����б���
		WCHAR szname[_DEF_SIZE] = {0};
		MultiByteToWideChar(CP_ACP,0,psgr->m_friendName,-1,szname,sizeof(szname));
		((CMyDlgMain*)theApp.m_pMainWnd)->m_friendlist.InsertItem(0,szname);

	}
	if(psgr->m_isagree ==1)
	{
		//�Է��ܾ����1����  Messagebox
		pSzResult = _T("add friend failed");
			AfxMessageBox(pSzResult);

	}


}



void TCPKernel::GetListFriendRs(char *szbuf)
{
	STRU_GETLISTFRIEND_RS * psgr=(STRU_GETLISTFRIEND_RS*)szbuf;

	WCHAR szname[_DEF_SIZE] = {0};
	MultiByteToWideChar(CP_ACP,0,psgr->m_friendName,-1,szname,sizeof(szname));
	((CMyDlgMain*)theApp.m_pMainWnd)->m_friendlist.InsertItem(0,szname);


}


STRU_LOOKPERSON_RS g_slr;
//�鿴����
void TCPKernel::LookPersonRs(char* szbuf)
{
	STRU_LOOKPERSON_RS* slr=(STRU_LOOKPERSON_RS*)szbuf;
	g_slr.m_Day = slr->m_Day;
	g_slr.m_level = slr->m_level;
	g_slr.m_Month = slr->m_Month;
	g_slr.m_nType = slr->m_nType;
	g_slr.m_score = slr->m_score;
	strncpy_s(g_slr.m_szWantLookName,slr->m_szWantLookName,_DEF_SIZE);
	g_slr.m_winpercent = slr->m_winpercent;
	g_slr.m_Year = slr->m_Year;
	strncpy_s(g_slr.p_id,slr->p_id,_DEF_SIZE);
	g_slr.sex = slr->sex;

	theApp.m_pMainWnd->PostMessage(UM_LOOKPERSONMSG,0,0);
}


extern int delete_id;
void TCPKernel::DeleteFriendRs(char* szbuf)
{
	STRU_DELETEFRIEND_RS * psdr=(STRU_DELETEFRIEND_RS*)szbuf;
	if(psdr->is_delete == true)
	{
		WCHAR szname[_DEF_SIZE] = {0};
		MultiByteToWideChar(CP_ACP,0,psdr->m_deleteName,-1,szname,sizeof(szname));
		((CMyDlgMain*)theApp.m_pMainWnd)->m_friendlist.DeleteItem(delete_id);

	}

}


extern CString delete_str;
//˽��
void TCPKernel::PersonChatRs(char* szbuf)
{
	STRU_PERSONCHAT_RS * psdr=(STRU_PERSONCHAT_RS*)szbuf;

	//��ȡ������
	char name[_DEF_SIZE] = {0};
	for(int i=0;i<_DEF_SIZE;i++)
	{
		if(psdr->m_szName[i]!=' ')
			name[i] = psdr->m_szName[i];
		else 
		{
			name[i] = '\0';
			break;
		}
	}

	if(strncmp(psdr->m_szName,name,_DEF_SIZE) != 0)
	{
		delete_str = name;
	}

	theApp.m_pMainWnd->PostMessage(UM_PERSONCHATMSG,0,0);

	Sleep(1000);
		 
	if( ((CMyDlgMain*)theApp.m_pMainWnd)->dlg_pc != NULL )
	{
		CString chat;
		chat = psdr->m_szName;
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg_pc->m_.AddString(chat);
		chat = psdr->m_chatbuf;
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg_pc->m_.AddString(chat);
	}
}


bool is_invite = false;
CString invite_name;
int invite_roomid;

//������Ϸ
void TCPKernel::InvitePlayerRs(char* szbuf)
{
	STRU_INVITEPLAYER_RS * psir=(STRU_INVITEPLAYER_RS*)szbuf;
	if(psir->szResult == _inviteplayer_younotinroom)
	{
		TCHAR *pSzResult = NULL;
		pSzResult = _T("�㶼���ڷ����� �㲻��������ˣ�");
		AfxMessageBox(pSzResult);
	}
	else if(psir->szResult == _inviteplayer_success)
	{
		is_invite = true;
		invite_name = (char*)psir->m_szName;
		invite_roomid = psir->m_roomid;
		theApp.m_pMainWnd->PostMessage(UM_ISGETFRIENDMSG,0,0);
	
		Sleep(1000);
		if( ((CMyDlgMain*)theApp.m_pMainWnd)->m_isagreefriend != NULL )
		{
			is_invite = false;
		}
	}
}

void TCPKernel::InvitePlayerYnRs(char* szbuf)
{
	STRU_INVITEPLAYERYN_RS * psir=(STRU_INVITEPLAYERYN_RS*)szbuf;
	TCHAR *pSzResult = NULL;
	if(psir->szResult == _inviteplayer_refuse)
	{
		pSzResult = _T("�㱻�ܾ��� �˼Ҳ�������Ϸ��");
		AfxMessageBox(pSzResult);
	}
	else if(psir->szResult == _inviteplayer_roomisbegin)
	{
		pSzResult = _T("�����Ѿ���ʼ��Ϸ�� ����ȥ�ˣ�");
		AfxMessageBox(pSzResult);
	}
	else if(psir->szResult == _inviteplayer_roomisfull)
	{
		pSzResult = _T("���������ˣ�");
		AfxMessageBox(pSzResult);
	}
	else if(psir->szResult == _inviteplayer_success)
	{
		if(psir->m_roomid == 1 && psir->m_sitid == 1)
		{
			((CMyDlgMain*)theApp.m_pMainWnd)->OnBnClickedButton24();
		}
	}
	
	
}

//������Ƶ
void TCPKernel::InviteVedioRq(char* szbuf)
{
	STRU_INVITEVEDIO_RQ * psir=(STRU_INVITEVEDIO_RQ*)szbuf;
	theApp.m_pMainWnd->PostMessage(UM_ISGETFRIENDMSG,0,0);
}

void TCPKernel::InviteVedioRs(char* szbuf)
{
	STRU_INVITEVEDIO_RS * psir=(STRU_INVITEVEDIO_RS*)szbuf;
	if(psir->szResult == _invitevedio_agree)
	{
		//һ��Ҫ��ʾ����chat������ʹ����Ƶ���ܣ�����
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg_pc->m_ffmpeg.Factory(true,true,true);
		((CMyDlgMain*)theApp.m_pMainWnd)->dlg_pc->m_ffmpeg.SetStart(true,true,true);

	}
	else if(psir->szResult == _invitevedio_refuse)
	{
		TCHAR *pSzResult = NULL;
		pSzResult = _T("�Է��ܾ��������Ƶ���룡");
		AfxMessageBox(pSzResult);
	}
}


void TCPKernel::SendFileData(char*szpath,char *szFileName)
{
	
	FILE *pFile = NULL;
	fopen_s(&pFile,szpath,"rb");
	if(pFile == NULL)
		return;
	fseek(pFile,0,SEEK_END);
	int nFileSize = ftell(pFile);
	fseek(pFile,0,SEEK_SET);
	//�����ļ���Ϣ���ļ���С��

	STRU_VIDEOSTREAM_RQ su;
	su.m_nType = _DEF_PROTOCOL_VIDEOSTREAMINFO_RQ;
	WideCharToMultiByte(CP_ACP,0,dlgname,-1,su.m_szName,sizeof(su.m_szName),0,0);
	strcpy_s(su.m_szStream,sizeof(su.m_szStream),szFileName);
	su.m_nlen = nFileSize;
	SendData((char*)&su,sizeof(su));
	//���ļ����ݲ�����
	while(1)
	{
		su.m_nType = _DEF_PROTOCOL_VIDEOSTREAM_RQ;
		su.m_nlen = fread_s(su.m_szStream,sizeof(su.m_szStream),sizeof(char),sizeof(su.m_szStream),pFile);
		if(su.m_nlen==0)
		{
			break;
		}

		SendData((char*)&su,sizeof(su));

	}

	fclose(pFile);

	fclose(pFile);

}


void TCPKernel::GetVedioStreamInfo(char* szbuf)
{
	STRU_VIDEOSTREAM_RQ *psvr = (STRU_VIDEOSTREAM_RQ*)szbuf;

	fopen_s(&m_pFile,psvr->m_szStream,"wb");

	if(m_pFile)
	{
		m_strFileName = psvr->m_szStream;
		m_nFileSize = psvr->m_nlen;
		m_nPos = 0;
	}
}


CString playerfilename;
void TCPKernel::GetVedioStream(char* szbuf)
{
	STRU_VIDEOSTREAM_RQ *psvr = (STRU_VIDEOSTREAM_RQ*)szbuf;
	if(!m_pFile)
		return;

	size_t nRelWriteNum =  fwrite(psvr->m_szStream,sizeof(char),psvr->m_nlen,m_pFile);
	if(nRelWriteNum >0)
	{
		m_nPos += psvr->m_nlen;

		if(m_nPos == m_nFileSize ||psvr->m_nlen < 1000 )
		{
			fclose(m_pFile);
			
			playerfilename = m_strFileName;
			theApp.m_pMainWnd->PostMessage(UM_PLAYERPLAYMSG,0,0);

			m_pFile = NULL;
			m_strFileName = _T("");
			m_nFileSize = 0;
			m_nPos = 0;

		}

	}

}

//�ļ�
extern FileDownloadInfo info;
void TCPKernel::SendFileRs(char* szbuf)
{
	STRU_SENDFILE_RS *pssr = (STRU_SENDFILE_RS *)szbuf;


	if(pssr->m_lresult == true)//֤����������
	{
	
		info.m_llpos = pssr->m_nPos;
		//���ļ����ݲ�����
		STRU_SENDFILEBLOCK_RQ sur;
		sur.m_nType = _DEF_PROTOCOL_SENDFILEBLOCK_RQ;
		strncpy_s(sur.m_szName,pssr->m_szName,_DEF_SIZE);
		strncpy_s(sur.m_szNameChat,pssr->m_szNameChat,_DEF_SIZE);
		memset(sur.m_szFileContent,0,sizeof(sur.m_szFileContent));
		size_t nRelReadNum = fread_s(sur.m_szFileContent,sizeof(sur.m_szFileContent),sizeof(char),MAX_FILEBLOCK_LEN,info.pfile);
		sur.m_nlen = nRelReadNum;
		memcpy(sur.m_szFileName,pssr->m_szFileName,_DEF_SIZE);
		m_pTcpNet->SendData((char*)&sur,sizeof(sur));
	
	}
	else
	{
		//���Ѳ����� Messgaebox
	
	}
	

}

void TCPKernel::SendFileBlockRs(char* szbuf)
{
	STRU_SENDFILEBLOCK_RS *psur = (STRU_SENDFILEBLOCK_RS*)szbuf;
		
	//�ϴ��ļ���ظ�

		info.m_llpos += psur->m_nlen;
		//�жϵ�û���ļ�β��
		if(info.m_llpos < info.m_llfilesize)
		{
			 
				//���ļ����ݲ�����
				STRU_SENDFILEBLOCK_RQ sur;
				sur.m_nType = _DEF_PROTOCOL_SENDFILEBLOCK_RQ;
				strncpy_s(sur.m_szName,psur->m_szName,_DEF_SIZE);
				strncpy_s(sur.m_szFileName,psur->m_szFileName,_DEF_SIZE);
				strncpy_s(sur.m_szNameChat,psur->m_szNameChat,_DEF_SIZE);
				memset(sur.m_szFileContent,0,sizeof(sur.m_szFileContent));
				size_t nRelReadNum = fread_s(sur.m_szFileContent,sizeof(sur.m_szFileContent),sizeof(char),MAX_FILEBLOCK_LEN,info.pfile);
				sur.m_nlen = nRelReadNum;
			
				m_pTcpNet->SendData((char*)&sur,sizeof(sur));
		}
		else
		{
			fclose(info.pfile);	
		}

	
}

void TCPKernel::RecvFileBlockRs(char* szbuf)
{
	STRU_SENDFILEBLOCK_RS *psur = (STRU_SENDFILEBLOCK_RS*)szbuf;
	char FileContent[MAX_FILEBLOCK_LEN];
	memcpy(FileContent,psur->m_szFileContent,MAX_FILEBLOCK_LEN);
	char my_path[400]="../test/";
	 int n=strlen(my_path);
	  int j=n;
	for(int i=0;i<260;i++)
	{
	 
	  my_path[j++]=psur->m_szFileName[i];
	}

	FILE *pfile;
	int err;
	err=fopen_s(&pfile,my_path,"ab+");
	int num;
	if(err == 0)
	{	
		num=fwrite(FileContent,sizeof(char),psur->m_nlen,pfile);
		fclose(pfile);
	}else
	{
		TRACE("error");
	}
	
}
void TCPKernel::GetTeamRs(char* szbuf)
{
	STRU_GETTEAM_RS *psur = (STRU_GETTEAM_RS*)szbuf;
	if(psur->szResult == true)
	{
			STRU_GETINTOROOM_RQ sgr;
			sgr.m_nType=_DEF_PROTOCOL_GETROOM_RQ;
			sgr.m_roomid=psur->m_roomid; //������
			sgr.m_sitid=1;
			sgr.m_buttonid=0;
			WideCharToMultiByte(CP_ACP,0,dlgname,-1,sgr.m_playername,sizeof(sgr.m_playername),0,0);
			theApp.GetKernel()->SendData((char*)&sgr,sizeof(sgr));
	
	}

}