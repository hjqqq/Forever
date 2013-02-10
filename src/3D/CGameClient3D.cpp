/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameClient3D.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#include "CGameClient3D.h"
#include "CPlayerInfoWnd.h"
#include "CBackpackWnd.h"
#include "CSkillWnd.h"
#include "CHudWnd.h"
#include "CHotKeyWnd.h"
#include "CPlayerStateWnd.h"

#include <OgreMeshManager.h>
#include <OgreMath.h>

#ifdef _DEBUGLOG
#include "LogWindow.h"
extern CLogWindow glog;
#endif  // #ifdef _DEBUG

CGameClient3D::CGameClient3D(std::string machineName) : CGameClient(machineName)
{
   m_pScene3D = NULL;
   m_fPivotPitch = 0;
   m_pTerrain = new CTerrain();
   m_pRayQuery = NULL;
   m_pWindowMan = new CWindowMan3D();

   m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");
   if(m_pRenderCore != NULL) {
      m_pRenderCore->addGameFlowListener(this);
      m_pRenderCore->addMouseEventListener(this);
   }
}

CGameClient3D::~CGameClient3D()
{
   if(m_pWindowMan != NULL) {
      delete m_pWindowMan;
      m_pWindowMan = NULL;
   }

   if(m_pTerrain != NULL) {
      delete m_pTerrain;
      m_pTerrain = NULL;
   }

   if(m_pScene3D != NULL) {
      delete m_pScene3D;
      m_pScene3D = NULL;
   }

   m_pRenderCore = NULL;
}

void CGameClient3D::initUI()
{
   CPlayer *pPlayer2D = this->getScene()->getMainPlayer();

   RECT rect;
   memset(&rect, 0, sizeof(rect));
   HWND hRenderWnd = m_pRenderCore->getRenderHwnd();
   GetClientRect(hRenderWnd, &rect);

   CPlayerInfoWnd *pPlayerInfoWnd = new CPlayerInfoWnd();
   pPlayerInfoWnd->init(10, 10, pPlayer2D);
   m_pWindowMan->addWnd(pPlayerInfoWnd);

   CBackpackWnd *pBackpackWnd = new CBackpackWnd();
   pBackpackWnd->init(10, 411, pPlayer2D);
   m_pWindowMan->addWnd(pBackpackWnd);

   CSkillWnd *pSkillWnd = new CSkillWnd();
   pSkillWnd->init(500, 10, pPlayer2D);
   m_pWindowMan->addWnd(pSkillWnd);

   int hudX = ((rect.right - rect.left) - 856) / 2;
   int hudY = ((rect.bottom - rect.top) - 126);

   CHotKeyWnd *pHotKeyWnd = new CHotKeyWnd();
   int hotkeyX = hudX + 381;
   int hotkeyY = hudY + 75;
   pHotKeyWnd->init(hotkeyX, hotkeyY, pPlayer2D);
   m_pWindowMan->addWnd(pHotKeyWnd);
   m_pRenderCore->addKeyEventListener(pHotKeyWnd);

   CPlayerStateWnd *pPlayerStateWnd = new CPlayerStateWnd();
   int playerstateX = hudX + 98;
   int playerstateY = hudY + 70;
   pPlayerStateWnd->init(playerstateX, playerstateY, pPlayer2D);
   m_pWindowMan->addWnd(pPlayerStateWnd);

   CHudWnd *pHudWnd = new CHudWnd();
   pHudWnd->init(hudX, hudY, pPlayer2D);
   m_pWindowMan->addWnd(pHudWnd);
}

void CGameClient3D::onRecvPlayerInit(CPacketPlayerInit *pPacket)
{
   CPlayer3D *pMainPlayer = m_pScene3D->getMainPlayer3D();
   if(pMainPlayer != NULL)
      pPacket->unpack(pMainPlayer);

   // createScene����, ���oGameServer�����a���
   m_bCreateScene = false;  
}

void CGameClient3D::onRecvPlayerData(CPacketPlayerData *pPacket)
{
   CPlayer3D *pPlayer = m_pScene3D->getPlayer3D(pPacket->getUID());
   if(pPlayer == NULL) {
      CPlayer *pNewPlayer2D = this->getScene()->addPlayer(pPacket->getUID());
      pPlayer = m_pScene3D->addPlayer3D(pNewPlayer2D);
   }

   pPacket->unpack(pPlayer);
}

