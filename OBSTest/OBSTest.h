
// OBSTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COBSTestApp: 
// �йش����ʵ�֣������ OBSTest.cpp
//

class COBSTestApp : public CWinApp
{
public:
	COBSTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COBSTestApp theApp;