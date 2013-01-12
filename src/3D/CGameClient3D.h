/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameClient3D.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#ifndef _CGAMECLIENT3D_H_
#define _CGAMECLIENT3D_H_
#include "CGraphicsRender.h"
#include "CRenderLoader.h"
#include "CPlayer3D.h"
#include "CTerrain.h"
#include "CGameClient.h"
#include "CWindowMan3D.h"

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneQuery.h>

class CGameClient3D : public IGameFlowListener,
                      public IMouseEventListener,
                      public CGameClient
{
   public:
      CGameClient3D();
      ~CGameClient3D();

      void run();

   protected:
      // CGameClient
      /* virtual */ void initUI();

   private:
      // IGameFlowListener
      /* virtual */ void createScene();
      /* virtual */ bool frameRenderingQueued(float timeSinceLastFrame);
      /* virtual */ void destoryScene();

      // IMouseEventListener
      /* virtual */ void mouseDown(const OIS::MouseEvent &evt);
      /* virtual */ void mouseMove(const OIS::MouseEvent &evt);
      /* virtual */ void mouseUp(const OIS::MouseEvent &evt);

      /** @brief �]�w��v��
        * @param pCamera ��v��
        * @param pos     �̾ڬY�Ӯy�Шӳ]�w��v�� */
      void setupCamera(Ogre::Camera *pCamera, const Ogre::Vector3 &pos);

      /** @brief ��s��v������ 
        * @param timeSinceLastFrame �@��frame�X��
        * @param pos                �̾ڬY�Ӯy�Шӳ]�w��v�� */
      void updateCamera(float timeSinceLastFrame, const Ogre::Vector3 &pos);

      /** @brief ������v�� */
      void releaseCamera();

      CWindowMan3D        *m_pWindowMan;     // UI�����޲z

      CPlayer3D           *m_pPlayer;        // ���a�ޱ�
      CTerrain            *m_pTerrain;       // 3D�a��
      Ogre::RaySceneQuery *m_pRayQuery;      // �����g�u���߰ݪ���

      float                m_fPivotPitch;    // �ثe��������(����)�P��������(�t��)

      Ogre::SceneNode     *m_pCameraPivot;   // ���⨭�W��Node (���׬��b�ӻH�W)
      Ogre::SceneNode     *m_pCameraGoal;    // ��v�����ت��I, �Z��m_pCameraPivot���᭱10���a�� (����I��10���Z��)
      Ogre::SceneNode     *m_pCameraNode;    // ��v���u���Ҧb, �|���m_pCameraGoal�Ӳ���

      Ogre::SceneManager  *m_pSceneManager;  // Ogre scene manager
      CGraphicsRender     *m_pRenderCore;    // ø�Ϥ���
};

#endif // #ifndef _CGAMECLIENT3D_H_