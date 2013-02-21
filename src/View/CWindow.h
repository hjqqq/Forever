/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWindow.h
  * @author �L���}
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - ��X�P�ץ� */
#ifndef _CWINDOW_H_
#define _CWINDOW_H_
#include "Common.h"

typedef enum WINDOW_CLASS_TYPE {
   WND_NULL,
   WND_PLAYERINFO,  // �H����T����
   WND_BACKPACK,    // �I�]����
   WND_SKILL,       // �ޯ����
   WND_HUD,         // Hud����
   WND_HOTKEY,      // �ֱ������
   WND_TARGETINFO,  // �ؼе���
   WND_PLAYERSTATE, // �H�����A����
} WindowClassType;

class CWindowMan;

//�N��@�ӹC����������
//�N�ӥi�H�Q�X�R�����I�]����,���A����,���Ȭɭ�
class CWindow
{
   public:
      CWindow();
	   virtual ~CWindow();

	   CWindow* pParent ;//���˵���
	   typedef std::list <CWindow*> VP_WND ;
	   VP_WND vpWnd ;//�Ҧ����l����

	   int x, y ;//�������y��,���W����
	   int w, h ;//�������e��

	   bool checkPoint(int tx, int ty);
      void addChild(CWindow *pChildWnd);
      void delChild(CWindow *pChildWnd);

	   virtual bool canDrag(int tx, int ty);   // �O�_�i�H�즲����
      virtual void onDrag();                  // �����즲�L�{��

	   virtual void onLClick(int tx, int ty);  // �ƹ�����Click
      virtual void onRClick(int tx, int ty);  // �ƹ��k��Click
   	
      virtual void onLCommand(int btnID);  //�l����,���sbutton,�q�� (�ƹ�������U)
      virtual void onRCommand(int btnID);  //�l����,���sbutton,�q�� (�ƹ��k����U)

      virtual WindowClassType getClassType();  // ���o�������A
      void setWindowMan(CWindowMan *pWndMan);

      bool isVisible();
      virtual void show(bool bShow);

#ifdef _GAMEENGINE_3D_
	   virtual void setZOrder(int order);
      virtual int getZOrder();
#elif _GAMEENGINE_2D_
      virtual void draw(HDC hdc, int ox, int oy);
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   protected:
      CWindowMan* getWindowMan();

   private:
      bool        m_bVisible;
      CWindowMan *m_pWindowMan;
};

#endif  // #ifndef _CWINDOW_H_