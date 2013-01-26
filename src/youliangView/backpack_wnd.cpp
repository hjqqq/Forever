#include "backpack_wnd.h"
#include "hotkey_wnd.h"
#include "item.h"
#include "image_button.h"
#include "player_info_wnd.h"


void BackpackWnd::upDate (Player* pb)
{
	pPlayer = pb ;
#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
//	overlayUI.getOverlay ()->hide () ;
	overlayUI.setImage ("backpack") ;

	for (int i = 0; i<3; i++)
		for (int m = 0; m<9; m++)
		{		
			vpBtn[i*9+m] = new ImageButton ;
			vpBtn[i*9+m]->init (overlayUI, m*58+14, i*59+58, ICON_SIZE, ICON_SIZE, i*9+m) ;
			Item* pItem = pPlayer->backpack.getItem (i*9+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{
					vpBtn[i*9+m]->setImage ((const Ogre::String)pInfo->image) ;
				}
			}
						
			addChild (vpBtn[i*9+m]) ;
		}
/*
	ImageButton* pBtn = new ImageButton ;
	pBtn->init (overlayUI, w-CELL_SIZE/3, 0, CELL_SIZE/3, CELL_SIZE/3, 24) ;
	//pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	//��ܰ��|�ƶq
	for (int i = 0; i<3; i++)
		for (int m = 0; m<9; m++)
		{		
			vpText[i*9+m] = new TextArea ;
			vpText[i*9+m]->init (overlayUI, m*58+43, i*59+88, 20, 20) ;
			Item* pItem = pPlayer->backpack.getItem (i*9+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{ 
					char buf[256] ;
					sprintf_s (buf, sizeof (buf), "%d", pItem->getStack ()) ;
					vpText[i*9+m]->setText (buf, 0, 1, 0) ;
				}
			}
			
			addChild (vpText[i*9+m]) ;
		}
	//��ܦ������W��(�I�])�Φh�֪���	
	for (int i = 0; i<2; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;

		if (i == 0)
		{
			vpText[i]->init (overlayUI, 260, 15, 40, 20) ;
			vpText[i]->setText ("�I�]", 1, 0, 0) ;
		}else if (i == 1)
		{
			vpText[i]->init (overlayUI, 360, 254, 200, 20) ;
			sprintf_s (buf, sizeof (buf), "����           %d", pPlayer->money) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}

		addChild (vpText[i]) ;
	}
#else _PROJECT_GDI_
	//��ܭI�]�̪��D��
	for (int i = 0; i<3; i++)
		for (int m = 0; m<9; m++)
		{		
			vpBtn[i*9+m] = new TextButton ;
			vpBtn[i*9+m]->init (m*58+14, i*59+58, ICON_SIZE, ICON_SIZE, i*9+m) ;
			Item* pItem = pPlayer->backpack.getItem (i*9+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{ 
					vpBtn[i*9+m]->str = pInfo->name ;
				}
			}
						
			addChild (vpBtn[i*9+m]) ;
		}
/*
	ImageButton* pBtn = new ImageButton ;
	pBtn->init (overlayUI, w-CELL_SIZE/3, 0, CELL_SIZE/3, CELL_SIZE/3, 24) ;
	//pBtn->str = "X" ;
	addChild (pBtn) ;
*/
	//��ܰ��|�ƶq
	for (int i = 0; i<3; i++)
		for (int m = 0; m<9; m++)
		{		
			vpText[i*9+m] = new TextArea ;
			vpText[i*9+m]->init (m*58+43, i*59+88, 20, 20) ;
			Item* pItem = pPlayer->backpack.getItem (i*9+m) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{ 
					char buf[256] ;
					sprintf_s (buf, sizeof (buf), "%d", pItem->getStack ()) ;
					vpText[i*9+m]->setText (buf, 0, 1, 0) ;
				}
			}
			
			addChild (vpText[i*9+m]) ;
		}
	//��ܦ������W��(�I�])�Φh�֪���	
	for (int i = 0; i<2; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;

		if (i == 0)
		{
			vpText[i]->init (260, 15, 40, 20) ;
			vpText[i]->setText ("�I�]", 1, 0, 0) ;
		}else if (i == 1)
		{
			vpText[i]->init (360, 254, 40, 20) ;
			sprintf_s (buf, sizeof (buf), "����           %d", pPlayer->money) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}

		addChild (vpText[i]) ;
	}
#endif	
}

//�I�]����
void BackpackWnd::init (int _x, int _y, Player* pb, HotKeyWnd* pw, PlayerInfoWnd* pw2 ,ItemInfoWnd* pi)
{	
	bVisible = true ;
	pPlayer = pb ;
	phkWnd = pw ;
	ppinWnd = pw2 ;
	pItemInfoWnd = pi ;

	x = _x ;
	y = _y ;
	w = 540 ;
	h = 288 ;

	upDate (pPlayer) ;
}

bool BackpackWnd::canDrag (int tx, int ty)
{
	return ty < 40 ;
}

void BackpackWnd::onCommand (int id)
{
/*	Item* pItem = pPlayer->backpack.getItem (id) ;
	if (pItem != NULL)
	{
		ItemInfo* pInfo = pItem->getInfo () ;
		if (pInfo != NULL)
		{ 
			int itemID = pItem->getID () ;
			if (pInfo->type == ItemInfo::ITEM_EQUIP)
			{
				//��W�h,�I�]��l�s��,
//				pPlayer->wearEquip (itemID) ;
//				ppinWnd->wearEquip (itemID) ;
//				pItem->clear () ;

				upDate (pPlayer) ;

			}else if (pInfo->type == ItemInfo::ITEM_FOOD)
			{
				//�i�H�Y��,�D��s��				
				phkWnd->addFoodHotKey (id, itemID) ;
			}
		}
	}*/
}
void BackpackWnd::onCommandFocus (int id)
{
	Item* pItem = pPlayer->backpack.getItem (id) ;
	if (pItem != NULL)
	{
		ItemInfo* pInfo = pItem->getInfo () ;
		if (pInfo != NULL)
		{
			pItemInfoWnd->setItem (pInfo->name) ;	
			pItemInfoWnd->setPos (x+(id%9)*58+65, y+(id/9)*59) ; 
			setInfoWnd (pItemInfoWnd) ;
			pItemInfoWnd->show (true) ;
		}else
		{
			pItemInfoWnd->show (false) ;
		}
	}else
	{
		pItemInfoWnd->show (false) ;
	}
}


#ifdef _PROJECT_OGRE_3D_
void BackpackWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void BackpackWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void BackpackWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

