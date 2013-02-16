/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlayer3D.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#include "CPlayer3D.h"
#include "CRenderLoader.h"
#include "CKeyActionEvent.h"
#include "CWASDKeyActionEvent.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CPacketTargetPos.h"

#include <OgreQuaternion.h>
#include <OgreSkeletonInstance.h>
#include <OgreSkeletonManager.h>

unsigned int CPlayer3D::m_iPlayerCount = 0;

CPlayer3D::CPlayer3D(CPlayer *pPlayer, Ogre::SceneManager *pSceneManager, GP::NetStream *pNetStream) : m_pPlayer2D(pPlayer),
                                                                                                       m_pSceneManager(pSceneManager),
                                                                                                       m_pNetStream(pNetStream)
{
   m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");
   m_pRenderCore->addKeyEventListener(this);

	char buf[256];
   memset(buf, 0, sizeof(buf));
   sprintf(buf, "%s::CPlayer3D::%d", m_pPlayer2D->getMachineName().c_str(), m_iPlayerCount++);
   m_pPlayerNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(buf);

   m_nameOverlay = NULL;

   m_pHairEntity = NULL;
   m_pHeadEntity = NULL;
   m_pBodyEntity = NULL;
   m_pFootEntity = NULL;
   m_pHandEntity = NULL;
   m_pLegEntity = NULL;

   m_pMainHandSlotEntity = NULL;
   m_pOffHandSlotEntity = NULL;
   m_pChestSlotEntity = NULL;
   m_pPantsSlotEntity = NULL;
   m_pGloveSlotEntity = NULL;
   m_pBootSlotEntity = NULL;
   m_pShoulderSlotEntity = NULL;

   m_mouseDirection = Ogre::Vector3::ZERO;
   m_keyDirection = Ogre::Vector3::ZERO;
   m_goalDirection = Ogre::Vector3::ZERO;
   m_bMainPlayer = false;

   m_pvtAnimationSet = new std::vector<Ogre::AnimationState *>();

   m_pPlayer2D->addPlayerEquipEventListener(this);
   m_pPlayer2D->addDrawWeaponNotifyListener(this);
   m_pPlayer2D->addPutinWeaponNotifyListener(this);
}

CPlayer3D::~CPlayer3D()
{
   m_pPlayer2D->removePlayerEquipEventListener(this);
   m_pPlayer2D->removeDrawWeaponNotifyListener(this);
   m_pPlayer2D->removePutinWeaponNotifyListener(this);

   release();

   if(m_pvtAnimationSet != NULL) {
      m_pvtAnimationSet->clear();
      delete m_pvtAnimationSet;
      m_pvtAnimationSet = NULL;
   }

   m_pSceneManager->getRootSceneNode()->removeChild(m_pPlayerNode);
   m_pPlayerNode = NULL;

   m_pSceneManager = NULL;
}

void CPlayer3D::setup()
{
   m_pHairEntity = m_pSceneManager->createEntity("LM023_Hair.mesh");
   m_pHeadEntity = m_pSceneManager->createEntity("LM001_Head.mesh");
   m_pBodyEntity = m_pSceneManager->createEntity("LMDF_C001_Body.mesh");
   m_pFootEntity = m_pSceneManager->createEntity("LMDF_C001_Foot.mesh");
   m_pHandEntity = m_pSceneManager->createEntity("LMDF_C001_Hand.mesh");
   m_pLegEntity = m_pSceneManager->createEntity("LMDF_C001_Leg.mesh");

   m_pPlayerNode->attachObject(m_pHairEntity);
   m_pPlayerNode->attachObject(m_pHeadEntity);
   m_pPlayerNode->attachObject(m_pBodyEntity);
   m_pPlayerNode->attachObject(m_pFootEntity);
   m_pPlayerNode->attachObject(m_pHandEntity);
   m_pPlayerNode->attachObject(m_pLegEntity);

   // �]�w���a��m
   const FPOS pos = m_pPlayer2D->getPosition();
   m_pPlayerNode->setPosition(pos.fX, 0, pos.fY);

   // �]�w���a����V (�y�¦V-Z�b�P2D��V�ۦP)
   m_pPlayerNode->resetOrientation();
   m_pPlayerNode->yaw(Ogre::Radian(m_pPlayer2D->getDirection()));

   // ���J�����ʧ@
   std::vector<std::string> vtAnimationName = m_pPlayer2D->getAllAnimationName();
   std::vector<std::string>::iterator it = vtAnimationName.begin();
   while(it != vtAnimationName.end()) {
      if((*it).length() > 0) {
         std::string skeletonFile = (*it) + std::string(".skeleton");
         setupSkeleton(skeletonFile);
      }
      it++;
   }

   // �]�w�ʧ@
   CAction *pNewAction = m_pPlayer2D->getCurAction();
   setAnimation(pNewAction->getAnimationName() + "::" + m_pPlayerNode->getName());

   m_nameOverlay = new CObjectTitle(m_pHairEntity, m_pRenderCore->getCamera(), "NCTaiwanFont", 20.0f);
}

