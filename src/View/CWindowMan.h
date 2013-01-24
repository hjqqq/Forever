/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWindowMan.h
  * @author �L���}
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - ��X�P�ץ� */
#ifndef _CWINDOWMAN_H_
#define _CWINDOWMAN_H_
#include "CWindow.h"

#ifdef _GAMEENGINE_2D_
#include "CKeyMan.h"
#endif

//�����޲z��(manager)
class CWindowMan
{
   public:
	   CWindowMan();
      virtual ~CWindowMan();

	   virtual void addWnd(CWindow *pWnd);
      void deleteAllWindow();

#ifdef _GAMEENGINE_2D_
      bool work(HWND hWnd, CKeyMan &keyMan);
	   void draw(HDC hdc);
#endif

   protected:
#ifdef _GAMEENGINE_2D_
	   void doDrag(HWND hWnd, CKeyMan &keyMan);
#endif

	   std::list<CWindow *> *m_pWindowList;  // �����C��
	   CWindow *m_pDragWnd;     // �즲��������
      CWindow *m_pBackpackWnd; // �I�]����
	   bool     m_bInDrag;      // �����O�_�b�즲��
	   int      m_iDragX;       // �즲���y��X
      int      m_iDragY;       // �즲���y��Y 
      int      m_iClientX;     // �ƹ��I�����y��X
      int      m_iClientY;     // �ƹ��I�����y��Y
};

#endif  // #ifndef _CWINDOWMAN_H_