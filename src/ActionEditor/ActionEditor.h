// ActionEditor.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CActionEditorApp:
// �аѾ\��@�����O�� ActionEditor.cpp
//

class CActionEditorApp : public CWinApp
{
public:
	CActionEditorApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CActionEditorApp theApp;