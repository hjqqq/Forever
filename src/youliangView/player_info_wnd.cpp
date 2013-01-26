#include "player_info_wnd.h"
#include "image_button.h"
#include "backpack.h"

void PlayerInfoWnd::init (int _x, int _y, Player* pPlr)
{
	bVisible = true ;
	pPlayer = pPlr ;
	x = _x ;
	y = _y ;
	w = 540 ;
	h = 400 ;

	for (int i = 0; i<BUTTON_COUNT; i++)
		playerInfo[i].itemID = -1 ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
//	overlayUI.getOverlay ()->hide () ;
	overlayUI.setImage ("playerInfo") ;

for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new ImageButton ;

		if (i == 0)//�C
		{
			vpBtn[i]->init (overlayUI, 11, 67, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 1)//��
		{
			vpBtn[i]->init (overlayUI, 228, 67, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 2)//����
		{
			vpBtn[i]->init (overlayUI, 11, 123, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 3)//����
		{
			vpBtn[i]->init (overlayUI, 228, 123, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 4)//�W��
		{
			vpBtn[i]->init (overlayUI, 11, 179, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 5)//�ӥ�
		{
			vpBtn[i]->init (overlayUI, 228, 179, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 6)//�Ǥl
		{
			vpBtn[i]->init (overlayUI, 11, 235, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 7)//��M
		{
			vpBtn[i]->init (overlayUI, 228, 235, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 8)//�٫�
		{
			vpBtn[i]->init (overlayUI, 11, 291, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 9)//�٫�
		{
			vpBtn[i]->init (overlayUI, 228, 291, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 10)//�c�l
		{
			vpBtn[i]->init (overlayUI, 11, 347, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 11)//�y�a
		{
			vpBtn[i]->init (overlayUI, 228, 347, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 12)//�ݩ�
		{
			vpBtn[i]->init (overlayUI, 285, 65, 250, 333, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 13)//�D����
		{
			vpBtn[i]->init (overlayUI, 64, 65, 160, 333, i) ;
			vpBtn[i]->setImage ("") ;
		}
		addChild (vpBtn[i]) ;
	}

	//�����򥻸�T
	for (int i = 0; i<3; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;
		if (i == 0)
		{
			vpText[i]->init (overlayUI, 240, 8, 540, 20) ;
			vpText[i]->setText ("�����T", 1, 1, 1) ;
		}else if (i == 1)
		{
			vpText[i]->init (overlayUI, 105, 38, 270, 20) ;
			vpText[i]->setText ("�D���W��", 1, 1, 1) ;
		}else if (i == 2)
		{
			vpText[i]->init (overlayUI, 310, 38, 270, 20) ;
			sprintf_s (buf, sizeof (buf), "���� %d  / �g���    %d", pPlayer->data.m_level, pPlayer->data.m_xp) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
		
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, 300, (i-3)*18+66, 200, 20) ;
		char buf[256] ;		
		if (i == 3)
		{
			sprintf_s (buf, sizeof (buf), "�ͩR�O                  %d", pPlayer->data.iHP) ;
		}else if (i == 4)
		{
			sprintf_s (buf, sizeof (buf), "�믫�O                  %d", pPlayer->data.iMP) ;
		}else if (i == 5)
		{
			sprintf_s (buf, sizeof (buf), "�̤j�ͩR�O          %d", pPlayer->data.iHPMax) ;
		}else if (i == 6)
		{
			sprintf_s (buf, sizeof (buf), "�̤j�믫�O          %d", pPlayer->data.iMPMax) ;
		}else if (i == 7)
		{
			sprintf_s (buf, sizeof (buf), "���z�����O          %d", pPlayer->data.iATK) ;
		}else if (i == 8)
		{
			sprintf_s (buf, sizeof (buf), "���z���m�O          %d", pPlayer->data.iDEF) ;
		}else if (i == 9)
		{
			sprintf_s (buf, sizeof (buf), "���z�R���v          %d", pPlayer->data.iHIT) ;
		}else if (i == 10)
		{
			sprintf_s (buf, sizeof (buf), "���z�����v          %d", pPlayer->data.iCRI) ;
		}else if (i == 11)
		{
			sprintf_s (buf, sizeof (buf), "�]�k�����O          %d", pPlayer->data.iMATK) ;
		}else if (i == 12)
		{
			sprintf_s (buf, sizeof (buf), "�]�k���m�O          %d", pPlayer->data.iMDEF) ;
		}else if (i == 13)
		{
			sprintf_s (buf, sizeof (buf), "�]�k�R���v          %d", pPlayer->data.iMHIT) ;
		}else if (i == 14)
		{
			sprintf_s (buf, sizeof (buf), "�]�k�����v          %d", pPlayer->data.iMCRI) ;
		}else if (i == 15)
		{
			sprintf_s (buf, sizeof (buf), "�޵P���m�O          %d", pPlayer->data.iSDEF) ;
		}else if (i == 16)
		{
			sprintf_s (buf, sizeof (buf), "�Z�����m�O          %d", pPlayer->data.iWDEF) ;
		}else if (i == 17)
		{
			sprintf_s (buf, sizeof (buf), "�j�ײv                  %d", pPlayer->data.iFlee) ;
		}else if (i == 18)
		{
			sprintf_s (buf, sizeof (buf), "���ʳt��              %.1f", pPlayer->data.fMove) ;
		}else if (i == 19)
		{
			sprintf_s (buf, sizeof (buf), "�����t��              %.1f", pPlayer->data.fATKSpeed) ;
		}else if (i == 20)
		{
			sprintf_s (buf, sizeof (buf), "�I�i�t��              %.1f", pPlayer->data.fCasting) ;
		}
		vpText[i]->setText (buf, 1, 1, 1) ;
		addChild (vpText[i]) ;
	}

#else _PROJECT_GDI_

for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new TextButton ;

		if (i == 0)//�C
		{
			vpBtn[i]->init (11, 67, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 1)//��
		{
			vpBtn[i]->init (228, 67, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 2)//����
		{
			vpBtn[i]->init (11, 123, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 3)//����
		{
			vpBtn[i]->init (228, 123, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 4)//�W��
		{
			vpBtn[i]->init (11, 179, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 5)//�ӥ�
		{
			vpBtn[i]->init (228, 179, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 6)//�Ǥl
		{
			vpBtn[i]->init (11, 235, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 7)//��M
		{
			vpBtn[i]->init (228, 235, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 8)//�٫�
		{
			vpBtn[i]->init (11, 291, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 9)//�٫�
		{
			vpBtn[i]->init (228, 291, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 10)//�c�l
		{
			vpBtn[i]->init (11, 347, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 11)//�y�a
		{
			vpBtn[i]->init (228, 347, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 12)//�ݩ�
		{
			vpBtn[i]->init (285, 65, 250, 333, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 13)//�D����
		{
			vpBtn[i]->init (64, 65, 160, 333, i) ;
			vpBtn[i]->str = "" ;
		}
		addChild (vpBtn[i]) ;
	}

	//�����򥻸�T
	for (int i = 0; i<3; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;
		if (i == 0)
		{
			vpText[i]->init (240, 8, 540, 20) ;
			vpText[i]->setText ("�����T", 1, 1, 1) ;
		}else if (i == 1)
		{
			vpText[i]->init (105, 38, 270, 20) ;
			vpText[i]->setText ("�D���W��", 1, 1, 1) ;
		}else if (i == 2)
		{
			vpText[i]->init (310, 38, 270, 20) ;
			sprintf_s (buf, sizeof (buf), "���� %d  / �g���    %d", pPlayer->data.m_level, pPlayer->data.m_xp) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
		
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (300, (i-3)*18+66, 200, 20) ;
		char buf[256] ;		
		if (i == 3)
		{
			sprintf_s (buf, sizeof (buf), "�ͩR�O                  %d", pPlayer->data.iHP) ;
		}else if (i == 4)
		{
			sprintf_s (buf, sizeof (buf), "�믫�O                  %d", pPlayer->data.iMP) ;
		}else if (i == 5)
		{
			sprintf_s (buf, sizeof (buf), "�̤j�ͩR�O          %d", pPlayer->data.iHPMax) ;
		}else if (i == 6)
		{
			sprintf_s (buf, sizeof (buf), "�̤j�믫�O          %d", pPlayer->data.iMPMax) ;
		}else if (i == 7)
		{
			sprintf_s (buf, sizeof (buf), "���z�����O          %d", pPlayer->data.iATK) ;
		}else if (i == 8)
		{
			sprintf_s (buf, sizeof (buf), "���z���m�O          %d", pPlayer->data.iDEF) ;
		}else if (i == 9)
		{
			sprintf_s (buf, sizeof (buf), "���z�R���v          %d", pPlayer->data.iHIT) ;
		}else if (i == 10)
		{
			sprintf_s (buf, sizeof (buf), "���z�����v          %d", pPlayer->data.iCRI) ;
		}else if (i == 11)
		{
			sprintf_s (buf, sizeof (buf), "�]�k�����O          %d", pPlayer->data.iMATK) ;
		}else if (i == 12)
		{
			sprintf_s (buf, sizeof (buf), "�]�k���m�O          %d", pPlayer->data.iMDEF) ;
		}else if (i == 13)
		{
			sprintf_s (buf, sizeof (buf), "�]�k�R���v          %d", pPlayer->data.iMHIT) ;
		}else if (i == 14)
		{
			sprintf_s (buf, sizeof (buf), "�]�k�����v          %d", pPlayer->data.iMCRI) ;
		}else if (i == 15)
		{
			sprintf_s (buf, sizeof (buf), "�޵P���m�O          %d", pPlayer->data.iSDEF) ;
		}else if (i == 16)
		{
			sprintf_s (buf, sizeof (buf), "�Z�����m�O          %d", pPlayer->data.iWDEF) ;
		}else if (i == 17)
		{
			sprintf_s (buf, sizeof (buf), "�j�ײv                  %d", pPlayer->data.iFlee) ;
		}else if (i == 18)
		{
			sprintf_s (buf, sizeof (buf), "���ʳt��              %.1f", pPlayer->data.fMove) ;
		}else if (i == 19)
		{
			sprintf_s (buf, sizeof (buf), "�����t��              %.1f", pPlayer->data.fATKSpeed) ;
		}else if (i == 20)
		{
			sprintf_s (buf, sizeof (buf), "�I�i�t��              %.1f", pPlayer->data.fCasting) ;
		}
		vpText[i]->setText (buf, 1, 1, 1) ;
		addChild (vpText[i]) ;
	}
#endif
}

bool PlayerInfoWnd::canDrag (int tx, int ty)
{
	return ty < 30 ;
}

void PlayerInfoWnd::onCommand (int id)
{
	
}

void PlayerInfoWnd::wearEquip (int _itemID)//�D��s�� 
{
/*	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		ItemInfo* pInfo = Item::getInfo (_itemID) ;
		if (pInfo != NULL)
		{			
			playerInfo[i].itemID = _itemID ;
			if (pInfo->equipPos == ItemInfo::EQUIP_WEAPON && i == PlayerInfoWnd::BUTTON_WEAPON)
			{				
#ifdef _PROJECT_OGRE_3D_
					vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
#else _PROJECT_GDI_
					vpBtn[i]->str = pInfo->name ;
#endif
					break ;							
			}else if (pInfo->equipPos == ItemInfo::EQUIP_SHIELD && i == PlayerInfoWnd::BUTTON_SHIELD)
			{				
#ifdef _PROJECT_OGRE_3D_
					vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
#else _PROJECT_GDI_
					vpBtn[i]->str = pInfo->name ;
#endif
					break ;				
			}			
		}
	}	*/
}

#ifdef _PROJECT_OGRE_3D_
void PlayerInfoWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void PlayerInfoWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void PlayerInfoWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