void CPlayer3D::update(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode)
{
   // m_pPlayer2D��work�ʧ@���bCScene���B�z

   if(m_pPlayer2D->isChangeAction()) {
      CAction *pNewAction = m_pPlayer2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pPlayerNode->getName());
   }
   else
      playAnimation(timeSinceLastFrame);
   
   if(pCameraNode != NULL) {
      // �N��D��
      m_bMainPlayer = true;

      if(m_keyDirection != Ogre::Vector3::ZERO) {
         // ��L����
         move(timeSinceLastFrame, pCameraNode, m_keyDirection);

         Ogre::Vector3 curPos = m_pPlayerNode->getPosition();
         m_pPlayer2D->setTargetPosition(curPos.x, curPos.z);

         CPacketTargetPos packet;
         packet.pack(m_pPlayer2D);
         m_pNetStream->send(&packet, sizeof(packet));
      }
      else {
         if(m_pPlayer2D->isMove() == true) {
            // �ƹ�����
            FPOS targetPos = m_pPlayer2D->getTargetPosition();
            FPOS curPos = m_pPlayer2D->getPosition();

            FPOS offsetPos;
            offsetPos.fX = targetPos.fX - curPos.fX;
            offsetPos.fY = targetPos.fY - curPos.fY;

            m_mouseDirection = Ogre::Vector3::ZERO;
            m_mouseDirection.x = offsetPos.fX;
            m_mouseDirection.z = offsetPos.fY;

            move(timeSinceLastFrame, m_mouseDirection);
         }
         else {
            // �D���A�D��L���ʤ]�D�ƹ����ʮ�
            m_pPlayer2D->setKeyMoveEnabled(false);

            FPOS pos = m_pPlayer2D->getPosition();
            setPosition(pos.fX, 0, pos.fY);
            setDirection(m_pPlayer2D->getDirection());
         }
      }
   }
   else {
      // ��L���a
      m_bMainPlayer = false;

      if((m_pPlayer2D->isMove() == true) && (m_pPlayer2D->isReachTarget() == false)) {
         // ��L���a��m���ܮ�, �@�ߵ�����L���a�ηƹ�����
         FPOS targetPos = m_pPlayer2D->getTargetPosition();
         FPOS curPos = m_pPlayer2D->getPosition();

         FPOS offsetPos;
         offsetPos.fX = targetPos.fX - curPos.fX;
         offsetPos.fY = targetPos.fY - curPos.fY;

         m_mouseDirection = Ogre::Vector3::ZERO;
         m_mouseDirection.x = offsetPos.fX;
         m_mouseDirection.z = offsetPos.fY;

         move(timeSinceLastFrame, m_mouseDirection);
      }
      else {
         // ��L���a�S�����ܦ�m��
         FPOS pos = m_pPlayer2D->getPosition();
         setPosition(pos.fX, 0, pos.fY);
         setDirection(m_pPlayer2D->getDirection());
      }
   }

   m_nameOverlay->setTitle(m_pPlayer2D->getName());
   m_nameOverlay->update();
}

