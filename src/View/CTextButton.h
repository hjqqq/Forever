/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTextButton.h
  * @author �L���}
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - ��X�P�ץ� */
#ifndef _CTEXTBUTTON_H_
#define _CTEXTBUTTON_H_
#include "CButton.h"

class CTextButton : public CButton
{
   public:
      std::string str ;

	   void draw (HDC hdc, int ox, int oy) ;
};

#endif  // #ifndef _CTEXTBUTTON_H_