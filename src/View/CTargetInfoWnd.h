/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTargetInfoWnd.h
  * @author �L���}
  * @date   2012/12/21
  * @version
  *         2013/01/14 Darren Chen - ��X�P�ץ� */
#ifndef _CTARGETINFOWND_H_
#define _CTARGETINFOWND_H_
#include "CWindow.h"
#include "CScene.h"
#include "IAdvAttrEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CTargetInfoWnd : public CWindow,
                       public IAdvAttrEventListener
{
   public:
      ~CTargetInfoWnd();

      void init(int _x, int _y, CScene *pScene, CPlayer *pPlayer);

      // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);
#ifdef _GAMEENGINE_3D_
	   /* virtual */ void setZOrder(int order);
#endif

      // IAdvAttrEventListener
      /* virtual */ void updateAdvAttr(CUnitObject *pUnitObject);

      void setTarget(long long uid);
      CUnitObject* getTarget();

   private:
      CScene    *m_pScene;
      CPlayer   *m_pPlayer;
      long long  m_targetUID;

#ifdef _GAMEENGINE_3D_	
	   CImageButton   *m_pBtn;
      CTextAreaOgre  *m_pText;
      COverlayUI      m_overlay;  //�޲zoverlay
#elif _GAMEENGINE_2D_
	   CTextButton    *m_pBtn;
      CTextArea      *m_pText;
#endif
};

#endif  // #ifndef _CTARGETINFOWND_H_