void CGameClient3D::createScene()
{
   CGameClient::init();

   m_pSceneManager = m_pRenderCore->getSceneManager();
   m_pScene3D = new CScene3D(m_pSceneManager, this->getNetStream());

   m_pRayQuery = m_pSceneManager->createRayQuery(Ogre::Ray());

   // �]�w�������ҥ���
   m_pSceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

   // �إߪ��a�ҫ� (��ƥ��w)
   CPlayer *pPlayer2D = this->getScene()->getMainPlayer();
   CPlayer3D *pMainPlayer = m_pScene3D->addPlayer3D(pPlayer2D, true);

   // �̾ڪ��a�ҫ���m�ӳ]�w��v��
   setupCamera(m_pRenderCore->getCamera(), pMainPlayer->getPosition());

   // �a�Ϊ�l��
   m_pTerrain->init(m_pSceneManager, m_pRenderCore->getCamera());

   // createScene�٨S����, ��������GameServer�����a���
   m_bCreateScene = true;  
}

bool CGameClient3D::frameRenderingQueued(float timeSinceLastFrame)
{
   CGameClient::work(m_pRenderCore->getRenderHwnd(), timeSinceLastFrame);

   if(m_bCreateScene == false) {
      m_pScene3D->work(timeSinceLastFrame, m_pCameraNode);

      // �H���a���⪺��m�ӧ�s��v�����޿�B��
      updateCamera(timeSinceLastFrame, m_pScene3D->getMainPlayer3D()->getPosition());
   }

   return true;
}

void CGameClient3D::destoryScene()
{
   m_pWindowMan->deleteAllWindow();

   m_pSceneManager->destroyQuery(m_pRayQuery);
   m_pRayQuery = NULL;

   releaseCamera();

   m_pTerrain->release();
   
   m_pScene3D->clear();

   this->getScene()->clear();
}

void CGameClient3D::mouseDown(const OIS::MouseEvent &evt)
{
   if(evt.state.buttonDown(OIS::MB_Left)) {   
      int xPos = evt.state.X.abs;
      int yPos = evt.state.Y.abs;
      int width = evt.state.width;
      int height = evt.state.height;

      if(m_pWindowMan->isPressWindow(xPos, yPos) == false) {
         Ogre::Camera *pCamera = m_pRenderCore->getCamera();

         // �qcamera��ƹ��I����X,Y�y�Ь��̾ڲ��ͤ@���g�u
         Ogre::Ray mouseRay = pCamera->getCameraToViewportRay(xPos / (float)width, yPos / (float)height);
         m_pRayQuery->setRay(mouseRay);

         // �M��o���g�u���줰��3D����
         Ogre::RaySceneQueryResult &result = m_pRayQuery->execute();
         Ogre::RaySceneQueryResult::iterator it = result.begin();
         while(it != result.end()) {
            std::string nodeName = (*it).movable->getName();
            if(nodeName.find("ETTerrain") != std::string::npos) {
               // �ƹ��I��a�O

               Ogre::Vector3 newPos;
               m_pTerrain->getRayPos(mouseRay, newPos);
               m_pScene3D->getMainPlayer3D()->setMouseTargetPosition(newPos);
               break;
            }

            it++;
         }
      }
   }
}

void CGameClient3D::mouseMove(const OIS::MouseEvent &evt)
{
   // �ƹ��k����ۤ���
   if(evt.state.buttonDown(OIS::MB_Right)) { 
      int xPos = evt.state.X.abs;
      int yPos = evt.state.Y.abs;
      if(m_pWindowMan->isPressWindow(xPos, yPos) == false) {
         /** ����Y�b�����V
           * evt.state.X ���ƹ����ʪ�X�ܰʶq */
         Ogre::Real dx = (float)evt.state.X.rel;

         /** ����X�b�����V
           * evt.state.Y ���ƹ����ʪ�Y�ܰʶq */
         Ogre::Real dy = (float)evt.state.Y.rel;

         if(abs(dx) > abs(dy)) {
            // �YX�y���ܰʶq�j��Y�y���ܰʶq, �K�HX�y���ܰʶq����

            /** �H�D���������I����Y�b (������������)
              * �ƹ���������, ��v���H�D����Y�b���b�ߦV�k����
              * �ƹ����k����, ��v���H�D����Y�b���b�ߦV������ */
            dx *= -1.0f;

            m_pCameraPivot->yaw(Ogre::Degree(dx), Ogre::Node::TS_WORLD);  
         }
         else {
            // �YY�y���ܰʶq�j��X�y���ܰʶq, �K�HY�y���ܰʶq����

            /** tan�c = y / x, �D�c���ץi�H���D½��쨤��}�U�̤j����(�P�a�O������)
              * �γ~: ��v���V�U½��ɥd��a�O�N���A½��, �K�o���Y�|��쩳�O���U */
            Ogre::Real x = m_pCameraGoal->_getDerivedPosition().distance(m_pCameraPivot->_getDerivedPosition());
            Ogre::Real y = abs(m_pCameraGoal->_getDerivedPosition().y);
            Ogre::Real withGroundRadian = atan(y / x);  // �c = tan-1(y / x)��X���O����
            Ogre::Real withGroundDegree = withGroundRadian * 180 / Ogre::Math::PI;  // ����=����*180/PI;

            /** �H�D���������I����X�b, ����̤j�������׬�70�׻P�������׬�withGroundDegree�� (������������)
              * �ƹ����U����, ��v���H�D����X�b���b�ߦV�W½��쨤���Y��
              * �ƹ����W����, ��v���H�D����X�b���b�ߦV�U½��쨤��}�U */
            dy *= -1.0f;

            if(!(m_fPivotPitch + dy < -60 && dy < 0) &&              // ����½����Y�������׳̤j60��
               !(m_fPivotPitch + dy > withGroundDegree && dy > 0)) { // ����½���}��������
                  m_pCameraPivot->pitch(Ogre::Degree(dy));
                  m_fPivotPitch += dy;
            }
         }
      }
   }

   // �ƹ��u���u�ʮ�, Z�Ȥ��|��0
   if(evt.state.Z.rel != 0) { 
      // �p����v���ؼ��I�P���⪺�Z��
      Ogre::Real dist = m_pCameraGoal->_getDerivedPosition().distance(m_pCameraPivot->_getDerivedPosition());

      /** �p��ƹ��u�����u�ʶq
        * �ѩ�ƹ��u���u�ʤ@��O120�I, �o�Ӻu�ʼƭȹ�C���ӻ���b�Ӥj�ҥH��2000��A���p��
        * ���e�u�� Z �O����, ����u�� Z �O�t��
        * �ƹ��u���V�U�u��, ���Y���Y�p
        * �ƹ��u���V�W�u��, ���Y����j */
      Ogre::Real distChange = ((float)evt.state.Z.rel / 2000.0f) * dist;
      distChange *= -1.0f;

	   // �����j/�Y�p���Z��
      if(!(dist + distChange < 8  && distChange < 0) &&  // ��j����Z��
         !(dist + distChange > 40 && distChange > 0))    // �Y�p����Z��
         m_pCameraGoal->translate(0, 0, distChange, Ogre::Node::TS_LOCAL);
   }
}

