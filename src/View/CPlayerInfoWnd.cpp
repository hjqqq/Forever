#include "CPlayerInfoWnd.h"

CPlayerInfoWnd::~CPlayerInfoWnd()
{
   if(m_pPlayer != NULL) {
      m_pPlayer->removeAdvAttrEventListener(this);
      m_pPlayer->removePlayerAttrEventListener(this);
      m_pPlayer->removePlayerEquipEventListener(this);
   }
}

void CPlayerInfoWnd::init (int _x, int _y, CPlayer *pPlr)
{
	m_pPlayer = pPlr;
   if(m_pPlayer != NULL) {
      m_pPlayer->addPlayerAttrEventListener(this);
      m_pPlayer->addAdvAttrEventListener(this);
      m_pPlayer->addPlayerEquipEventListener(this);
   }
   
   x = _x;
   y = _y;
   w = CELL_SIZE * 24;
   h = CELL_SIZE * 20;

#ifdef _GAMEENGINE_3D_
	m_overlay.init(x, y, w, h);
	m_overlay.setBackImage("Examples/KAMEN-setup");

   for(int i = 0; i<BUTTON_COUNT; i++)
	{
		m_vpBtn[i] = new CImageButton ;

		if (i == 0)
		{//�H�U���˳���
			m_vpBtn[i]->init (m_overlay, 0, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 1)
		{
			m_vpBtn[i]->init (m_overlay, 0, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 2)
		{
			m_vpBtn[i]->init (m_overlay, 0, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 3)
		{
			m_vpBtn[i]->init (m_overlay, CELL_SIZE*11, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 4)
		{
			m_vpBtn[i]->init (m_overlay, CELL_SIZE*11, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 5)
		{
			m_vpBtn[i]->init (m_overlay, CELL_SIZE*11, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 6)
		{
			m_vpBtn[i]->init (m_overlay, CELL_SIZE*6-10, CELL_SIZE*17, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 7)
		{//UI�W��(�D����T)
			m_vpBtn[i]->init (m_overlay, 0, 0, w, CELL_SIZE, i) ;
		}else if (i == 8)
		{//�D���W��
			m_vpBtn[i]->init (m_overlay, 0, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 9)
		{//���Ťθg���
			m_vpBtn[i]->init (m_overlay, w/2, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 10)
		{//�ݩ�
			m_vpBtn[i]->init (m_overlay, CELL_SIZE*14, CELL_SIZE*2, CELL_SIZE*10, CELL_SIZE*18, i) ;
		}else if (i == 11)
		{//�D����
			m_vpBtn[i]->init (m_overlay, CELL_SIZE*3, CELL_SIZE*2, CELL_SIZE*8, CELL_SIZE*15, i) ;
			m_vpBtn[i]->setImage ("Examples/tusk") ;
		}
		addChild (m_vpBtn[i]) ;
	}

	//�����򥻸�T
	for (int i = 0; i<3; i++)
	{
		m_vpText[i] = new CTextAreaOgre ;
		if (i == 0)
		{
			m_vpText[i]->init (m_overlay, w/2-30, 0, w, CELL_SIZE) ;
			m_vpText[i]->setText ("�����T", 1, 1, 1) ;
		}else if (i == 1)
		{
			m_vpText[i]->init (m_overlay, w/4-30, CELL_SIZE, w/2, CELL_SIZE) ;
		}else if (i == 2)
		{
			m_vpText[i]->init (m_overlay, w*1/2+40, CELL_SIZE, w/2, CELL_SIZE) ;
		}
		addChild (m_vpText[i]) ;
	}
		
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextAreaOgre ;
		m_vpText[i]->init (m_overlay, CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*(i-1), CELL_SIZE*10, CELL_SIZE) ;
		addChild (m_vpText[i]) ;
	}

#elif _GAMEENGINE_2D_
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		m_vpBtn[i] = new CTextButton ;

		if (i == 0)
		{//�H�U���˳���
			m_vpBtn[i]->init (0, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 1)
		{
			m_vpBtn[i]->init (0, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 2)
		{
			m_vpBtn[i]->init (0, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 3)
		{
			m_vpBtn[i]->init (CELL_SIZE*11, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 4)
		{
			m_vpBtn[i]->init (CELL_SIZE*11, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 5)
		{
			m_vpBtn[i]->init (CELL_SIZE*11, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 6)
		{
			m_vpBtn[i]->init (CELL_SIZE*6-10, CELL_SIZE*17, CELL_SIZE*3, CELL_SIZE*3, i) ;
		}else if (i == 7)
		{//UI�W��(�D����T)
			m_vpBtn[i]->init (0, 0, w, CELL_SIZE, i) ;
		}else if (i == 8)
		{//�D���W��
			m_vpBtn[i]->init (0, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 9)
		{//���Ťθg���
			m_vpBtn[i]->init (w/2, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 10)
		{//�ݩ�
			m_vpBtn[i]->init (CELL_SIZE*14, CELL_SIZE*2, CELL_SIZE*10, CELL_SIZE*18, i) ;
		}else if (i == 11)
		{//�D����
			m_vpBtn[i]->init (CELL_SIZE*3, CELL_SIZE*2, CELL_SIZE*8, CELL_SIZE*15, i) ;
		}
		addChild (m_vpBtn[i]) ;
	}

	//�����򥻸�T
	for (int i = 0; i<3; i++)
	{
		m_vpText[i] = new CTextArea ;
		if (i == 0)
		{
			m_vpText[i]->init (w/2-30, 0, w, CELL_SIZE) ;
			m_vpText[i]->setText ("�����T", 1, 1, 1) ;
		}else if (i == 1)
		{
			m_vpText[i]->init (w/4-30, CELL_SIZE, w/2, CELL_SIZE) ;
		}else if (i == 2)
		{
			m_vpText[i]->init (w*1/2+40, CELL_SIZE, w/2, CELL_SIZE) ;
		}
		addChild (m_vpText[i]) ;
	}
		
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		m_vpText[i] = new CTextArea ;
		m_vpText[i]->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*(i-1), CELL_SIZE*10, CELL_SIZE) ;
		addChild (m_vpText[i]) ;
	}
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   updateAdvAttr(m_pPlayer);
   updatePlayerAttr(m_pPlayer);
   
   // �˳���M��
   updatePlayerEquip(m_pPlayer, MAIN_HAND, -1);
   updatePlayerEquip(m_pPlayer, OFF_HAND, -1);
   updatePlayerEquip(m_pPlayer, CHEST, -1);
   updatePlayerEquip(m_pPlayer, LEGS, -1);
   updatePlayerEquip(m_pPlayer, SHOULDER, -1);
   updatePlayerEquip(m_pPlayer, GLOVE, -1);
   updatePlayerEquip(m_pPlayer, BOOT, -1);

   // ��ܪ��a�˳�
   std::map<EquipSlot, int> vtEquip = m_pPlayer->getEquip();
   std::map<EquipSlot, int>::iterator it = vtEquip.begin();
   while(it != vtEquip.end()) {
      updatePlayerEquip(m_pPlayer, it->first, it->second);
      it++;
   }

   show(false);
}

bool CPlayerInfoWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE;
}

void CPlayerInfoWnd::onRCommand (int btnID)
{
   switch(btnID) {
      case 0: {  // �ӻH����
         m_pPlayer->shedEquip(SHOULDER);
         break;
      }

      case 1: {  // ��M����
         m_pPlayer->shedEquip(GLOVE);
         break;
      }

      case 2: {  // �D��Z��
         m_pPlayer->shedEquip(MAIN_HAND);
         break;
      }

      case 3: {  // �W��
         m_pPlayer->shedEquip(CHEST);
         break;
      }

      case 4: {  // �Ǥl
         m_pPlayer->shedEquip(LEGS);
         break;
      }

      case 5: {  // �Ƥ�Z��
         m_pPlayer->shedEquip(OFF_HAND);
         break;
      }

      case 6: {  // �c�l
         m_pPlayer->shedEquip(BOOT);
         break;
      }
   }
}

WindowClassType CPlayerInfoWnd::getClassType()
{
   return WND_PLAYERINFO;
}

void CPlayerInfoWnd::show(bool bShow)
{
   CWindow::show(bShow);

#ifdef _GAMEENGINE_3D_
   if(bShow)
      m_overlay.getOverlay()->show();
   else
      m_overlay.getOverlay()->hide();
#endif  // #ifdef _GAMEENGINE_3D_
}

void CPlayerInfoWnd::onDrag()
{   
#ifdef _GAMEENGINE_3D_
	m_overlay.setPos(x, y);
#endif  // #ifdef _GAMEENGINE_3D_
}

#ifdef _GAMEENGINE_3D_
void CPlayerInfoWnd::setZOrder(int order)
{
	m_overlay.setZOrder(order);
}
#endif  // #ifdef _GAMEENGINE_3D_

void CPlayerInfoWnd::updateAdvAttr(CUnitObject *pUnitObject)
{
   //��s�򥻸�T
   char buf[50];
   memset(buf, 0, sizeof(buf));
   m_vpText[1]->setText(pUnitObject->getName(), 1, 1, 1);
	   

   // ��s�ݩʸ��
   AdvancedAttribute advAttr = pUnitObject->getAdvAttr();
   for(int i = 3; i < TEXT_COUNT; i++) {
	   char buf[50];
      memset(buf, 0, sizeof(buf));

	   if(i == 3)
         sprintf_s (buf, sizeof (buf), "�ͩR�O   %5d", advAttr.iHP) ;  
	   else if (i == 4)
         sprintf_s (buf, sizeof (buf), "�믫�O   %5d", advAttr.iMP) ;  
	   else if (i == 5)
         sprintf_s (buf, sizeof (buf), "�̤j�ͩR�O %5d", advAttr.iHPMax) ;  
	   else if (i == 6)
         sprintf_s (buf, sizeof (buf), "�̤j�믫�O %5d", advAttr.iMPMax) ;  
	   else if (i == 7)
         sprintf_s (buf, sizeof (buf), "���z�����O %5d", advAttr.iATK) ;  
	   else if (i == 8)
		   sprintf_s (buf, sizeof (buf), "���z���m�O %5d", advAttr.iDEF) ;  
	   else if (i == 9)
         sprintf_s (buf, sizeof (buf), "���z�R���v %5d", advAttr.iHIT) ;  
	   else if (i == 10)
         sprintf_s (buf, sizeof (buf), "���z�����v %5d", advAttr.iCRI) ;  
	   else if (i == 11)
         sprintf_s (buf, sizeof (buf), "�]�k�����O %5d", advAttr.iMATK) ;  
	   else if (i == 12)
         sprintf_s (buf, sizeof (buf), "�]�k���m�O %5d", advAttr.iMDEF) ;  
	   else if (i == 13)
         sprintf_s (buf, sizeof (buf), "�]�k�R���v %5d", advAttr.iMHIT) ;  
	   else if (i == 14)
         sprintf_s (buf, sizeof (buf), "�]�k�����v %5d", advAttr.iMCRI) ;  
	   else if (i == 15)
         sprintf_s (buf, sizeof (buf), "�޵P���m�O %5d", advAttr.iSDEF) ;  
	   else if (i == 16)
         sprintf_s (buf, sizeof (buf), "�Z�����m�O %5d", advAttr.iWDEF) ;  
	   else if (i == 17)
         sprintf_s (buf, sizeof (buf), "�j�ײv   %5d", advAttr.iFlee) ;  
	   else if (i == 18)
         sprintf_s (buf, sizeof (buf), "���ʳt��  %5.1f", advAttr.fMove) ;  
	   else if (i == 19)
         sprintf_s (buf, sizeof (buf), "�����t��  %5.1f", advAttr.fATKSpeed) ;  
	   else if (i == 20)
         sprintf_s (buf, sizeof (buf), "�I�i�t��  %5.1f", advAttr.fCasting) ;  
	   
	   m_vpText[i]->setText (buf, 1, 1, 1) ;
   }
}

void CPlayerInfoWnd::updatePlayerAttr(CPlayer *pPlayer)
{
   //��s�򥻸�T
   char buf[50];
   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "���� %3d/�g��� %3d", pPlayer->getLevel(), pPlayer->getXP());
	m_vpText[2]->setText(buf, 1, 1, 1);
}

void CPlayerInfoWnd::updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId)
{
#ifdef _GAMEENGINE_3D_
   //��s�˳���
   switch(equipSlot) {
      case SHOULDER: {
         if(itemId == -1)
            m_vpBtn[0]->setImage("Examples/ogreborder");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[0]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case GLOVE: {
         if(itemId == -1)
            m_vpBtn[1]->setImage("Examples/ogreborder");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[1]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case MAIN_HAND: {
         if(itemId == -1)
            m_vpBtn[2]->setImage("Examples/ogreborder");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[2]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case CHEST: {
         if(itemId == -1)
            m_vpBtn[3]->setImage("Examples/ogreborder");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[3]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case LEGS: {
         if(itemId == -1)
            m_vpBtn[4]->setImage("Examples/ogreborder");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[4]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case OFF_HAND: {
         if(itemId == -1)
            m_vpBtn[5]->setImage("Examples/ogreborder");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[5]->setImage(pItemInfo->geticonName());
         }
         break;
	   }

      case BOOT: {
         if(itemId == -1)
            m_vpBtn[6]->setImage("Examples/ogreborder");
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[6]->setImage(pItemInfo->geticonName());
         }
         break;
	   }
   }
#elif _GAMEENGINE_2D_
   //��s�˳���
   switch(equipSlot) {
	   case SHOULDER: {
         if(itemId == -1)
		      m_vpBtn[0]->str = "�ӥ�" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[0]->str = pItemInfo->getName();
         }
         break;
	   }

      case GLOVE: {
         if(itemId == -1)
		      m_vpBtn[1]->str = "��M" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[1]->str = pItemInfo->getName();
         }
         break;
	   }

      case MAIN_HAND: {
         if(itemId == -1)
		      m_vpBtn[2]->str = "�D��Z��" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[2]->str = pItemInfo->getName();
         }
         break;
	   }

      case CHEST: {
         if(itemId == -1)
		      m_vpBtn[3]->str = "��A" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[3]->str = pItemInfo->getName();
         }
         break;
	   }

      case LEGS: {
         if(itemId == -1)
		      m_vpBtn[4]->str = "�Ǥl" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[4]->str = pItemInfo->getName();
         }
         break;
	   }

      case OFF_HAND: {
         if(itemId == -1)
		      m_vpBtn[5]->str = "�Ƥ�Z��" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[5]->str = pItemInfo->getName();
         }
         break;
	   }

      case BOOT: {
         if(itemId == -1)
		      m_vpBtn[6]->str = "�c�l" ;
         else {
            CItemInfo *pItemInfo = CItem::getInfo(itemId);
            m_vpBtn[6]->str = pItemInfo->getName();
         }
         break;
	   }
   }
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
}