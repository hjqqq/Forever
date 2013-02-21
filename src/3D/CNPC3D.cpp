#include "CNPC3D.h"
#include "CRenderLoader.h"

#include <OgreQuaternion.h>
#include <OgreSkeletonInstance.h>
#include <OgreSkeletonManager.h>

unsigned int CNPC3D::m_iNPCCount = 0;

CNPC3D::CNPC3D(CNPC *pNPC, Ogre::SceneManager *pSceneManager) : m_pNPC2D(pNPC),
																					 m_pSceneManager(pSceneManager)
{
	m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");

	char buf[256];
   memset(buf, 0, sizeof(buf));
   sprintf(buf, "%s::CNPC3D::%d", m_pNPC2D->getMachineName().c_str(), m_iNPCCount++);
   m_pNPCNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(buf);

   m_nameOverlay = NULL;

   m_pBodyEntity = NULL;

   m_pvtAnimationSet = new std::vector<Ogre::AnimationState *>();
}

CNPC3D::~CNPC3D()
{
	release();

   if(m_pvtAnimationSet != NULL) {
      m_pvtAnimationSet->clear();
      delete m_pvtAnimationSet;
      m_pvtAnimationSet = NULL;
   }

   m_pSceneManager->getRootSceneNode()->removeChild(m_pNPCNode);
   m_pNPCNode = NULL;

   m_pSceneManager = NULL;
}

void CNPC3D::setup()
{
	CNPCInfo *pNPCInfo = CNPC::getInfo(m_pNPC2D->getID());
	if(pNPCInfo != NULL)
	{
		m_pBodyEntity = m_pSceneManager->createEntity(pNPCInfo->getMeshName());

      std::string meshName = pNPCInfo->getMeshName();
      size_t idx = meshName.find(".mesh");
      m_meshName = meshName.substr(0, idx);

      m_pNPCNode->attachObject(m_pBodyEntity);

      // �]�w��m
      const FPOS pos = m_pNPC2D->getPosition();
      m_pNPCNode->setPosition(pos.fX, 0, pos.fY);

      // �]�w��V (�y�¦V-Z�b�P2D��V�ۦP)
      m_pNPCNode->resetOrientation();
      m_pNPCNode->yaw(Ogre::Radian(m_pNPC2D->getDirection()));

      // ���J�����ʧ@
      std::vector<std::string> vtAnimationName = m_pNPC2D->getAllAnimationName();
      std::vector<std::string>::iterator it = vtAnimationName.begin();
      while(it != vtAnimationName.end()) {
         if((*it).length() > 0) {
            std::string skeletonFile = (*it) + std::string(".skeleton");
            setupSkeleton(skeletonFile);
         }
         it++;
		}

		// �]�w�ʧ@
      CAction *pNewAction = m_pNPC2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pNPCNode->getName());

      m_nameOverlay = new CObjectTitle(m_pBodyEntity, m_pRenderCore->getCamera(), "NCTaiwanFont", 20.0f);
	}
}

void CNPC3D::update(float timeSinceLastFrame)
{
   // m_pNPC2D��work�ʧ@���bCScene���B�z

   if(m_pNPC2D->isChangeAction()) {
      CAction *pNewAction = m_pNPC2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pNPCNode->getName());
   }
   else
      playAnimation(timeSinceLastFrame);

   if((m_pNPC2D->isMove() == true) && (m_pNPC2D->isReachTarget() == false)) {
      // �Ǫ���m���ܮ�, �@�ߵ����ηƹ�����
      FPOS targetPos = m_pNPC2D->getTargetPosition();
      FPOS curPos = m_pNPC2D->getPosition();

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
      FPOS pos = m_pNPC2D->getPosition();
      setPosition(pos.fX, 0, pos.fY);
      setDirection(m_pNPC2D->getDirection());
   }

   m_nameOverlay->setTitle(m_pNPC2D->getName());
   m_nameOverlay->update();
}

void CNPC3D::release()
{
   if(m_nameOverlay != NULL) {
      delete m_nameOverlay;
      m_nameOverlay = NULL;
   }

   m_pvtAnimationSet->clear();
   m_pNPCNode->detachAllObjects();

   if(m_pBodyEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pBodyEntity);
      m_pBodyEntity = NULL;
   }

   m_pNPC2D = NULL;  // ��CScene����ӧR��
}

const Ogre::Vector3& CNPC3D::getPosition()
{
   return m_pNPCNode->getPosition();
}

CNPC* CNPC3D::getNPC2D()
{
   return m_pNPC2D;
}

void CNPC3D::setUID(long long uid)
{
   m_pNPCNode->setUserAny(Ogre::Any(uid));
}

void CNPC3D::setPosition(float x, float y, float z)
{
   m_pNPCNode->setPosition(x, y, z);
}

void CNPC3D::setDirection(float direction)
{
   // �]�w��V (�y�¦V-Z�b�P2D��V�ۦP)
   m_pNPCNode->resetOrientation();
   m_pNPCNode->yaw(Ogre::Radian(direction));
}

void CNPC3D::setAnimation(std::string animationName)
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

void CNPC3D::playAnimation(float timeSinceLastFrame)
{
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      if((*it)->hasEnded() == true)
         (*it)->setTimePosition(0.0f);

      (*it)->addTime(timeSinceLastFrame);
      it++;
   }
}

void CNPC3D::setupSkeleton(std::string skeletonFile)
{
   Ogre::SkeletonPtr pSkeletonBody = Ogre::SkeletonManager::getSingleton().getByName(m_meshName + ".skeleton");

   Ogre::Skeleton::BoneHandleMap boneHandleMap;
  
   Ogre::SkeletonPtr pNewSkeleton = Ogre::SkeletonManager::getSingleton().load(skeletonFile, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
   Ogre::Animation *pSrcAnimation = pNewSkeleton->getAnimation(0);
   std::string newAnimationName = pSrcAnimation->getName() + "::" + m_pNPCNode->getName();
   Ogre::Animation *pNewAnimation = pNewSkeleton->createAnimation(newAnimationName, pSrcAnimation->getLength());
   Ogre::Animation *pCloneAnimation = pNewSkeleton->getAnimation(0)->clone(newAnimationName);
   *pNewAnimation = *pCloneAnimation;
   pNewSkeleton->removeAnimation(pSrcAnimation->getName());

   pNewSkeleton->_buildMapBoneByHandle(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonBody->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   Ogre::SkeletonManager::getSingleton().remove(skeletonFile);

   m_pBodyEntity->getSkeleton()->_refreshAnimationState(m_pBodyEntity->getAllAnimationStates());
}

void CNPC3D::move(float timeSinceLastFrame, Ogre::Vector3 &offsetDirection)
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
      Ogre::Quaternion toGoal = m_pNPCNode->getOrientation().zAxis().getRotationTo(m_goalDirection);

      // ���o��V�᪺��V�O�X�ר�
      Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();

      // ��s��V�᪺��V(����)
      m_pNPC2D->addDirection(toGoal.getYaw().valueRadians());

      // �ҫ�Y�b����
      m_pNPCNode->yaw(Ogre::Degree(yawToGoal));

      // �ҫ�����Z�b
      AdvancedAttribute advAttr = m_pNPC2D->getAdvAttr();
      m_pNPCNode->translate(0, 0, timeSinceLastFrame * advAttr.fMove, Ogre::Node::TS_LOCAL);

      // ��s�ҫ��y���I
      Ogre::Vector3 newPos = m_pNPCNode->getPosition();
      m_pNPC2D->setPosition(newPos.x, newPos.z);
   }
}