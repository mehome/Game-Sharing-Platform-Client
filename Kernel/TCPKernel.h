#ifndef _TCPKERNEL_H
#define _TCPKERNEL_H

#include "IKernel.h"
#include "TCPNet.h"

#include "Packdef.h"
#include "MyDlgMain.h"
#include "RoomDlgg.h"
#include <string.h>


class TCPKernel;
typedef void (TCPKernel:: *PFUN)(char*);
struct ProtocolMap
{
    PackType m_nType;
	PFUN     m_pfun;
};


class TCPKernel :public IKernel
{
public:
	TCPKernel();
	virtual ~TCPKernel();
public:
	bool Open();
	void Close();
	void DealData(char* szbuf);
	bool SendData(char* szbuf,int nlen);
public:
	void RegisterRs(char* szbuf); //ע��
	void LoginRs(char* szbuf); //��¼
	void RecvOnlineListRs(char* szbuf); //��ʾ�������
	void QuitRs(char* szbuf); //�˳�
	void ChatRs(char* szbuf); //����
	void GetRoomRs(char* szbuf); //��ȡ���������Ϣ
	void QuitRoomRs(char* szbuf); //�˳�����ظ�
	void ChatRoomRs(char* szbuf); //��������
	void GetPointRs(char* szbuf);
	void StartRs(char* szbuf); //�յ���ʼ��Ϸ��֪ͨ
	void GetSitRs(char* szbuf); //����֪ͨ
	void ReadyRs(char* szbuf); //����׼�� ȡ��׼��
	void GameOverRs(char* szbuf);
	void AlterPersonRs(char* szbuf); //�޸ĸ�����Ϣ
	void GetFriendRs(char *szbuf); //��Ӻ�������
	void GetListFriendRs(char* szbuf);
	void LookPersonRs(char* szbuf); //�鿴���ϻظ���
	void DeleteFriendRs(char* szbuf);
	void PersonChatRs(char* szbuf); //˽��
	void InvitePlayerRs(char* szbuf); //������Ϸ
	void InvitePlayerYnRs(char* szbuf);
	void InviteVedioRq(char* szbuf); //������Ƶ
	void InviteVedioRs(char* szbuf);
	void SendFileData(char*szpath,char *szFileName);
	void GetVedioStreamInfo(char* szbuf);
	void GetVedioStream(char* szbuf);
	void SendFileRs(char* szbuf);//�����ļ��ظ�
	void SendFileBlockRs(char* szbuf);
	void RecvFileBlockRs(char* szbuf);
	void GetTeamRs(char* szbuf);

private:
	INet *m_pTcpNet;

public:
	FILE *m_pFile;
	CString m_strFileName;
	int   m_nPos;
	int   m_nFileSize;

};

#endif