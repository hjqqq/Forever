/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyState.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/13 */
#include "CKeyState.h"

CKeyState::CKeyState()
{
   m_iKeyID = 0;
   m_bPrevDown = false;
   m_bPress = false;
   m_bDown = false;
}

void CKeyState::setKey(int key)
{
   m_iKeyID = key;
}

bool CKeyState::isPress()
{
   return m_bPress;
}

bool CKeyState::isDown()
{
   return m_bDown;
}

void CKeyState::work()
{
   if(GetAsyncKeyState(m_iKeyID) < 0) {
      // ������U

      if(m_bPrevDown == false)
         m_bPress = true;  // �W����}, �o������, �N��O������U������
      else
         m_bPress = false; // �W������, �o������, �N��O�������۪����A

      m_bDown = true;
      m_bPrevDown = m_bDown;  // �O��o�����A
   }
   else {
      // �����}

      m_bDown = false;
      m_bPrevDown = false;
      m_bPress = false;
   }
}