void CPlayer3D::release()
{
   if(m_nameOverlay != NULL) {
      delete m_nameOverlay;
      m_nameOverlay = NULL;
   }

   m_pvtAnimationSet->clear();
   m_pPlayerNode->detachAllObjects();

   if(m_pHairEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pHairEntity);
      m_pHairEntity = NULL;
   }

   if(m_pHeadEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pHeadEntity);
      m_pHeadEntity = NULL;
   }

   if(m_pBodyEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pBodyEntity);
      m_pBodyEntity = NULL;
   }

   if(m_pFootEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pFootEntity);
      m_pFootEntity = NULL;
   }

   if(m_pHandEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pHandEntity);
      m_pHandEntity = NULL;
   }

   if(m_pLegEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pLegEntity);
      m_pLegEntity = NULL;
   }

   if(m_pMainHandSlotEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pMainHandSlotEntity);
      m_pMainHandSlotEntity = NULL;
   }

   if(m_pOffHandSlotEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pOffHandSlotEntity);
      m_pOffHandSlotEntity = NULL;
   }

   if(m_pChestSlotEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pChestSlotEntity);
      m_pChestSlotEntity = NULL;
   }

   if(m_pPantsSlotEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pPantsSlotEntity);
      m_pPantsSlotEntity = NULL;
   }

   if(m_pGloveSlotEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pGloveSlotEntity);
      m_pGloveSlotEntity = NULL;
   }

   if(m_pBootSlotEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pBootSlotEntity);
      m_pBootSlotEntity = NULL;
   }

   if(m_pShoulderSlotEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pShoulderSlotEntity);
      m_pBootSlotEntity = NULL;
   }

   m_pPlayer2D = NULL;  // ��CScene����ӧR��
}

const Ogre::Vector3& CPlayer3D::getPosition()
{
   return m_pPlayerNode->getPosition();
}

void CPlayer3D::setMouseTargetPosition(Ogre::Vector3 &targetPos)
{
   if(m_bMainPlayer == false)
      return;

   m_pPlayer2D->setTargetPosition(targetPos.x, targetPos.z);

   if(m_pPlayer2D->isReachTarget() == false) {
      CActionEvent actEvent;
      actEvent.m_event = AET_NOT_REACH;
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
   }

   CPacketTargetPos packet;
   packet.pack(m_pPlayer2D);
   m_pNetStream->send(&packet, sizeof(packet));
}

CPlayer* CPlayer3D::getPlayer2D()
{
   return m_pPlayer2D;
}

void CPlayer3D::setUID(long long uid)
{
   m_pPlayerNode->setUserAny(Ogre::Any(uid));
}

void CPlayer3D::setPosition(float x, float y, float z)
{
   m_pPlayerNode->setPosition(x, y, z);
}

void CPlayer3D::setDirection(float direction)
{
   // �]�w���a����V (�y�¦V-Z�b�P2D��V�ۦP)
   m_pPlayerNode->resetOrientation();
   m_pPlayerNode->yaw(Ogre::Radian(direction));
}

void CPlayer3D::setAnimation(std::string animationName)
{
   // �M���ʵe
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      (*it)->setEnabled(false);
      it++;
   }
   m_pvtAnimationSet->clear();

   // ���s�]�w�ʵe
   m_pvtAnimationSet->push_back(m_pHairEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pHeadEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pBodyEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pFootEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pHandEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pLegEntity->getAnimationState(animationName));

   it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      (*it)->setTimePosition(0.0f);
      (*it)->setLoop(false);
      (*it)->setEnabled(true);
      it++;
   }
}

void CPlayer3D::playAnimation(float timeSinceLastFrame)
{
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      if((*it)->hasEnded() == true)
         (*it)->setTimePosition(0.0f);

      (*it)->addTime(timeSinceLastFrame);
      it++;
   }
}

