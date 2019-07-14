#ifndef  _PACKDEF_H
#define	 _PACKDEF_H

#include<list>
using namespace std;

typedef char   PackType;

//#define SERVER_IP "127.0.0.1"
#define SERVER_IP "192.168.153.130"

//------------------------------------------------------------------------------------------------
#define BEGIN_PROTOCOL_MAP static const ProtocolMap m_ProtocolMapEntries[]= \
{

#define END_PROTOCOL_MAP 	{0,0} \
};

#define PM(X,Y)  {X,Y},

//------------------------------------------------------------------------------------------------
//��Ϣ
#define UM_LOGINMSG           WM_USER +1
#define UM_GETLISTROOM        WM_USER +2
#define UM_GETPLAYERS         WM_USER +3
#define UM_CREATEROOMMSG      WM_USER +4
#define UM_CREATERESROOMMSG   WM_USER +5
#define UM_CREATEPERSONDLGMSG WM_USER +6
#define UM_ISGETFRIENDMSG     WM_USER +7
#define UM_LOOKPERSONMSG      WM_USER +8
#define UM_PERSONCHATMSG      WM_USER +9
#define UM_PLAYERPLAYMSG      WM_USER +10

//------------------------------------------------------------------------------------------------
//��ʱ��
#define START_GAME_TIMER_ID      1
#define CLOSE_DLG_TIMER_ID       2


//------------------------------------------------------------------------------------------------
//ע��
#define _register_telexists      0
#define _register_userexists     1
#define _register_success        2

//��¼
#define _login_usernoexists      0
#define _login_passworderr       1
#define _login_success           2

//���뷿�� ��ȡ������Ϣ
#define _getroominfo_fail        0
#define _getroominfo_success     1

//��ɫ
#define role_player             0

//�˳����
#define _quit_success 0
#define _quit_fail    1
#define _quit_others  2

//����ʼ��Ϸ
#define _start_success 0
#define _start_people  1 //����ֻ��һ���� �޷���ʼ��Ϸ
#define _start_fail    2 //���������������������� ����û��ȫ�����׼�����
#define _start_end     3 //һ����Ϸ����

//�޸ĸ�����Ϣ
#define _alterperson_success 0
#define _alterperson_pwfail  1

//������������Ϸ
#define _inviteplayer_younotinroom  0
#define _inviteplayer_success       1

#define _inviteplayer_agree         2
#define _inviteplayer_refuse        3
#define _inviteplayer_roomisbegin   4
#define _inviteplayer_roomisfull    5


//ѯ���Ƿ������Ƶ����ظ����
#define _invitevedio_agree     0
#define _invitevedio_refuse    1


//------------------------------------------------------------------------------------------------
//Ĭ��ֵ
#define _DEF_SIZE			64
#define _DEF_SQLLEN        300
#define _DEF_ROOMNUM         6
#define _DEF_PLAYER         36
#define _DEF_IMAGE        4096
#define MAX_PATH			         260
#define MAX_LEN				          40
#define MAX_STHRESH        100*1024*1024
#define MAX_FILEBLOCK_LEN            500
#define _DEF_STREAMSIZE			    1000

//--------------------------------------------------------------------------------------------------
//Э��
#define _DEF_PROTOCOL_BASE		50

//ע��
#define _DEF_PROTOCOL_REGISTER_RQ		_DEF_PROTOCOL_BASE +1
#define _DEF_PROTOCOL_REGISTER_RS		_DEF_PROTOCOL_BASE +2

//��¼
#define _DEF_PROTOCOL_LOGIN_RQ			_DEF_PROTOCOL_BASE +3
#define _DEF_PROTOCOL_LOGIN_RS			_DEF_PROTOCOL_BASE +4

//��ʾ��ǰ�����������
#define _DEF_PROTOCOL_ONLINE_RQ         _DEF_PROTOCOL_BASE +5
#define _DEF_PROTOCOL_ONLINE_RS         _DEF_PROTOCOL_BASE +6

//�˳���ť
#define _DEF_PROTOCOL_QUIT_RQ           _DEF_PROTOCOL_BASE +7
#define _DEF_PROTOCOL_QUIT_RS           _DEF_PROTOCOL_BASE +8

//��������
#define _DEF_PROTOCOL_CHAT_RQ           _DEF_PROTOCOL_BASE +9
#define _DEF_PROTOCOL_CHAT_RS           _DEF_PROTOCOL_BASE +10

