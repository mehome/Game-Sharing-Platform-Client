
// 1027Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include"IKernel.h"
#include"TCPKernel.h"
// CMy1027ClientApp:
// �йش����ʵ�֣������ 1027Client.cpp
//

class CMy1027ClientApp : public CWinApp
{
public:
	CMy1027ClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
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