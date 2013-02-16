/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CMonster3D.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/10 */
#include "CMonster3D.h"
#include "CRenderLoader.h"

#include <OgreQuaternion.h>
#include <OgreSkeletonInstance.h>
#include <OgreSkeletonManager.h>

unsigned int CMonster3D::m_iMonsterCount = 0;

CMonster3D::CMonster3D(CMonster *pMonster, Ogre::SceneManager *pSceneManager) : m_pMonster2D(pMonster),
                                                                                m_pSceneManager(pSceneManager)
{
   m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");

   char buf[256];
   memset(buf, 0, sizeof(buf));
   sprintf(buf, "%s::CMonster3D::%d", m_pMonster2D->getMachineName().c_str(), m_iMonsterCount++);
   m_pMonsterNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(buf);

   m_nameOverlay = NULL;

   m_pBodyEntity = NULL;

   m_pvtAnimationSet = new std::vector<Ogre::AnimationState *>();
}

CMonster3D::~CMonster3D()
{
   release();

   if(m_pvtAnimationSet != NULL) {
      m_pvtAnimationSet->clear();
      delete m_pvtAnimationSet;
      m_pvtAnimationSet = NULL;
   }

   m_pSceneManager->getRootSceneNode()->removeChild(m_pMonsterNode);
   m_pMonsterNode = NULL;

   m_pSceneManager = NULL;
}

void CMonster3D::setup()
{
   CMonsterInfo *pMonsterInfo = CMonster::getInfo(m_pMonster2D->getID());
   if(pMonsterInfo != NULL) {
      m_pBodyEntity = m_pSceneManager->createEntity(pMonsterInfo->getMeshName());

      std::string meshName = pMonsterInfo->getMeshName();
      size_t idx = meshName.find(".mesh");
      m_meshName = meshName.substr(0, idx);

      m_pMonsterNode->attachObject(m_pBodyEntity);

      // �]�w��m
      const FPOS pos = m_pMonster2D->getPosition();
      m_pMonsterNode->setPosition(pos.fX, 0, pos.fY);

      // �]�w��V (�y�¦V-Z�b�P2D��V�ۦP)
      m_pMonsterNode->resetOrientation();
      m_pMonsterNode->yaw(Ogre::Radian(m_pMonster2D->getDirection()));

      // ���J�����ʧ@
      std::vector<std::string> vtAnimationName = m_pMonster2D->getAllAnimationName();
      std::vector<std::string>::iterator it = vtAnimationName.begin();
      while(it != vtAnimationName.end()) {
         if((*it).length() > 0) {
            std::string skeletonFile = (*it) + std::string(".skeleton");
            setupSkeleton(skeletonFile);
         }
         it++;
      }

      // �]�w�ʧ@
      CAction *pNewAction = m_pMonster2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pMonsterNode->getName());

      m_nameOverlay = new CObjectTitle(m_pBodyEntity, m_pRenderCore->getCamera(), "NCTaiwanFont", 20.0f);
   }
}

void CMonster3D::update(float timeSinceLastFrame)
{
   // m_pMonster2D��work�ʧ@���bCScene���B�z

   if(m_pMonster2D->isChangeAction()) {
      CAction *pNewAction = m_pMonster2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pMonsterNode->getName());
   }
   else
      playAnimation(timeSinceLastFrame);

   if((m_pMonster2D->isMove() == true) && (m_pMonster2D->isReachTarget() == false)) {
      // �Ǫ���m���ܮ�, �@�ߵ����ηƹ�����
      FPOS targetPos = m_pMonster2D->getTargetPosition();
      FPOS curPos = m_pMonster2D->getPosition();

      FPOS offsetPos;
      offsetPos.fX = targetPos.fX - curPos.fX;
      offsetPos.fY = targetPos.fY - curPos.fY;

      m_mouseDirection = Ogre::Vector3::ZERO;
      m_mouseDirection.x = offsetPos.fX;
      m_mouseDirection.z = offsetPos.fY;

      move(timeSinceLastFrame, m_mouseDirection);
   }
   else {
      // �Ǫ��S�����ܦ�m��
      FPOS pos = m_pMonster2D->getPosition();
      setPosition(pos.fX, 0, pos.fY);
      setDirection(m_pMonster2D->getDirection());
   }

   m_nameOverlay->setTitle(m_pMonster2D->getName());
   m_nameOverlay->update();
}

