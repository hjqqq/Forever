/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlayer3D.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#ifndef _CPLAYER3D_H_
#define _CPLAYER3D_H_
#include "Common.h"
#include "CGraphicsRender.h"
#include "CPlayer.h"
#include "CObjectTitle.h"
#include "CTerrain.h"
#include "IKeyEventListener.h"
#include "IPlayerEquipEventListener.h"
#include "IDrawWeaponNotifyListener.h"
#include "IPutinWeaponNotifyListener.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

#include <network\gp_socket.h>

class CPlayer3D : public IKeyEventListener,
                  public IPlayerEquipEventListener,
                  public IDrawWeaponNotifyListener,
                  public IPutinWeaponNotifyListener
{
   public:
      CPlayer3D(CPlayer *pPlayer, Ogre::SceneManager *pSceneManager, GP::NetStream *pNetStream, CTerrain &terrain);
      ~CPlayer3D();

      /** @brief �]�w�ҫ� */
      void setup();

      /** @brief ��s�ҫ��޿�B��
        * @param timeSinceLastFrame 1Frame�O�X��
        * @param pCameraNode        �H��v������m/��V����ǨӹB�� */
      void update(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode);

      /** @brief ����ҫ� */
      void release();

      /** @brief ���o�y�Ц�m
        * @return 3D�y�Ц�m */
      const Ogre::Vector3& getPosition();
      
      /** @brief �]�w�ƹ��ؼ��I��m
        * @param targetPos �ؼ��I��m */
      void setMouseTargetPosition(Ogre::Vector3 &targetPos);

      CPlayer* getPlayer2D();

      void setUID(long long uid);

      void setMainPlayer(bool bMainPlayer);

   private:
      friend class CPacketPlayerInit;
      friend class CPacketPlayerData;
      friend class CPacketEquipData;
      friend class CPacketPlayerDeadReset;

      void setPosition(float x, float y, float z);
      void setDirection(float direction);

      /** @brief ���������Ӱʧ@
        * @param animationName �ʧ@�W�� */
      void setAnimation(std::string animationName);

      /** @brief ����ʧ@
        * @param timeSinceLastFrame 1��Frame�g�L�X�� */
      void playAnimation(float timeSinceLastFrame);

      /** @brief �w�˰ʧ@
        * @param skeletonFile �ʧ@�� */
      void setupSkeleton(std::string skeletonFile);

      /** @brief �w��/���U�˳�
        * @param pBaseEntity  ���⨺�ӳ���ҫ�
        * @param pSlotEntity  ���Ӹ˳ƼѼҫ�
        * @param itemId       �s�˳ƥN�X
        * @return �w�˩Ψ��U���ҫ� */
      Ogre::Entity* setupArmor(Ogre::Entity *pBaseEntity, Ogre::Entity *pSlotEntity, int itemId);

      // IKeyEventListener
      /* virtual */ void keyDown(const OIS::KeyEvent &evt);
      /* virtual */ void keyUp(const OIS::KeyEvent &evt);

      // IPlayerEquipEventListener
      /* virtual */ void updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId);

      // IDrawWeaponNotifyListener
      /* virtual */ void notifyDrawWeapon();

      // IPutinWeaponNotifyListener
      /* virtual */ void notifyPutinWeapon();

      std::vector<Ogre::AnimationState *> *m_pvtAnimationSet;  // ��e���⪺�ʵe���X(�Ҧ��ҫ�)

      // Title
      CObjectTitle        m_nameOverlay;      // ��ܩ�3D������W��

      // ��v����������Ѽ�
      Ogre::Vector3       m_mouseDirection;   // �ƹ����ʤ�V�P�����q
      Ogre::Vector3       m_keyDirection;     // ��L���ʤ�V�P�����q
      Ogre::Vector3       m_goalDirection;    // �ؼФ�V

      // 3D�ҫ������Ѽ�
      std::string         m_mainHandBoneName;     // �D��Z����b���Ӱ��Y���W��
      std::string         m_offHandBoneName;      // �Ƥ�Z����b���Ӱ��Y���W��
      Ogre::Entity       *m_pHairEntity;          // �Y�v�ҫ� (�򥻼ҫ�)
      Ogre::Entity       *m_pHeadEntity;          // �y���ҫ� (�򥻼ҫ�)
      Ogre::Entity       *m_pBodyEntity;          // ����ҫ� (�򥻼ҫ�)
      Ogre::Entity       *m_pFootEntity;          // �}�ҫ� (�򥻼ҫ�)
      Ogre::Entity       *m_pHandEntity;          // ��ҫ� (�򥻼ҫ�)
      Ogre::Entity       *m_pLegEntity;           // �L�ҫ� (�򥻼ҫ�)
      Ogre::Entity       *m_pMainHandSlotEntity;  // �D��Ѽҫ�
      Ogre::Entity       *m_pOffHandSlotEntity;   // �Ƥ�Ѽҫ�
      Ogre::Entity       *m_pChestSlotEntity;     // �W��Ѽҫ�
      Ogre::Entity       *m_pPantsSlotEntity;     // �Ǥl�Ѽҫ�
      Ogre::Entity       *m_pGloveSlotEntity;     // ��M�Ѽҫ�
      Ogre::Entity       *m_pBootSlotEntity;      // �c�l�Ѽҫ�
      Ogre::Entity       *m_pShoulderSlotEntity;  // �ӥҼѼҫ�
      Ogre::SceneNode    *m_pPlayerNode;          // ����`�I
      Ogre::SceneManager *m_pSceneManager;        // �����޲z��
      CGraphicsRender    *m_pRenderCore;          // ø�Ϥ���

      GP::NetStream      *m_pNetStream;
      CTerrain           &m_terrain;              // 3D�a��
      Ogre::Vector3       m_terrainHeight;        // 3D�a�ΰ���
      bool                m_bMainPlayer;          // �O�D����?
      CPlayer            *m_pPlayer2D;            // ���a

      static unsigned int m_iPlayerCount;
};

#endif // #ifndef _CPLAYER3D_H_