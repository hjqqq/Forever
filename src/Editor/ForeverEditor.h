// ForeverEditor.h : ForeverEditor ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CForeverEditorApp:
// �аѾ\��@�����O�� ForeverEditor.cpp
//

class CForeverEditorApp : public CWinApp
{
public:
	CForeverEditorApp();


// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CForeverEditorApp theApp;