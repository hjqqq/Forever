/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IGameFlowListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#ifndef _IGAMEFLOWLISTENER_H_
#define _IGAMEFLOWLISTENER_H_
#include "Common.h"

/** @brief �C���y�{�T��
  *        �~�Ӧ�����������i�H����ø�Ϥ����ҵo�X���y�{�T�� */
class IGameFlowListener
{
   public:
      /** @brief �إ߳��� */
      virtual void createScene() = 0;

      /** @brief �}�lø�Ϥ��e���C���޿��s */
      virtual bool frameRenderingQueued(float timeSinceLastFrame) = 0;

      /** @brief ��������O���� */
      virtual void destoryScene() = 0;
};

#endif // #ifndef _IGAMEFLOWLISTENER_H_