void CPlayer3D::setupSkeleton(std::string skeletonFile)
{
   Ogre::SkeletonPtr pSkeletonHair = Ogre::SkeletonManager::getSingleton().getByName("LM023_Hair.skeleton");
   Ogre::SkeletonPtr pSkeletonHead = Ogre::SkeletonManager::getSingleton().getByName("LM001_Head.skeleton");
   Ogre::SkeletonPtr pSkeletonBody = Ogre::SkeletonManager::getSingleton().getByName("LMDF_C001_Body.skeleton");
   Ogre::SkeletonPtr pSkeletonFoot = Ogre::SkeletonManager::getSingleton().getByName("LMDF_C001_Foot.skeleton");
   Ogre::SkeletonPtr pSkeletonHand = Ogre::SkeletonManager::getSingleton().getByName("LMDF_C001_Hand.skeleton");
   Ogre::SkeletonPtr pSkeletonLeg  = Ogre::SkeletonManager::getSingleton().getByName("LMDF_C001_Leg.skeleton");

   Ogre::Skeleton::BoneHandleMap boneHandleMap;
  
   Ogre::SkeletonPtr pNewSkeleton = Ogre::SkeletonManager::getSingleton().load(skeletonFile, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
   Ogre::Animation *pSrcAnimation = pNewSkeleton->getAnimation(0);
   std::string newAnimationName = pSrcAnimation->getName() + "::" + m_pPlayerNode->getName();
   Ogre::Animation *pNewAnimation = pNewSkeleton->createAnimation(newAnimationName, pSrcAnimation->getLength());
   Ogre::Animation *pCloneAnimation = pNewSkeleton->getAnimation(0)->clone(newAnimationName);
   *pNewAnimation = *pCloneAnimation;
   pNewSkeleton->removeAnimation(pSrcAnimation->getName());

   pNewSkeleton->_buildMapBoneByHandle(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonHair->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonHead->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonBody->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonFoot->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonHand->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonLeg->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   Ogre::SkeletonManager::getSingleton().remove(skeletonFile);

   m_pHairEntity->getSkeleton()->_refreshAnimationState(m_pHairEntity->getAllAnimationStates());
   m_pHeadEntity->getSkeleton()->_refreshAnimationState(m_pHeadEntity->getAllAnimationStates());
   m_pBodyEntity->getSkeleton()->_refreshAnimationState(m_pBodyEntity->getAllAnimationStates());
   m_pFootEntity->getSkeleton()->_refreshAnimationState(m_pFootEntity->getAllAnimationStates());
   m_pHandEntity->getSkeleton()->_refreshAnimationState(m_pHandEntity->getAllAnimationStates());
   m_pLegEntity->getSkeleton()->_refreshAnimationState(m_pLegEntity->getAllAnimationStates());
}

void CPlayer3D::move(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode, Ogre::Vector3 &offsetDirection)
{
   if(offsetDirection != Ogre::Vector3::ZERO) {
      // ��offsetDirection������0��, �N����

      // �ƭȲM��
      m_goalDirection = Ogre::Vector3::ZERO;

      // �H��v������V�p����L����V
      m_goalDirection += (offsetDirection.z * pCameraNode->getOrientation().zAxis());
      m_goalDirection += (offsetDirection.x * pCameraNode->getOrientation().xAxis());
      m_goalDirection.y = 0;
      m_goalDirection.normalise(); // �H�p��᪺��V�����

      // ���o���⪺Z�b��V�����m_goalDirection����V
      Ogre::Quaternion toGoal = m_pPlayerNode->getOrientation().zAxis().getRotationTo(m_goalDirection);

      // ���o��V�᪺��V�O�X�ר�
      Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();

      // ��s��V�᪺��V(����)
      m_pPlayer2D->addDirection(toGoal.getYaw().valueRadians());

      // �ҫ�Y�b����
      m_pPlayerNode->yaw(Ogre::Degree(yawToGoal));

      // �ҫ�����Z�b
      AdvancedAttribute advAttr = m_pPlayer2D->getAdvAttr();
      m_pPlayerNode->translate(0, 0, timeSinceLastFrame * advAttr.fMove, Ogre::Node::TS_LOCAL);

      // ��s�ҫ��y���I
      Ogre::Vector3 newPos = m_pPlayerNode->getPosition();
      m_pPlayer2D->setPosition(newPos.x, newPos.z);
   }
}

void CPlayer3D::move(float timeSinceLastFrame, Ogre::Vector3 &offsetDirection)
{
   if(offsetDirection != Ogre::Vector3::ZERO) {
      // ��offsetDirection������0��, �N����

      // �ƭȲM��
      m_goalDirection = Ogre::Vector3::ZERO;

      // �����q��V���ؼФ�V
      m_goalDirection = offsetDirection;
      m_goalDirection.y = 0;
      m_goalDirection.normalise(); // �H�ؼФ�V�����

      // ���o���⪺Z�b��V�����m_goalDirection����V
      Ogre::Quaternion toGoal = m_pPlayerNode->getOrientation().zAxis().getRotationTo(m_goalDirection);

      // ���o��V�᪺��V�O�X�ר�
      Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();

      // ��s��V�᪺��V(����)
      m_pPlayer2D->addDirection(toGoal.getYaw().valueRadians());

      // �ҫ�Y�b����
      m_pPlayerNode->yaw(Ogre::Degree(yawToGoal));

      // �ҫ�����Z�b
      AdvancedAttribute advAttr = m_pPlayer2D->getAdvAttr();
      m_pPlayerNode->translate(0, 0, timeSinceLastFrame * advAttr.fMove, Ogre::Node::TS_LOCAL);

      // ��s�ҫ��y���I
      Ogre::Vector3 newPos = m_pPlayerNode->getPosition();
      m_pPlayer2D->setPosition(newPos.x, newPos.z);
   }
}

Ogre::Entity* CPlayer3D::setupArmor(Ogre::Entity *pBaseEntity, Ogre::Entity *pSlotEntity, int itemId)
{
   if(itemId != -1) {
      CItemInfo *pItemInfo = CItem::getInfo(itemId);
      if(pItemInfo->getClassType() == ARMOR) {
         CArmorInfo *pArmorInfo = (CArmorInfo *)pItemInfo;

         // �Ѱ�����˳�
         if(pSlotEntity != NULL) {
            m_pPlayerNode->detachObject(pSlotEntity);
            m_pSceneManager->destroyEntity(pSlotEntity);
            pSlotEntity = NULL;
         }
         else
            m_pPlayerNode->detachObject(pBaseEntity);

         // ���J�s�˳�
         pSlotEntity = m_pSceneManager->createEntity(pArmorInfo->getMeshName());

         // �󴫸˳� (�ϥΰ��[�@�ɤ覡�Ӵ��˳�)
         Ogre::SkeletonPtr baseSkPtr = pBaseEntity->getMesh()->getSkeleton();
         pSlotEntity->getMesh()->_notifySkeleton(baseSkPtr);
         pSlotEntity->shareSkeletonInstanceWith(pBaseEntity);
         m_pPlayerNode->attachObject(pSlotEntity);
      }
   }
   else {
      if(pSlotEntity != NULL) {
         m_pPlayerNode->detachObject(pSlotEntity);
         m_pPlayerNode->attachObject(pBaseEntity);

         m_pSceneManager->destroyEntity(pSlotEntity);
         pSlotEntity = NULL;
      }
   }

   return pSlotEntity;
}

void CPlayer3D::keyDown(const OIS::KeyEvent &evt)
{
   if(m_bMainPlayer == false)
      return;

   switch(evt.key) {
      case OIS::KC_W: {
         m_keyDirection.z = -1;

         m_pPlayer2D->setKeyMoveEnabled(true);

         CWASDKeyActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyDownID = 'W';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
         break;
      }

      case OIS::KC_A: {
         m_keyDirection.x = -1;

         m_pPlayer2D->setKeyMoveEnabled(true);

         CWASDKeyActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyDownID = 'A';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
         break;
      }

      case OIS::KC_S: {
         m_keyDirection.z = 1;

         m_pPlayer2D->setKeyMoveEnabled(true);

         CWASDKeyActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyDownID = 'S';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
         break;
      }

      case OIS::KC_D: {
         m_keyDirection.x = 1;

         m_pPlayer2D->setKeyMoveEnabled(true);

         CWASDKeyActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyDownID = 'D';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
         break;
      }
      
      case OIS::KC_X: {
         if(m_pMainHandSlotEntity != NULL) {
            if(m_pPlayer2D->getCurAction()->getID() == 1 ||   // ����
               m_pPlayer2D->getCurAction()->getID() == 4) {   // �԰�����
               CKeyActionEvent actEvent;
               actEvent.m_event = AET_KEY;
               actEvent.m_iKeyID = 'X';
               CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
            }
         }
         break;
      }
   }
}

void CPlayer3D::keyUp(const OIS::KeyEvent &evt)
{
   if(m_bMainPlayer == false)
      return;

   if((evt.key == OIS::KC_W) && (m_keyDirection.z == -1)) {
      m_keyDirection.z = 0;

      CWASDKeyActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyUpID = 'W';
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
   }
   else if((evt.key == OIS::KC_A) && (m_keyDirection.x == -1)) {
      m_keyDirection.x = 0;

      CWASDKeyActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyUpID = 'A';
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
   }
   else if((evt.key == OIS::KC_S) && (m_keyDirection.z == 1)) {
      m_keyDirection.z = 0;

      CWASDKeyActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyUpID = 'S';
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
   }
   else if((evt.key == OIS::KC_D) && (m_keyDirection.x == 1)) {
      m_keyDirection.x = 0;

      CWASDKeyActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyUpID = 'D';
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getMachineName(), m_pPlayer2D->getUID(), actEvent);
   }
}

void CPlayer3D::updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId)
{
   switch(equipSlot) {
      case MAIN_HAND: {
         Ogre::Entity *pEntity = NULL;
         if(m_pChestSlotEntity != NULL)
            pEntity = m_pChestSlotEntity;
         else
            pEntity = m_pBodyEntity;

         if(itemId > -1) {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            if(pItemInfo->getClassType() == WEAPON) {
               CWeaponInfo *pWeaponInfo = (CWeaponInfo *)pItemInfo;

               if(m_pMainHandSlotEntity != NULL) {
                  // �����ªZ��
                  pEntity->detachObjectFromBone(m_pMainHandSlotEntity);
                  m_pSceneManager->destroyEntity(m_pMainHandSlotEntity);
                  m_pMainHandSlotEntity = NULL;
               }

               // ���J�s�Z��
               m_pMainHandSlotEntity = m_pSceneManager->createEntity(pWeaponInfo->getMeshName());

               // �̾ڤ��P���ʧ@�A�Z����b���P��m�W
               m_mainHandBoneName.clear();
               CAction *pCurAction = m_pPlayer2D->getCurAction();
               if(pCurAction->getID() <= ACTION_RUN) {  // ���� �P �D�԰����]�B
                  pEntity->attachObjectToBone("Lwaist_bone", m_pMainHandSlotEntity);
                  m_mainHandBoneName.assign("Lwaist_bone");
               }
               else {
                  pEntity->attachObjectToBone("Rhand_bone", m_pMainHandSlotEntity);
                  m_mainHandBoneName.assign("Rhand_bone");
               }
            }
         }
         else {
            // ���U�Z��
            if(m_pMainHandSlotEntity != NULL) {
               pEntity->detachObjectFromBone(m_pMainHandSlotEntity);
               m_pSceneManager->destroyEntity(m_pMainHandSlotEntity);
               m_pMainHandSlotEntity = NULL;
               m_mainHandBoneName.clear();
            }
         }
         break;
      }   // case MAIN_HAND

      case OFF_HAND: {
         Ogre::Entity *pEntity = NULL;
         if(m_pChestSlotEntity != NULL)
            pEntity = m_pChestSlotEntity;
         else
            pEntity = m_pBodyEntity;

         if(itemId > -1) {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            if(pItemInfo->getClassType() == WEAPON) {
               CWeaponInfo *pWeaponInfo = (CWeaponInfo *)pItemInfo;

               if(m_pOffHandSlotEntity != NULL) {
                  // �����ªZ��
                  pEntity->detachObjectFromBone(m_pOffHandSlotEntity);
                  m_pSceneManager->destroyEntity(m_pOffHandSlotEntity);
                  m_pOffHandSlotEntity = NULL;
               }

               // ���J�s�Z��
               m_pOffHandSlotEntity = m_pSceneManager->createEntity(pWeaponInfo->getMeshName());

               // �̾ڤ��P���ʧ@�A�Z����b���P��m�W
               m_offHandBoneName.clear();
               CAction *pCurAction = m_pPlayer2D->getCurAction();
               if(pCurAction->getID() <= ACTION_RUN) {  // ���� �P �D�԰����]�B
                  pEntity->attachObjectToBone("Back_bone", m_pOffHandSlotEntity);
                  m_offHandBoneName.assign("Back_bone");
               }
               else {
                  pEntity->attachObjectToBone("Shield_bone", m_pOffHandSlotEntity);
                  m_offHandBoneName.assign("Shield_bone");
               }
            }
         }
         else {
            // ���U�Z��
            if(m_pOffHandSlotEntity != NULL) {
               pEntity->detachObjectFromBone(m_pOffHandSlotEntity);
               m_pSceneManager->destroyEntity(m_pOffHandSlotEntity);
               m_pOffHandSlotEntity = NULL;
               m_offHandBoneName.clear();
            }
         }
         break;
      }  // case OFF_HAND

      case CHEST: {
         Ogre::Entity *pEntity = NULL;
         if(m_pChestSlotEntity != NULL)
            pEntity = m_pChestSlotEntity;
         else
            pEntity = m_pBodyEntity;

         // ���U�Z��
         if(m_pMainHandSlotEntity != NULL)
            pEntity->detachObjectFromBone(m_pMainHandSlotEntity);

         if(m_pOffHandSlotEntity != NULL)
            pEntity->detachObjectFromBone(m_pOffHandSlotEntity);

         m_pChestSlotEntity = setupArmor(m_pBodyEntity, m_pChestSlotEntity, itemId);

         if(m_pChestSlotEntity != NULL)
            pEntity = m_pChestSlotEntity;
         else
            pEntity = m_pBodyEntity;

         // �w�˥D��Z��
         if(m_pMainHandSlotEntity != NULL)
            pEntity->attachObjectToBone(m_mainHandBoneName, m_pMainHandSlotEntity);

         if(m_pOffHandSlotEntity != NULL)
            pEntity->attachObjectToBone(m_offHandBoneName, m_pOffHandSlotEntity);

         break;
      }  // case CHEST

      case LEGS: {
         m_pPantsSlotEntity = setupArmor(m_pLegEntity, m_pPantsSlotEntity, itemId);
         break;
      }  // case LEGS

      case GLOVE: {
         m_pGloveSlotEntity = setupArmor(m_pHandEntity, m_pGloveSlotEntity, itemId);
         break;
      }  // case GLOVE

      case BOOT: {
         m_pBootSlotEntity = setupArmor(m_pFootEntity, m_pBootSlotEntity, itemId);
         break;
      }  // case GLOVE

      case SHOULDER: {
         if(itemId != -1) {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            if(pItemInfo->getClassType() == ARMOR) {
               CArmorInfo *pArmorInfo = (CArmorInfo *)pItemInfo;

               // �Ѱ�����˳�
               if(m_pShoulderSlotEntity != NULL) {
                  m_pPlayerNode->detachObject(m_pShoulderSlotEntity);
                  m_pSceneManager->destroyEntity(m_pShoulderSlotEntity);
                  m_pShoulderSlotEntity = NULL;
               }

               // ���J�s�˳�
               m_pShoulderSlotEntity = m_pSceneManager->createEntity(pArmorInfo->getMeshName());

               // �󴫸˳� (�ϥΰ��[�@�ɤ覡�Ӵ��˳�)
               Ogre::SkeletonPtr baseSkPtr = m_pBodyEntity->getMesh()->getSkeleton();
               m_pShoulderSlotEntity->getMesh()->_notifySkeleton(baseSkPtr);
               m_pShoulderSlotEntity->shareSkeletonInstanceWith(m_pBodyEntity);
               m_pPlayerNode->attachObject(m_pShoulderSlotEntity);
            }
         }
         else {
            if(m_pShoulderSlotEntity != NULL) {
               m_pPlayerNode->detachObject(m_pShoulderSlotEntity);

               m_pSceneManager->destroyEntity(m_pShoulderSlotEntity);
               m_pShoulderSlotEntity = NULL;
            }
         }
         break;
      }  // case SHOULDER
   }  // switch
}

