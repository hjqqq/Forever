/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CSoundManager.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/31 */
#ifndef _CSOUNDMANAGER_H_
#define _CSOUNDMANAGER_H_
#ifdef _GAMESOUND_
#include "Common.h"
#include "sound_man.h"

class CSoundManager
{
   public:
      /** @brief ���oCSoundManager���骫��
        * @return CSoundManager���骫�� */
      static CSoundManager* getInstance();

      /** @brief ����CSoundManager���骫�� */
      static void releaseInstance();

      void work();

      /** @brief ����I������
        * @param bgmFile �I�������ɦW
        * @param bLoop   �O�_�n�`������ */
      void playBGM(std::string bgmFile, bool bLoop);

      /** @brief �����I������ */
      void stopBGM();

      /** @brief ���񭵮�
        * @param soundFile �����ɦW */
      void playSound(std::string soundFile);

   private:
      CSoundManager();
      ~CSoundManager();

      static CSoundManager *m_pInstance;  // CSoundManager���骫��

      SoundMan *m_pSoundMan;
};

#endif  // #ifdef _GAMESOUND_
#endif  // #ifndef _CSOUNDMANAGER_H_