
// generateRegCode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CgenerateRegCodeApp: 
// �йش����ʵ�֣������ generateRegCode.cpp
//

class CgenerateRegCodeApp : public CWinApp
{
public:
	CgenerateRegCodeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CgenerateRegCodeApp theApp;
