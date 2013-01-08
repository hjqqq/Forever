/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWindow.h
  * @author �L���}
  * @date   2012/12/21
  *         2013/01/05 ��X�P�ץ� by Darren Chen */
#ifndef _CWINDOW_H_
#define _CWINDOW_H_
#include "Common.h"

typedef enum WINDOW_CLASS_TYPE {
   WND_NULL,
   WND_PLAYERINFO,  // �H����T����
   WND_BACKPACK,    // �I�]����
   WND_SKILL,       // �ޯ����
} WindowClassType;

//�N��@�ӹC����������
//�N�ӥi�H�Q�X�R�����I�]����,���A����,���Ȭɭ�
class CWindow
{
   public:
      CWindow ();
	   virtual ~CWindow ();

	   CWindow* pParent ;//���˵���
	   typedef std::list <CWindow*> VP_WND ;
	   VP_WND vpWnd ;//�Ҧ����l����

	   int x, y ;//�������y��,���W����
	   int w, h ;//�������e��

	   bool bVisible ;

	   bool checkPoint (int tx, int ty) ;

	   virtual void onMove () {} ;

	   virtual bool canDrag (int tx, int ty) ;
	   virtual void onLClick (int tx, int ty);  // �ƹ�����Click
      virtual void onRClick(int tx, int ty);   // �ƹ��k��Click
   	
	   virtual void setZOrder (int) {} ;

	   void addChild (CWindow*) ;

	   virtual void onLCommand (int) {} ;//�l����,���sbutton,�q�� (�ƹ�������U)
      virtual void onRCommand (int) {} ;//�l����,���sbutton,�q�� (�ƹ��k����U)

      virtual WindowClassType getClassType();

#ifdef _GAMEENGINE_2D_
      virtual void draw (HDC hdc, int ox, int oy) ;
#endif 
};

#endif  // #ifndef _CWINDOW_H_