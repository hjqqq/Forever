// ChildView.h : CChildView ���O������
//


#pragma once

#include "DLGItem.h"
#include "DLGBuff.h"
#include "DLGSkill.h"

#include "CClientServer.h"

// CChildView ����

class CChildView : public CWnd
{
// �غc
public:
	CChildView();

// �ݩ�
public:
	DLGItem dlgItem ;
    DLGBuff dlgBuff ;
    DLGSkill dlgSkill;

private:
    CClientServer *m_pClientServer;
    HDC            m_memDC;
    HBITMAP        m_hBMP;

// �@�~
public:

// �мg
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �{���X��@
public:
	virtual ~CChildView();

	// ���ͪ��T�������禡
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct ) ;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
//	afx_msg void OnKeyDown (UINT, UINT, UINT) ;

	DECLARE_MESSAGE_MAP()
};

