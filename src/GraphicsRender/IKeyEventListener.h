/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IKeyEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/16 */
#ifndef _IKEYEVENTLISTENER_H_
#define _IKEYEVENTLISTENER_H_
#include "Common.h"
#include <OISKeyboard.h>

class IKeyEventListener
{
   public:
      /** @brief ��L������U
        * @param evt ��L������T */
      virtual void keyDown(const OIS::KeyEvent &evt) = 0;

      /** @brief ��L�����}
        * @param evt ��L������T */
      virtual void keyUp(const OIS::KeyEvent &evt) = 0;
};

#endif  // #ifndef _IKEYEVENTLISTENER_H_