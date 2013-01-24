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
#include "CMonster.h"

/** @brief �����޲z
  *        �޲z�o�ӳ����������Ǫ��a */
class CScene
{
   public:
      CScene();
      ~CScene();

      /** @brief �s�W���a
        * @param uid         �ߤ@�s��
        * @param bMainPlayer �O�_���D��
        * @return ���a���� */
      CPlayer* addPlayer(long long uid, bool bMainPlayer = false);

      /** @brief �R�����a
        * @param uid �ߤ@�s�� */
      void removePlayer(long long uid);

      /** @brief �s�W�Ǫ�
        * @param uid    �ߤ@�s��
        * @param kindID �Ǫ������s��
        * @param x      �y��X
        * @param y      �y��Y
        * @return �Ǫ����� */
      CMonster* addMonster(long long uid, int kindID, float x, float y);

      /** @brief �R���Ҧ��F�� */
      void removeAll();

      void loadScene(SCENE_TYPE scene);

      /** @brief ���o�D�����a */
      CPlayer* getMainPlayer();

      /** @brief ���o���a
        * @param uid �ߤ@�s��
        * @return ���a���� */
      CPlayer* getPlayer(long long uid);

      /** @brief ���o�Ǫ�
        * @param uid �ߤ@�s��
        * @return �Ǫ����� */
      CMonster* getMonster(long long uid);

      /** @brief ���o�@�Գ�� (�i��O���a/�Ǫ�/NPC)
        * @param uid �ߤ@�s��
        * @return �@�Գ�쪫�� */
      CUnitObject* getUnitObject(long long uid);

      /** @brief �޿�ʧ@
        * @param timePass �@��frame�X�� */
      void work(float timePass);

      std::list<CPlayer *>* getvtPlayer();

#ifdef _GAMEENGINE_2D_
      /** @brief ���o���a
        * @param x �ƹ��I����X�y��
        * @param y �ƹ��I����Y�y��
        * @return ���a���� */
      CPlayer* getPlayer(float x, float y);

      /** @brief ���o�Ǫ�
        * @param x �ƹ��I����X�y��
        * @param y �ƹ��I����Y�y��
        * @return �Ǫ����� */
      CMonster* getMonster(float x, float y);

      /** @brief ���o�@�Գ��
        * @param x �ƹ��I����X�y��
        * @param y �ƹ��I����Y�y��
        * @return �@�Գ�쪫�� */
      CUnitObject* getUnitObject(float x, float y);

      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   private:
      std::list<CPlayer *>  *m_pvtPlayer;   // �������Ҧ����a
      std::list<CMonster *> *m_pvtMonster;  // �������Ҧ��Ǫ�
      CPlayer               *m_pMainPlayer; // ���a
      SCENE_TYPE             m_scene;       // ���ӳ���
};

#endif  // #ifndef _CSCENE_H_