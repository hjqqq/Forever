#ifndef _CNPC3D_H_
#define _CNPC3D_H_

#include "Common.h"
#include "CGraphicsRender.h"
#include "CNPC.h"
#include "CObjectTitle.h"
#include "CTerrain.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

#include <network\gp_socket.h>

class CNPC3D
{
public:
	CNPC3D(CNPC *pNPC, Ogre::SceneManager *pSceneManager, CTerrain &terrain);
	~CNPC3D();

	/** @brief �]�w�ҫ� */
	void	setup();

   /** @brief ��s�ҫ��޿�B��
	  * @param timeSinceLastFrame 1Frame�O�X�� */
   void update(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode);

   /** @brief ����ҫ� */
   void release();

   /** @brief ���o�y�Ц�m
     * @return 3D�y�Ц�m */
   const Ogre::Vector3& getPosition();

   CNPC* getNPC2D();

   void setUID(long long uid);
private:
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

   std::vector<Ogre::AnimationState *> *m_pvtAnimationSet;  // ���e���⪺�ʵe���X(�Ҧ��ҫ�)

   // Title
   CObjectTitle        m_nameOverlay;      // ��ܩ�3D������W��

   Ogre::Vector3       m_mouseDirection;   // �ƹ����ʤ�V�P�����q
   Ogre::Vector3       m_goalDirection;    // �ؼФ�V

   std::string         m_meshName;         // �ҫ��W��, �S�����ɦW
   Ogre::Entity       *m_pBodyEntity;      // ����ҫ� (�򥻼ҫ�)
   Ogre::SceneNode    *m_pNPCNode;         // ����`�I
   CTerrain           &m_terrain;          // 3D�a��
   Ogre::Vector3       m_terrainHeight;    // 3D�a�ΰ���
   Ogre::SceneManager *m_pSceneManager;    // �����޲z��
   CGraphicsRender    *m_pRenderCore;      // ø�Ϥ���

   CNPC					 *m_pNPC2D;           // NPC

   static unsigned int m_iNPCCount;
};

#endif	//#ifndef _CNPC3D_H_