void CPlayer3D::notifyDrawWeapon()
{
   if(m_pMainHandSlotEntity != NULL) {
      Ogre::Entity *pEntity = NULL;
      if(m_pChestSlotEntity != NULL)
         pEntity = m_pChestSlotEntity;
      else
         pEntity = m_pBodyEntity;

      pEntity->detachObjectFromBone(m_pMainHandSlotEntity);
      pEntity->attachObjectToBone("Rhand_bone", m_pMainHandSlotEntity);
      m_mainHandBoneName.assign("Rhand_bone");
      
      if(m_pOffHandSlotEntity != NULL) {
         pEntity->detachObjectFromBone(m_pOffHandSlotEntity);
         pEntity->attachObjectToBone("Shield_bone", m_pOffHandSlotEntity);
         m_offHandBoneName.assign("Shield_bone");
      }
   }
}

void CPlayer3D::notifyPutinWeapon()
{
   if(m_pMainHandSlotEntity != NULL) {
      Ogre::Entity *pEntity = NULL;
      if(m_pChestSlotEntity != NULL)
         pEntity = m_pChestSlotEntity;
      else
         pEntity = m_pBodyEntity;

      pEntity->detachObjectFromBone(m_pMainHandSlotEntity);
      pEntity->attachObjectToBone("Lwaist_bone", m_pMainHandSlotEntity);
      m_mainHandBoneName.assign("Lwaist_bone");
      
      if(m_pOffHandSlotEntity != NULL) {
         pEntity->detachObjectFromBone(m_pOffHandSlotEntity);
         pEntity->attachObjectToBone("Back_bone", m_pOffHandSlotEntity);
         m_offHandBoneName.assign("Back_bone");
      }
   }
}