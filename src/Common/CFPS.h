/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CFPS.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/26 */
#ifndef _CFPS_H_
#define _CFPS_H_
#include "Common.h"

class CFPS
{
   public:
      CFPS();

      int getFPS();
      float getTimePass();
      void work();

   private:
      int   m_iFPS;          // FPS
      int   m_iFrameCount;   // �e����s����
      float m_fNextFPSTime;  // �U���n�p��fps���ɶ�
      float m_fTimePass;
      int   m_iPreTime;      // �W�@��gameWork���ɶ�
};

#endif  // #ifndef _CFPS_H_