void CMonster3D::release()
{
   if(m_nameOverlay != NULL) {
      delete m_nameOverlay;
      m_nameOverlay = NULL;
   }

   m_pvtAnimationSet->clear();
   m_pMonsterNode->detachAllObjects();

   if(m_pBodyEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pBodyEntity);
      m_pBodyEntity = NULL;
   }

   m_pMonster2D = NULL;  // ��CScene����ӧR��
}

const Ogre::Vector3& CMonster3D::getPosition()
{
   return m_pMonsterNode->getPosition();
}

CMonster* CMonster3D::getMonster2D()
{
   return m_pMonster2D;
}

void CMonster3D::setUID(long long uid)
{
   m_pMonsterNode->setUserAny(Ogre::Any(uid));
}

void CMonster3D::setPosition(float x, float y, float z)
{
   m_pMonsterNode->setPosition(x, y, z);
}

void CMonster3D::setDirection(float direction)
{
   // �]�w��V (�y�¦V-Z�b�P2D��V�ۦP)
   m_pMonsterNode->resetOrientation();
   m_pMonsterNode->yaw(Ogre::Radian(direction));
}

void CMonster3D::setAnimation(std::string animationName)
{
   // �M���ʵe
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      (*it)->setEnabled(false);
      it++;
   }
   m_pvtAnimationSet->clear();

   // ���s�]�w�ʵe
   m_pvtAnimationSet->push_back(m_pBodyEntity->getAnimationState(animationName));

   it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      (*it)->setTimePosition(0.0f);
      (*it)->setLoop(false);
      (*it)->setEnabled(true);
      it++;
   }
}

void CMonster3D::playAnimation(float timeSinceLastFrame)
{
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      if((*it)->hasEnded() == true)
         (*it)->setTimePosition(0.0f);

      (*it)->addTime(timeSinceLastFrame);
      it++;
   }
}

void CMonster3D::setupSkeleton(std::string skeletonFile)
{
   Ogre::SkeletonPtr pSkeletonBody = Ogre::SkeletonManager::getSingleton().getByName(m_meshName + ".skeleton");

   Ogre::Skeleton::BoneHandleMap boneHandleMap;
  
   Ogre::SkeletonPtr pNewSkeleton = Ogre::SkeletonManager::getSingleton().load(skeletonFile, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
   Ogre::Animation *pSrcAnimation = pNewSkeleton->getAnimation(0);
   std::string newAnimationName = pSrcAnimation->getName() + "::" + m_pMonsterNode->getName();
   Ogre::Animation *pNewAnimation = pNewSkeleton->createAnimation(newAnimationName, pSrcAnimation->getLength());
   Ogre::Animation *pCloneAnimation = pNewSkeleton->getAnimation(0)->clone(newAnimationName);
   *pNewAnimation = *pCloneAnimation;
   pNewSkeleton->removeAnimation(pSrcAnimation->getName());

   pNewSkeleton->_buildMapBoneByHandle(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonBody->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   Ogre::SkeletonManager::getSingleton().remove(skeletonFile);

   m_pBodyEntity->getSkeleton()->_refreshAnimationState(m_pBodyEntity->getAllAnimationStates());
}

void CMonster3D::move(float timeSinceLastFrame, Ogre::Vector3 &offsetDirection)
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
      Ogre::Quaternion toGoal = m_pMonsterNode->getOrientation().zAxis().getRotationTo(m_goalDirection);

      // ���o��V�᪺��V�O�X�ר�
      Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();

      // ��s��V�᪺��V(����)
      m_pMonster2D->addDirection(toGoal.getYaw().valueRadians());

      // �ҫ�Y�b����
      m_pMonsterNode->yaw(Ogre::Degree(yawToGoal));

      // �ҫ�����Z�b
      AdvancedAttribute advAttr = m_pMonster2D->getAdvAttr();
      m_pMonsterNode->translate(0, 0, timeSinceLastFrame * advAttr.fMove, Ogre::Node::TS_LOCAL);

      // ��s�ҫ��y���I
      Ogre::Vector3 newPos = m_pMonsterNode->getPosition();
      m_pMonster2D->setPosition(newPos.x, newPos.z);
   }
}