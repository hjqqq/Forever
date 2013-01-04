/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IMouseEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/16 */
#ifndef _IMOUSEEVENTLISTENER_H_
#define _IMOUSEEVENTLISTENER_H_
#include "Common.h"
#include <OISMouse.h>

class IMouseEventListener
{
   public:
      /** @brief �ƹ�������U
        * @param evt �ƹ�������T
        * @param id  ���ӷƹ����� */
      virtual void mouseDown(const OIS::MouseEvent &evt) = 0;

      /** @brief �ƹ�����
        * @param evt �ƹ�������T */
      virtual void mouseMove(const OIS::MouseEvent &evt) = 0;

      /** @brief �ƹ������}
        * @param evt �ƹ�������T 
        * @param id  ���ӷƹ����� */
      virtual void mouseUp(const OIS::MouseEvent &evt) = 0;
};

#endif  // #ifndef _IMOUSEEVENTLISTENER_H_