//���뷿�� ��Ϣ��ȡ����
#define _DEF_PROTOCOL_GETROOM_RQ		_DEF_PROTOCOL_BASE +11
#define _DEF_PROTOCOL_GETROOM_RS		_DEF_PROTOCOL_BASE +12

//�˳�����
#define _DEF_PROTOCOL_QUITROOM_RQ		_DEF_PROTOCOL_BASE +13
#define _DEF_PROTOCOL_QUITROOM_RS		_DEF_PROTOCOL_BASE +14

//��������
#define _DEF_PROTOCOL_CHATROOM_RQ		_DEF_PROTOCOL_BASE +15
#define _DEF_PROTOCOL_CHATROOM_RS		_DEF_PROTOCOL_BASE +16

//���͵�����
#define _DEF_PROTOCOL_GETPOINT_RQ		_DEF_PROTOCOL_BASE +17
#define _DEF_PROTOCOL_GETPOINT_RS		_DEF_PROTOCOL_BASE +18

//����ʼ
#define _DEF_PROTOCOL_START_RQ		    _DEF_PROTOCOL_BASE +19
#define _DEF_PROTOCOL_START_RS		    _DEF_PROTOCOL_BASE +20

//����
#define _DEF_PROTOCOL_GETSIT_RS		    _DEF_PROTOCOL_BASE +21


//׼�� ȡ��׼��
#define _DEF_PROTOCOL_READY_RQ          _DEF_PROTOCOL_BASE +22
#define _DEF_PROTOCOL_READY_RS          _DEF_PROTOCOL_BASE +23

//����һ���˵���Ϸ
#define _DEF_PROTOCOL_GAMEOVER_RS       _DEF_PROTOCOL_BASE +24

//�޸ĸ�����ϢЭ���
#define _DEF_PROTOCOL_ALTERPERSON_RQ    _DEF_PROTOCOL_BASE +25
#define _DEF_PROTOCOL_ALTERPERSON_RS    _DEF_PROTOCOL_BASE +26

//ÿ����һ����ע��ɹ� ����ӵ����ݿ��person���ݿ���
#define _DEF_PROTOCOL_INSERTPERSON_RQ   _DEF_PROTOCOL_BASE +27
   
//������Ӻ���
#define _DEF_PROTOCOL_GETFRIEND_RQ      _DEF_PROTOCOL_BASE +28
#define _DEF_PROTOCOL_GETFRIEND_RS      _DEF_PROTOCOL_BASE +29


//��ȡ���ݿ��е����к���
#define _DEF_PROTOCOL_GETLISTFRIEND_RQ    _DEF_PROTOCOL_BASE +30
#define _DEF_PROTOCOL_GETLISTFRIEND_RS    _DEF_PROTOCOL_BASE +31


//�鿴���������������
#define _DEF_PROTOCOL_LOOKPERSON_RQ       _DEF_PROTOCOL_BASE +32
#define _DEF_PROTOCOL_LOOKPERSON_RS       _DEF_PROTOCOL_BASE +33


//ɾ������
#define _DEF_PROTOCOL_DELETEFRIEND_RQ     _DEF_PROTOCOL_BASE +34
#define _DEF_PROTOCOL_DELETEFRIEND_RS     _DEF_PROTOCOL_BASE +35


//˽��
#define _DEF_PROTOCOL_PERSONCHAT_RQ		  _DEF_PROTOCOL_BASE +36
#define _DEF_PROTOCOL_PERSONCHAT_RS		  _DEF_PROTOCOL_BASE +37


//�����������ҽ�����Ϸ
#define _DEF_PROTOCOL_INVITEPLAYER_RQ     _DEF_PROTOCOL_BASE +38
#define _DEF_PROTOCOL_INVITEPLAYER_RS     _DEF_PROTOCOL_BASE +39


//ͬ����߾ܾ�
#define _DEF_PROTOCOL_INVITEPLAYERYN_RQ   _DEF_PROTOCOL_BASE +40
#define _DEF_PROTOCOL_INVITEPLAYERYN_RS   _DEF_PROTOCOL_BASE +41


//ѯ���Ƿ������Ƶ����
#define _DEF_PROTOCOL_INVITEVEDIO_RQ      _DEF_PROTOCOL_BASE +42
#define _DEF_PROTOCOL_INVITEVEDIO_RS      _DEF_PROTOCOL_BASE +43


