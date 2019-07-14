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
	void RegisterRs(char* szbuf); //注册
	void LoginRs(char* szbuf); //登录
	void RecvOnlineListRs(char* szbuf); //显示大厅玩家
	void QuitRs(char* szbuf); //退出
	void ChatRs(char* szbuf); //聊天
	void GetRoomRs(char* szbuf); //获取房间玩家信息
	void QuitRoomRs(char* szbuf); //退出房间回复
	void ChatRoomRs(char* szbuf); //房间聊天
	void GetPointRs(char* szbuf);
	void StartRs(char* szbuf); //收到开始游戏的通知
	void GetSitRs(char* szbuf); //换肤通知
	void ReadyRs(char* szbuf); //请求准备 取消准备
	void GameOverRs(char* szbuf);
	void AlterPersonRs(char* szbuf); //修改个人信息
	void GetFriendRs(char *szbuf); //添加好友请求
	void GetListFriendRs(char* szbuf);
	void LookPersonRs(char* szbuf); //查看资料回复包
	void DeleteFriendRs(char* szbuf);
	void PersonChatRs(char* szbuf); //私信
	void InvitePlayerRs(char* szbuf); //邀请游戏
	void InvitePlayerYnRs(char* szbuf);
	void InviteVedioRq(char* szbuf); //邀请视频
	void InviteVedioRs(char* szbuf);
	void SendFileData(char*szpath,char *szFileName);
	void GetVedioStreamInfo(char* szbuf);
	void GetVedioStream(char* szbuf);
	void SendFileRs(char* szbuf);//发送文件回复
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