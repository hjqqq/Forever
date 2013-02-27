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
#include "CNPC.h"
#include "ISceneMonsterEventListener.h"

/** @brief �����޲z
  *        �޲z�o�ӳ����������Ǫ��a */
class CScene
{
   public:
      CScene(std::string machineName);
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

		void removeMonster(long long uid);

		CNPC* addNPC(long long uid, int kindID, float x, float y, float direction = -3.1415926f);

		void	removeNPC(long long uid);

      /** @brief �R���Ҧ��F�� */
      void clear();

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

		CNPC* getNPC(long long uid);

      /** @brief ���o�@�Գ�� (�i��O���a/�Ǫ�/NPC)
        * @param uid �ߤ@�s��
        * @return �@�Գ�쪫�� */
      CUnitObject* getUnitObject(long long uid);

      /** @brief �޿�ʧ@
        * @param timePass �@��frame�X�� */
      void work(float timePass);

      std::list<CPlayer *>* getAllPlayer();
      std::list<CMonster *>* getAllMonster();
		std::vector<CNPC *>* getAllNPC();

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

		CNPC* getNPC(float x, float y);

      /** @brief ���o�@�Գ��
        * @param x �ƹ��I����X�y��
        * @param y �ƹ��I����Y�y��
        * @return �@�Գ�쪫�� */
      CUnitObject* getUnitObject(float x, float y);

      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

      void addSceneMonsterEventListener(ISceneMonsterEventListener *pListener);
      void removeSceneMonsterEventListener(ISceneMonsterEventListener *pListener);

   private:
      void notifyAddMonsterUpdate(CMonster *pNewMonster);

      std::string            m_machineName; // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      std::list<CPlayer *>  *m_pvtPlayer;   // �������Ҧ����a
      std::list<CMonster *> *m_pvtMonster;  // �������Ҧ��Ǫ�
		std::vector<CNPC *>	 *m_pvtNPC;
      CPlayer               *m_pMainPlayer; // ���a

      std::set<ISceneMonsterEventListener *> m_monsterEventListeners;    // ��ť�Ǫ��ƥ󪺺�ť�̦C��
};

#endif  // #ifndef _CSCENE_H_