//�ϴ��ļ�
#define _DEF_PROTOCOL_SENDFILE_RQ		_DEF_PROTOCOL_BASE       +44
#define _DEF_PROTOCOL_SENDFILE_RS		_DEF_PROTOCOL_BASE 		 +45

//�ϴ��ļ���
#define _DEF_PROTOCOL_SENDFILEBLOCK_RQ		_DEF_PROTOCOL_BASE 	 +46
#define _DEF_PROTOCOL_SENDFILEBLOCK_RS		_DEF_PROTOCOL_BASE 	 +47

//�����ļ���
#define _DEF_PROTOCOL_RECVFILEBLOCK_RQ		_DEF_PROTOCOL_BASE   +48
#define _DEF_PROTOCOL_RECVFILEBLOCK_RS		_DEF_PROTOCOL_BASE   +49


////����
//#define _DEF_PROTOCOL_STARTTRANSFER_RQ		 _DEF_PROTOCOL_BASE  +50
//#define _DEF_PROTOCOL_STARTTRANSFER_RS		 _DEF_PROTOCOL_BASE  +51
////ֹͣ����														 
//#define _DEF_PROTOCOL_STOPTRANSFER_RQ		_DEF_PROTOCOL_BASE 	 +52
//#define _DEF_PROTOCOL_STOPTRANSFER_RS		_DEF_PROTOCOL_BASE 	 +53

//��Ƶ������														
#define _DEF_PROTOCOL_VIDEOSTREAMINFO_RQ    _DEF_PROTOCOL_BASE 	 +54
#define _DEF_PROTOCOL_VIDEOSTREAMINFO_RS    _DEF_PROTOCOL_BASE 	 +55
//��Ƶ��														 
#define _DEF_PROTOCOL_VIDEOSTREAM_RQ		_DEF_PROTOCOL_BASE 	 +56
#define _DEF_PROTOCOL_VIDEOSTREAM_RS		_DEF_PROTOCOL_BASE 	 +57
//�������
#define _DEF_PROTOCOL_GETTEAM_RQ		    _DEF_PROTOCOL_BASE 	 +58
#define _DEF_PROTOCOL_GETTEAM_RS		    _DEF_PROTOCOL_BASE 	 +59



//-------------------------------------------------------------------------------------------------
//���
struct Player
{
	char m_szName[_DEF_SIZE];
	char m_szPassword[_DEF_SIZE];
	long long m_tel;
	int m_grade;     //����
	int m_role;      //��ɫ
	int m_tablenum;  //��������
};

//����������ҽ�� ������
struct OnlinePlayerServer
{
	char m_szName[_DEF_SIZE];
	SOCKET sock;
};
struct OnlinePlayer
{
	char m_szName[_DEF_SIZE];
};

//����������ҽ�� ������
struct InRoomPlayerServer
{
	char m_szName[_DEF_SIZE];
	SOCKET sock;
};
struct InRoomPlayer
{
	char m_szName[_DEF_SIZE];
};

//����
struct	Room 
{
	long long m_roomid;
	int m_maxplayer;
	int m_curplayer;
	list<struct Player> m_listplayer;
	CBitmap m_blackbitmap;
	CBitmap m_whitebitmap;
	POINT point;
};

//����Ա
struct Root
{
	list<struct Room> m_listroom;
	int m_roomnum;
}; 

//---------------------------------------------------------------------------------------------
//ע������
struct STRU_REGISTER_RQ
{
	 PackType m_nType;
	 char m_szName[_DEF_SIZE];
	 long long m_tel;
	 char m_szPassword[_DEF_SIZE];
	 char  m_role;
};
//ע��ظ�
struct STRU_REGISTER_RS
{
	 PackType m_nType;
	 char m_szName[_DEF_SIZE];
	 long long m_tel;
	 char m_szResult;
};

//��¼����
struct STRU_LOGIN_RQ
{
	 PackType m_nType;
	 char m_szName[_DEF_SIZE];
	 char m_szPassword[_DEF_SIZE];
};

//��¼�ظ�
struct STRU_LOGIN_RS
{
	 PackType m_nType;
	 char m_szName[_DEF_SIZE];
	 char m_szResult;
	 int sit[_DEF_PLAYER];
};

