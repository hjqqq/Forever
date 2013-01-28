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
#include "IKeyEventListener.h"
#include "CPlayer.h"
#include "IPlayerEquipEventListener.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

class CPlayer3D : public IKeyEventListener,
                  public IPlayerEquipEventListener
{
   public:
      CPlayer3D(CPlayer *pPlayer, Ogre::SceneManager *pSceneManager);
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

   private:
      /** @brief ���������Ӱʧ@
        * @param animationName �ʧ@�W�� */
      void setAnimation(std::string animationName);

      /** @brief ����ʧ@
        * @param timeSinceLastFrame 1��Frame�g�L�X�� */
      void playAnimation(float timeSinceLastFrame);

      /** @brief �w�˰ʧ@
        * @param skeletonFile �ʧ@�� */
      void setupSkeleton(std::string skeletonFile);

      /** @brief 3D��������
        * @param timeSinceLastFrame 1��Frame�g�L�X��
        * @param pCameraNode        �H��v������m/��V����ǨӹB��
        * @param offsetDirection    ���ʰ����q */
      void move(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode, Ogre::Vector3 &offsetDirection);

      /** @brief 3D��������
        * @param timeSinceLastFrame 1��Frame�g�L�X��
        * @param offsetDirection    ���ʰ����q */
      void move(float timeSinceLastFrame, Ogre::Vector3 &offsetDirection);

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

      std::vector<Ogre::AnimationState *> *m_pvtAnimationSet;  // ��e���⪺�ʵe���X(�Ҧ��ҫ�)

      // ��v����������Ѽ�
      Ogre::Vector3       m_mouseDirection;   // �ƹ����ʤ�V�P�����q
      Ogre::Vector3       m_keyDirection;     // ��L���ʤ�V�P�����q
      Ogre::Vector3       m_goalDirection;    // �ؼФ�V
      float               m_fTurnSpeed;       // �ҫ����V���t��
      bool                m_bMouseMove;       // �ƹ��I��s�y�ШϨ��Ⲿ��

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

      CPlayer            *m_pPlayer2D;            // ���a
};

#endif // #ifndef _CPLAYER3D_H_