/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyState.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/13 */
#ifndef _CKEYSTATE_H_
#define _CKEYSTATE_H_
#include "Common.h"

class CKeyState
{
   public:
      CKeyState();

      /** @brief �]�w�n�ʴ�������
        * @param key ����N�X */
      void setKey(int key);

      /** @brief �^�ǬO�_�����U������ */
      bool isPress();       

      /** @brief �^�ǬO�_�����۪����� */
      bool isDown();

      /** @brief ���䪬�A�ˬd */
      void work();

   private:
      int  m_iKeyID;     // �ʴ�������N�X
      bool m_bPrevDown;  // �W������O�_����
      bool m_bPress;     // ����O���O�����U�h������
      bool m_bDown;      // ����O���O����
};

#endif  // #ifndef _CKEYSTATE_H_