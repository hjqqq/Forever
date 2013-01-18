#include "CPlayerInfoWnd.h"
#include "CWindowMan.h"

CPlayerInfoWnd::~CPlayerInfoWnd()
{
   if(m_pPlayer != NULL)
      m_pPlayer->removeModelEventListener(this);
}

void CPlayerInfoWnd::init (int _x, int _y, CPlayer *pPlr)
{
	m_pPlayer = pPlr;
   m_pPlayer->addModelEventListener(this);
   
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
   CPlayer *pPlayer = dynamic_cast<CPlayer *>(pUnitObject);
   if(pPlayer != NULL) {
#ifdef _GAMEENGINE_3D_
      //��s�˳���
      for (int i = 0; i<BUTTON_COUNT; i++)
	   {
		   if (i == 0)
		   {
            int itemID = pPlayer->getEquip(SHOULDER);
            if(itemID == -1)
               m_vpBtn[i]->setImage("Examples/ogreborder");
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->setImage(pItemInfo->geticonName());
            }
		   }else if (i == 1)
		   {
            int itemID = pPlayer->getEquip(GLOVE);
            if(itemID == -1)
               m_vpBtn[i]->setImage("Examples/ogreborder");
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->setImage(pItemInfo->geticonName());
            }
		   }else if (i == 2)
		   {
            int itemID = pPlayer->getEquip(MAIN_HAND);
            if(itemID == -1)
               m_vpBtn[i]->setImage("Examples/ogreborder");
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->setImage(pItemInfo->geticonName());
            }
		   }else if (i == 3)
		   {
            int itemID = pPlayer->getEquip(CHEST);
            if(itemID == -1)
               m_vpBtn[i]->setImage("Examples/ogreborder");
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->setImage(pItemInfo->geticonName());
            }
		   }else if (i == 4)
		   {
            int itemID = pPlayer->getEquip(LEGS);
            if(itemID == -1)
               m_vpBtn[i]->setImage("Examples/ogreborder");
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->setImage(pItemInfo->geticonName());
            }
		   }else if (i == 5)
		   {
            int itemID = pPlayer->getEquip(OFF_HAND);
            if(itemID == -1)
               m_vpBtn[i]->setImage("Examples/ogreborder");
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->setImage(pItemInfo->geticonName());
            }
		   }else if (i == 6)
		   {
            int itemID = pPlayer->getEquip(BOOT);
            if(itemID == -1)
               m_vpBtn[i]->setImage("Examples/ogreborder");
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->setImage(pItemInfo->geticonName());
            }
		   }
	   }
#elif _GAMEENGINE_2D_
      //��s�˳���
      for(int i = 0; i < BUTTON_COUNT; i++) {
		   if(i == 0) {
            int itemID = pPlayer->getEquip(SHOULDER);
            if(itemID == -1)
			      m_vpBtn[i]->str = "�ӥ�" ;
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->str = pItemInfo->getName();
            }
		   }
         else if(i == 1) {
            int itemID = pPlayer->getEquip(GLOVE);
            if(itemID == -1)
			      m_vpBtn[i]->str = "��M" ;
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->str = pItemInfo->getName();
            }
		   }
         else if(i == 2) {
            int itemID = pPlayer->getEquip(MAIN_HAND);
            if(itemID == -1)
			      m_vpBtn[i]->str = "�D��Z��" ;
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->str = pItemInfo->getName();
            }
		   }
         else if(i == 3) {
            int itemID = pPlayer->getEquip(CHEST);
            if(itemID == -1)
			      m_vpBtn[i]->str = "��A" ;
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->str = pItemInfo->getName();
            }
		   }
         else if(i == 4) {
            int itemID = pPlayer->getEquip(LEGS);
            if(itemID == -1)
			      m_vpBtn[i]->str = "�Ǥl" ;
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->str = pItemInfo->getName();
            }
		   }
         else if(i == 5) {
            int itemID = pPlayer->getEquip(OFF_HAND);
            if(itemID == -1)
			      m_vpBtn[i]->str = "�Ƥ�Z��" ;
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->str = pItemInfo->getName();
            }
		   }
         else if(i == 6) {
            int itemID = pPlayer->getEquip(BOOT);
            if(itemID == -1)
			      m_vpBtn[i]->str = "�c�l" ;
            else {
               CItemInfo *pItemInfo = CItem::getInfo(itemID);
               m_vpBtn[i]->str = pItemInfo->getName();
            }
		   }
	   }
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

      //��s�򥻸�T
	   for(int i = 1; i < 3; i++) {
		   char buf[50];
         memset(buf, 0, sizeof(buf));

		   if(i == 1) {
            m_vpText[i]->setText(pPlayer->getName(), 1, 1, 1);
		   }
         else if(i == 2) {
            sprintf_s(buf, sizeof(buf), "���� %3d/�g��� %3d", pPlayer->getLevel(), pPlayer->getXP());
			   m_vpText[i]->setText(buf, 1, 1, 1);
		   }
	   }

      // ��s�ݩʸ��
      AdvancedAttribute advAttr = pPlayer->getAdvAttr();
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
}

void CPlayerInfoWnd::updateBackpack(CUnitObject *pUnitObject)
{
}

void CPlayerInfoWnd::updateSkill(CUnitObject *pUnitObject)
{
}

void CPlayerInfoWnd::updateHotKeyItem(int field, HotKeyItem *pHotKeyItem)
{
}

void CPlayerInfoWnd::updateCoolDown(CSkill *pSkill)
{
}