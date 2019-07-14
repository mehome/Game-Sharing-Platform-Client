
// 1027Client.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include"IKernel.h"
#include"TCPKernel.h"
// CMy1027ClientApp:
// 有关此类的实现，请参阅 1027Client.cpp
//

class CMy1027ClientApp : public CWinApp
{
public:
	CMy1027ClientApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现
private:
	IKernel * m_pKernel;
public:
	IKernel* GetKernel()
	{
		return m_pKernel;
	}

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMy1027ClientApp theApp;