//��ʾ���ߴ�������б� ����
struct STRU_SHOWPLAYER_RQ
{
	PackType m_nType;
};
//�ظ�
struct STRU_SHOWPLAYER_RS
{
	PackType m_nType;
	OnlinePlayer online[_DEF_PLAYER];
};

//�˳�����
struct STRU_QUIT_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
};
//�˳��ظ�
struct STRU_QUIT_RS
{
	PackType m_nType;
	char szResult;
};

//���췢������
struct STRU_CHAT_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_chatbuf[_DEF_SQLLEN];
};
//����ظ�
struct STRU_CHAT_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_chatbuf[_DEF_SQLLEN];
};

//�����λ���뷿�� ��ȡ������Ϣ
struct STRU_GETINTOROOM_RQ
{
	PackType m_nType;
	int m_roomid;
	int m_sitid;
	int m_buttonid;
	char m_playername[_DEF_SIZE];
};
struct STRU_GETINTOROOM_RS
{
	PackType m_nType;
	int m_roomid;
	int m_sitid;
	int m_buttonid;
	InRoomPlayer inroom[_DEF_ROOMNUM];
	char szResult;
};
struct STRU_GETSIT_RS
{
	PackType m_nType;
	bool flag;
	int buttonid;
};

//�˳���������
struct STRU_QUITROOM_RQ
{
	PackType m_nType;
	int m_roomid;
	int sitidc;
	int sitid;
	char m_szName[_DEF_SIZE];
	bool flag_ready;
};
struct STRU_QUITROOM_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE]; //�˳�����
	InRoomPlayer inroom[_DEF_ROOMNUM];
	char szResult;
};

//�������췢������
struct STRU_CHATROOM_RQ
{
	PackType m_nType;
	int m_roomid;
	char m_szName[_DEF_SIZE];
	char m_chatbuf[_DEF_SQLLEN];
	bool flag;
};
//����ظ�
struct STRU_CHATROOM_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_chatbuf[_DEF_SQLLEN];
	bool m_istrue; //�жϲµĶԲ���
	int m_score;//��¼���˵õ��ķ���
	char m_dszName[_DEF_SIZE];//��������
	int m_dscore;//�����˷���
};

//���͵�
struct STRU_GETPOINT_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	int m_roomid;
	POINT point;
	POINT movepoint;
	COLORREF color;
};
//���͸�����ͼ����֮���
struct STRU_GETPOINT_RS
{
	PackType m_nType;
	POINT point;
	POINT movepoint;
	COLORREF color;
};

//����ʼ��Ϸ
struct STRU_START_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	int m_roomid;
};
struct STRU_START_RS
{
	PackType m_nType;
	char m_chatbuf[_DEF_SQLLEN];
	int m_curplayer;
	char szResult;
	char szDrawplayername[_DEF_SIZE];
};

//׼�� ȡ��׼��
struct STRU_READY_RQ
{
	PackType m_nType;
	bool flag_ready; //trueΪ׼�� falseΪȡ��׼��
	int m_roomid;
};

struct STRU_READY_RS
{
	PackType m_nType;
	bool flag_ready; //trueΪ׼�� falseΪȡ��׼��
};

//����һ���˵���Ϸ
struct STRU_GAMEOVER_RS
{
	PackType m_nType;//��Ϸ������־
};
struct STRU_GAMEOVER_RQ
{
	PackType m_nType;
};


//�޸ĸ�����ϢЭ���
struct STRU_ALTERPERSON_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	long long m_tel;
	char sex;

	int m_Year;
	int m_Month;
	int m_Day;

	BOOL b_yespw;
	char m_szoldpw[_DEF_SIZE];
	char m_sznewpw[_DEF_SIZE];
	char m_sznewpw2[_DEF_SIZE];
	//char m_image[_DEF_IMAGE];
};
struct STRU_ALTERPERSON_RS
{
	PackType m_nType;
	char szResult;
};


struct STRU_INSERTPERSON_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	long long m_tel;
};

//��Ӻ�������Э���
struct STRU_GETFRIEND_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_friendName[_DEF_SIZE];
	
};
//��Ӻ��ѻظ�Э���
struct STRU_GETFRIEND_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_friendName[_DEF_SIZE];
	int m_isagree;//�Ƿ�ͬ�����
	//0---ͬ�� 1---��ͬ�� 2---����

};


//
struct STRU_GETLISTFRIEND_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
};

