#include "CScene3D.h"

CScene3D::CScene3D(Ogre::SceneManager *pSceneManager, GP::NetStream *pNetStream, CTerrain &terrain) : m_pSceneManager(pSceneManager),
                                                                                                      m_pNetStream(pNetStream),
                                                                                                      m_terrain(terrain)
{
   m_pMainPlayer = NULL;
}

CScene3D::~CScene3D()
{
	std::list<CNPC3D *>::iterator itNPC3D = m_npc3DList.begin();
	while(itNPC3D != m_npc3DList.end()) {
		delete (*itNPC3D);
		++itNPC3D;
	}
	m_npc3DList.clear();

   std::list<CMonster3D *>::iterator itMonster3D = m_monster3DList.begin();
   while(itMonster3D != m_monster3DList.end()) {
      delete (*itMonster3D);
      ++itMonster3D;
   }
   m_monster3DList.clear();

   std::list<CPlayer3D *>::iterator itPlayer3D = m_player3DList.begin();
   while(itPlayer3D != m_player3DList.end()) {
      delete (*itPlayer3D);
      ++itPlayer3D;
   }
   m_player3DList.clear();
}

CPlayer3D* CScene3D::addPlayer3D(CPlayer *pPlayer2D, bool bMainPlayer)
{
   CPlayer3D *pPlayer = new CPlayer3D(pPlayer2D, m_pSceneManager, m_pNetStream, m_terrain);
   pPlayer->setup();
   m_player3DList.push_back(pPlayer);

   if(bMainPlayer == true)
      m_pMainPlayer = pPlayer;

   return pPlayer;
}

CPlayer3D* CScene3D::getPlayer3D(long long uid)
{
   std::list<CPlayer3D *>::iterator it = m_player3DList.begin();
   while(it != m_player3DList.end()) {
      if((*it)->getPlayer2D()->getUID() == uid)
         return (*it);

      it++;
   }

   return NULL;
}

void CScene3D::removePlayer3D(long long uid)
{
   std::list<CPlayer3D *>::iterator it = m_player3DList.begin();
   while(it != m_player3DList.end()) {
      if((*it)->getPlayer2D()->getUID() == uid) {
         delete (*it);
         m_player3DList.erase(it);
         return;
      }
         
      it++;
   }
}

CPlayer3D* CScene3D::getMainPlayer3D()
{
   return m_pMainPlayer;
}

CMonster3D* CScene3D::addMonster3D(CMonster *pMonster2D)
{
   CMonster3D *pMonster3D = new CMonster3D(pMonster2D, m_pSceneManager, m_terrain);
   pMonster3D->setup();
   m_monster3DList.push_back(pMonster3D);

   return pMonster3D;
}

CMonster3D* CScene3D::getMonster3D(long long uid)
{
   std::list<CMonster3D *>::iterator it = m_monster3DList.begin();
   while(it != m_monster3DList.end()) {
      if((*it)->getMonster2D()->getUID() == uid)
         return (*it);

      it++;
   }

   return NULL;
}

void CScene3D::removeMonster3D(long long uid)
{
   std::list<CMonster3D *>::iterator it = m_monster3DList.begin();
   while(it != m_monster3DList.end()) {
      if((*it)->getMonster2D()->getUID() == uid) {
         delete (*it);
         m_monster3DList.erase(it);
         return;
      }
         
      it++;
   }
}

CNPC3D* CScene3D::addNPC3D(CNPC *pNPC2D)
{
	CNPC3D *pNPC3D = new CNPC3D(pNPC2D, m_pSceneManager, m_terrain);
	pNPC3D->setup();
	m_npc3DList.push_back(pNPC3D);
	return pNPC3D;
}

CNPC3D* CScene3D::getNPC3D(long long uid)
{
	std::list<CNPC3D *>::iterator it = m_npc3DList.begin();
	while(it != m_npc3DList.end()) {
		if((*it)->getNPC2D()->getUID() == uid)
			return (*it);
		it++;
	}

	return NULL;
}

void CScene3D::removeNPC3D(long long uid)
{
	std::list<CNPC3D *>::iterator it = m_npc3DList.begin();
   while(it != m_npc3DList.end()) {
      if((*it)->getNPC2D()->getUID() == uid) {
         delete (*it);
         m_npc3DList.erase(it);
         return;
      }
         
      it++;
   }
}

void CScene3D::clear()
{
	std::list<CNPC3D *>::iterator itNPC3D = m_npc3DList.begin();
	while(itNPC3D != m_npc3DList.end()) {
		delete (*itNPC3D);
		++itNPC3D;
	}
	m_npc3DList.clear();

   std::list<CMonster3D *>::iterator itMonster3D = m_monster3DList.begin();
   while(itMonster3D != m_monster3DList.end()) {
      delete (*itMonster3D);
      ++itMonster3D;
   }
   m_monster3DList.clear();

   std::list<CPlayer3D *>::iterator itPlayer3D = m_player3DList.begin();
   while(itPlayer3D != m_player3DList.end()) {
      delete (*itPlayer3D);
      ++itPlayer3D;
   }
   m_player3DList.clear();
}

void CScene3D::work(float timePass, Ogre::SceneNode *pCameraNode)
{
   std::list<CPlayer3D *>::iterator itPlayer3D = m_player3DList.begin();
   while(itPlayer3D != m_player3DList.end()) {
      if((*itPlayer3D) == m_pMainPlayer)
         (*itPlayer3D)->setMainPlayer(true);

         (*itPlayer3D)->update(timePass, pCameraNode);  

      itPlayer3D++;
   }

   std::list<CMonster3D *>::iterator itMonster3D = m_monster3DList.begin();
   while(itMonster3D != m_monster3DList.end()) {
         (*itMonster3D)->update(timePass, pCameraNode);

      itMonster3D++;
   }

	std::list<CNPC3D *>::iterator itNPC3D = m_npc3DList.begin();
	while(itNPC3D != m_npc3DList.end()) {
		(*itNPC3D)->update(timePass, pCameraNode);
		itNPC3D++;
	}
}