void CGameClient3D::mouseUp(const OIS::MouseEvent &evt)
{
}

void CGameClient3D::setupCamera(Ogre::Camera *pCamera, const Ogre::Vector3 &pos)
{
   // �إߤ@�Ӧb���⨭�W���`�I, ���׬��b����ӻH��m
   m_pCameraPivot = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
   m_pCameraPivot->setPosition(pos + Ogre::Vector3::UNIT_Y * 5);

   /** �إߤ@����v�����ؼи`�I, ��v���|�����즹�`�I,
     * �ӳo�Ӹ`�I����m�|�Z������`�IZ��V10���Z���W */
   m_pCameraGoal = m_pCameraPivot->createChildSceneNode(Ogre::Vector3(0, 0, 10));

   /** �إ���v���`�I, ��v���|�j�b���`�I�W.
     * �ӳo�Ӹ`�I����m�|�b������10���Z���W */
   m_pCameraNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
   m_pCameraNode->setPosition(m_pCameraPivot->getPosition() - m_pCameraGoal->getPosition());
   m_pCameraNode->attachObject(pCamera);

   m_pCameraPivot->setFixedYawAxis(true);
   m_pCameraGoal->setFixedYawAxis(true);
	m_pCameraNode->setFixedYawAxis(true);

   // ��v���ݵۨ���`�I����m
   m_pCameraNode->lookAt(m_pCameraPivot->getPosition(), Ogre::Node::TS_WORLD);
}

void CGameClient3D::updateCamera(float timeSinceLastFrame, const Ogre::Vector3 &pos)
{
   /** ���o����̷s����m�I�M�Φ�m_pCameraPivot�`�I�W
     * m_pCameraPivot���ʮ�, m_pCameraGoal�]�|��ۤ@�_���� */
   m_pCameraPivot->setPosition(pos + Ogre::Vector3::UNIT_Y * 5.0f);

   // �p����v���ؼ��I�P��v���`�I���t�Z�Z��
   Ogre::Vector3 offset = m_pCameraGoal->_getDerivedPosition() - m_pCameraNode->getPosition();

   // �̾ڮt�Z�Z��������v��
   m_pCameraNode->translate(offset);

   // ��v���ݵۨ����m
   m_pCameraNode->lookAt(m_pCameraPivot->getPosition(), Ogre::Node::TS_WORLD);
}

void CGameClient3D::releaseCamera()
{
   m_pCameraGoal->detachAllObjects();
   m_pSceneManager->getRootSceneNode()->removeChild(m_pCameraGoal);
   m_pCameraGoal = NULL;

   m_pCameraPivot->detachAllObjects();
   m_pSceneManager->getRootSceneNode()->removeChild(m_pCameraPivot);
   m_pCameraPivot = NULL;

   m_pCameraNode->detachAllObjects();
   m_pSceneManager->getRootSceneNode()->removeChild(m_pCameraNode);
   m_pCameraNode = NULL;
}