struct STRU_GETLISTFRIEND_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_friendName[_DEF_SIZE];

};



//�鿴�����������
struct STRU_LOOKPERSON_RQ
{
	PackType m_nType;
	char m_szWantLookName[_DEF_SIZE];
};
struct STRU_LOOKPERSON_RS
{
	PackType m_nType;
	char m_szWantLookName[_DEF_SIZE];
	char p_id[_DEF_SIZE];
	char sex; //�Ա���0Ů1
	int m_Year;
	int m_Month;
	int m_Day;
	int m_score;
	int m_level;
	float m_winpercent;
};


struct STRU_DELETEFRIEND_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_deleteName[_DEF_SIZE];
};
struct STRU_DELETEFRIEND_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_deleteName[_DEF_SIZE];
	bool is_delete;
};

//˽��
//���췢������
struct STRU_PERSONCHAT_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_szNameChat[_DEF_SIZE];
	char m_chatbuf[_DEF_SQLLEN];
};
//����ظ�
struct STRU_PERSONCHAT_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_chatbuf[_DEF_SQLLEN];
};


//����������������Ϸ
struct STRU_INVITEPLAYER_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE]; //�����������
	char m_szNameInvite[_DEF_SIZE]; //Ҫ����˭ 
	int m_roomid; //���������ķ���
};
struct STRU_INVITEPLAYER_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_szNameInvite[_DEF_SIZE];
	int m_roomid;
	char szResult;
};

//ͬ�� ���߾ܾ� ֪ͨ������
struct STRU_INVITEPLAYERYN_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_szNameInvite[_DEF_SIZE];
	int m_roomid;
	char szResult;
};
struct STRU_INVITEPLAYERYN_RS
{
	PackType m_nType;
	char szResult;
	int m_roomid;
	int m_sitid;
};


//ѯ���Ƿ������Ƶ����
struct STRU_INVITEVEDIO_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_szNameInvite[_DEF_SIZE];
};
struct STRU_INVITEVEDIO_RS
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
	char m_szNameInvite[_DEF_SIZE];
	char szResult;
};

//�ļ�
struct STRU_SENDFILE_RQ
{
	PackType  m_nType;
	char m_szName[_DEF_SIZE];//��������
	char m_szNameChat[_DEF_SIZE];
	char m_szFileName[MAX_PATH];
	long long m_lFileSize;
	char    m_szMD5[MAX_LEN];

};
struct STRU_SENDFILE_RS
{
	PackType  m_nType;
	char m_szName[_DEF_SIZE];//��������
	char m_szNameChat[_DEF_SIZE];
	char m_szFileName[MAX_PATH];
	bool m_lresult;
	long long m_nPos;

};
struct STRU_SENDFILEBLOCK_RQ
{
	PackType  m_nType;
	char m_szName[_DEF_SIZE];//��������
	char m_szNameChat[_DEF_SIZE];
	char m_szFileName[MAX_PATH];
	char m_szFileContent[MAX_FILEBLOCK_LEN];
	int  m_nlen;
};
struct STRU_SENDFILEBLOCK_RS
{
	PackType  m_nType;
	char m_szName[_DEF_SIZE];//��������
	char m_szNameChat[_DEF_SIZE];
	char m_szFileName[MAX_PATH];
	char m_szFileContent[MAX_FILEBLOCK_LEN];
	long  m_lresult;
	long long m_nlen;
};


//��ʼ��������
struct STRU_STARTTRANSFER_RQ
{
	 PackType m_nType;
	 char m_szName[_DEF_SIZE];	
	 char m_szNameChat[_DEF_SIZE];
};
//��ʼ�����ظ�
struct STRU_STARTTRANSFER_RS
{
	 PackType m_nType;
	 char m_szName[_DEF_SIZE];	
	 char szResult;
};
//��Ƶ����Ϣ
struct STRU_VIDEOSTREAM_RQ
{
	 PackType m_nType;
	 char m_szName[_DEF_SIZE];	
	 char m_szStream[_DEF_STREAMSIZE];
	 int  m_nlen;
};
struct STRU_GETTEAM_RQ
{
	 PackType m_nType;
	 char m_szName[_DEF_SIZE];	
};
struct STRU_GETTEAM_RS
{
	 PackType m_nType;
	 char szResult;
	 int m_roomid;
	// char m_szName[_DEF_SIZE];	
};


#endif
