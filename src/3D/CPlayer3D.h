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

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

class CPlayer3D : public IKeyEventListener
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

      // IKeyEventListener
      /* virtual */ void keyDown(const OIS::KeyEvent &evt);
      /* virtual */ void keyUp(const OIS::KeyEvent &evt);

      std::vector<Ogre::AnimationState *> *m_pvtAnimationSet;  // ��e���⪺�ʵe���X(�Ҧ��ҫ�)

      // ��v����������Ѽ�
      Ogre::Vector3       m_mouseDirection;   // �ƹ����ʤ�V�P�����q
      Ogre::Vector3       m_keyDirection;     // ��L���ʤ�V�P�����q
      Ogre::Vector3       m_goalDirection;    // �ؼФ�V
      float               m_fTurnSpeed;       // �ҫ����V���t��
      bool                m_bMouseMove;       // �ƹ��I��s�y�ШϨ��Ⲿ��

      // 3D�ҫ������Ѽ�
      Ogre::Entity       *m_pHairEntity;      // �Y�v�ҫ�
      Ogre::Entity       *m_pHeadEntity;      // �y���ҫ�
      Ogre::Entity       *m_pBodyEntity;      // �W��ҫ�
      Ogre::Entity       *m_pFootEntity;      // �c�l�ҫ�
      Ogre::Entity       *m_pHandEntity;      // ��M�ҫ�
      Ogre::Entity       *m_pLegEntity;       // �Ǥl�ҫ�
      Ogre::Entity       *m_pShoulderEntity;  // �ӥҼҫ�
      Ogre::SceneNode    *m_pPlayerNode;      // ����`�I
      Ogre::SceneManager *m_pSceneManager;    // �����޲z��

      CPlayer            *m_pPlayer2D;        // ���a
};

#endif // #ifndef _CPLAYER3D_H_