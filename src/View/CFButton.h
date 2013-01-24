/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CButton.h
  * @author �L���}
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - ��X�P�ץ� */
#ifndef _CFBUTTON_H_
#define _CFBUTTON_H_
#include "CWindow.h"

class CFButton : public CWindow
{
   public:
	   int id ;

	   void init (int _x, int _y, int _w, int _h, int _id) ;
	   virtual void onLClick (int tx, int ty) ;
      virtual void onRClick (int tx, int ty) ;
};

#endif  // #ifndef _CFBUTTON_H_