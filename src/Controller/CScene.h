/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CScene.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#ifndef _CSCENE_H_
#define _CSCENE_H_
#include "Common.h"
#include "CPlayer.h"

/** @brief �����޲z
  *        �޲z�o�ӳ����������Ǫ��a */
class CScene
{
   public:
      CScene();
      ~CScene();

      /** @brief �s�W���a
        * @param  uid ���a�s��
        * @return ���a���� */
      CPlayer* addPlayer(long long uid, bool bMainPlayer = false);

      /** @brief �R�����a
        * @param uid ���a�s�� */
      void removePlayer(long long uid);

      /** @brief �R���Ҧ��F�� */
      void removeAll();

      void loadScene(SCENE_TYPE scene);

      /** @brief ���o���a */
      CPlayer* getMainPlayer();

      /** @brief �޿�ʧ@
        * @param timePass �@��frame�X�� */
      void work(float timePass);

#ifdef _GAMEENGINE_2D_
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   private:
      std::list<CPlayer *> *m_pvtPlayer;   // ���������Ҧ����a
      CPlayer              *m_pMainPlayer; // ���a
      SCENE_TYPE            m_scene;       // ���ӳ���
};

#endif  // #ifndef _CSCENE_H_