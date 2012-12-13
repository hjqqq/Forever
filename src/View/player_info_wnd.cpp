#include "player_info_wnd.h"

void PlayerInfoWnd::init (int _x, int _y, UnitData* pu)
{
	pUnitData = pu ;
	x = _x ;
	y = _y ;
	w = CELL_SIZE*24 ;
	h = CELL_SIZE*20 ;

#ifdef _PROJECT_OGRE_3D_
	//	overlay.init (x, y, w, h) ;
#endif
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
#ifdef _PROJECT_GDI_
		TextButton* pBtn = new TextButton ;

		if (i == 0)
		{
			pBtn->init (0, 0, w, CELL_SIZE, i) ;
		}else if (i == 1)
		{
			pBtn->init (0, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 2)
		{
			pBtn->init (w/2, CELL_SIZE, w/2, CELL_SIZE, i) ;
		}else if (i == 3)
		{
			pBtn->init (CELL_SIZE*14, CELL_SIZE*2, CELL_SIZE*10, CELL_SIZE*18, i) ;
		}else if (i == 4)
		{
			pBtn->init (CELL_SIZE*23, 0, CELL_SIZE, CELL_SIZE, i) ;
			pBtn->str = "X" ;
		}else if (i == 5)
		{
			pBtn->init (CELL_SIZE*3, CELL_SIZE*2, CELL_SIZE*8, CELL_SIZE*15, i) ;
		}else if (i == 6)
		{
			pBtn->init (0, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
			pBtn->str = "�ӥ�" ;
		}else if (i == 7)
		{
			pBtn->init (0, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
			pBtn->str = "��M" ;
		}else if (i == 8)
		{
			pBtn->init (0, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
			pBtn->str = "�Z��" ;
		}else if (i == 9)
		{
			pBtn->init (CELL_SIZE*11, CELL_SIZE*2, CELL_SIZE*3, CELL_SIZE*3, i) ;
			pBtn->str = "�W��" ;
		}else if (i == 10)
		{
			pBtn->init (CELL_SIZE*11, CELL_SIZE*7, CELL_SIZE*3, CELL_SIZE*3, i) ;
			pBtn->str = "�Ǥl" ;
		}else if (i == 11)
		{
			pBtn->init (CELL_SIZE*11, CELL_SIZE*12, CELL_SIZE*3, CELL_SIZE*3, i) ;
			pBtn->str = "�޵P" ;
		}else if (i == 12)
		{
			pBtn->init (CELL_SIZE*6-10, CELL_SIZE*17, CELL_SIZE*3, CELL_SIZE*3, i) ;
			pBtn->str = "�c�l" ;
		}


#else _PROJECT_OGRE_3D_
			ImageButton* pBtn = new ImageButton ;

			pBtn->init (overlay, (i+1)*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, i) ;

			/*
			if (i == 0)
				pBtn->setImage ("img_backpack") ;
			else if (i == 1)
				pBtn->setImage ("img_skill") ;
			else if (i == 2)
				pBtn->setImage ("img_status") ;
			else if (i == 3)
				pBtn->setImage ("img_shp") ;
			*/

#endif
		addChild (pBtn) ;
	}

			

			

#ifdef _PROJECT_GDI_
	for (int i = 0; i<TEXT_COUNT; i++)
	{
		pTA = new TextArea ;
		char buf[256] ;

		if (i == 0)
		{
			pTA->init (w/2-30, 0, w, CELL_SIZE) ;
			pTA->setText ("�����T", 1, 1, 1) ;
		}else if (i == 1)
		{
			pTA->init (w/4-30, CELL_SIZE, w/2, CELL_SIZE) ;
			pTA->setText ("�D���W��", 1, 1, 1) ;
		}else if (i == 2)
		{
			pTA->init (w*3/4-30, CELL_SIZE, w/2, CELL_SIZE) ;
			pTA->setText ("�D������/�g���", 1, 1, 1) ;
		}else if (i == 3)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*2, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�ͩR�O                  %d", pUnitData->iHP) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 4)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*3, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�믫�O                  %d", pUnitData->iMP) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 5)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*4, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�̤j�ͩR�O          %d", pUnitData->iHPMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 6)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*5, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�̤j�믫�O          %d", pUnitData->iMPMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 7)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*6, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "���z�����O          %d", pUnitData->iATK) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 8)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*7, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "���z���m�O          %d", pUnitData->iDEF) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 9)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*8, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "���z�R���v          %d", pUnitData->iHIT) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 10)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*9, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "���z�����v          %d", pUnitData->iCRI) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 11)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*10, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�]�k�����O          %d", pUnitData->iMATK) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 12)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*11, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�]�k���m�O          %d", pUnitData->iMDEF) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 13)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*12, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�]�k�R���v          %d", pUnitData->iMHIT) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 14)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*13, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�]�k�����v          %d", pUnitData->iMCRI) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 15)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*14, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�޵P���m�O          %d", pUnitData->iSDEF) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 16)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*15, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�Z�����m�O          %d", pUnitData->iWDEF) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 17)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*16, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�j�ײv                  %d", pUnitData->iFlee) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 18)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*17, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "���ʳt��              %.1f", pUnitData->fMove) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 19)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*18, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�����t��              %.1f", pUnitData->fATKSpeed) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 20)
		{
			pTA->init (CELL_SIZE*14+CELL_SIZE/2, CELL_SIZE*19, CELL_SIZE*10, CELL_SIZE) ;
			sprintf_s (buf, sizeof (buf), "�I�i�t��              %.1f", pUnitData->fCasting) ;
			pTA->setText (buf, 1, 1, 1) ;
		}

		addChild (pTA) ;
	}

#else _PROJECT_OGRE_3D_

#endif
}

bool PlayerInfoWnd::canDrag (int tx, int ty)
{
	return true ;
}

void PlayerInfoWnd::onCommand (int id)
{
}




/*
void PlayerStatusWnd::draw (HDC hdc)
{
	Window::draw (hdc, 0, 0) ;
	char buf[256] ;
	sprintf_s (buf, sizeof(buf), "hp:%d", pUnitData->hp) ;
	TextOut (hdc, x+2, y+2, buf, strlen (buf)) ;
	sprintf_s (buf, sizeof(buf), "mp:%d", pUnitData->mp) ;
	TextOut (hdc, x+2, y+2+20, buf, strlen (buf)) ;
}
*/
