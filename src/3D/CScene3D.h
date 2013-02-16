#ifndef _CSCENE3D_H_
#define _CSCENE3D_H_
#include "Common.h"
#include "CPlayer3D.h"
#include "CMonster3D.h"

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include <network\gp_socket.h>

class CScene3D
{
   public:
      CScene3D(Ogre::SceneManager *pSceneManager, GP::NetStream *pNetStream);
      ~CScene3D();

      CPlayer3D* addPlayer3D(CPlayer *pPlayer2D, bool bMainPlayer = false);
      CPlayer3D* getPlayer3D(long long uid);
      void removePlayer3D(long long uid);
      CPlayer3D* getMainPlayer3D();

      CMonster3D* addMonster3D(CMonster *pMonster2D);
      CMonster3D* getMonster3D(long long uid);
      void removeMonster3D(long long uid);

      void clear();

      /** @brief ��s�ҫ��޿�B��
        * @param timePass    1Frame�O�X��
        * @param pCameraNode �H��v������m/��V����ǨӹB�� */
      void work(float timePass, Ogre::SceneNode *pCameraNode);

   private:
      GP::NetStream           *m_pNetStream;
      Ogre::SceneManager      *m_pSceneManager;  // Ogre scene manager
      CPlayer3D               *m_pMainPlayer;    // ���a�ޱ�
      std::list<CPlayer3D *>  *m_pPlayer3DList;  // ���a�C��
      std::list<CMonster3D *> *m_pMonster3DList; // �Ǫ��C��
};

#endif  // #ifndef _CSCENE3D_H_