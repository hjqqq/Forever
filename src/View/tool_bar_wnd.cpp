#include "tool_bar_wnd.h"
#include "item.h"

#ifdef _PROJECT_OGRE_3D_
	#include "image_button.h"
#endif

//�I�]����
void ToolBarWnd::init (Window* pw0, 
					   Window* pw1, 
					   Window* pw2, Window* pw3,
					   int _x, int _y)
	{
		pTA = NULL ;

		vpWnd[0] = pw0 ;
		vpWnd[1] = pw1 ;
		vpWnd[2] = pw2 ;
		vpWnd[3] = pw3 ;

		x = _x ;
		y = _y ;

		w = (UI_COUNT+1)*CELL_SIZE ;
		h = CELL_SIZE ;

#ifdef _PROJECT_OGRE_3D_
		overlayTB.init (x, y, w, h) ;
#endif

		for (int i = 0; i<UI_COUNT; i++)
		{
#ifdef _PROJECT_GDI_
			TextButton* pBtn = new TextButton ;

			pBtn->init ((i+1)*CELL_SIZE, 0, CELL_SIZE,
							CELL_SIZE, i) ;

			if (i == 0)
				pBtn->str = "�I�]" ;
			else if (i == 1)
				pBtn->str = "���A" ;
			else if (i == 2)
				pBtn->str = "�ޯ�" ;
			else if (i == 3)
				pBtn->str = "�a��" ;

#else _PROJECT_OGRE_3D_
			ImageButton* pBtn = new ImageButton ;

			pBtn->init (overlayTB, (i+1)*CELL_SIZE, 0, CELL_SIZE,
							CELL_SIZE, i) ;
			pBtn->setImage ("droplet_x") ;


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

		for (int i = 0; i<UI_COUNT; i++)
		{
			pTA = new TextArea ;
#ifdef _PROJECT_GDI_
			pTA->init ((i+1)*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE) ;
				
#else
			pTA->init (overlayTB, (i+1)*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE) ;
			if (i == 0)
				pTA->setText ("�I�]", 1, 1, 1) ;
			else if (i == 1)
				pTA->setText ("�D��", 1, 1, 1) ;
			else if (i == 2)
				pTA->setText ("�ޯ�", 1, 1, 1) ;
			else if (i == 3)
				pTA->setText ("�a��", 1, 1, 1) ;
#endif
			
			addChild (pTA) ;
		}

		



	}

bool ToolBarWnd::canDrag (int tx, int ty)
{
	return tx < CELL_SIZE ;
}

void ToolBarWnd::onCommand (int btnID)
{
//	pTA->setText ("???", 1, 1, 1) ;


	vpWnd[btnID]->bVisible = 
		!(vpWnd[btnID]->bVisible) ;
}

void ToolBarWnd::onMove ()
{
#ifdef _PROJECT_OGRE_3D_
	overlayTB.setPos (x, y) ;
#endif
}

void ToolBarWnd::setZOrder (int z)
{
#ifdef _PROJECT_OGRE_3D_
	overlayTB.setZOrder (z) ;
#endif
}

/*
void ToolBarWnd::onClick (int tx, int ty)
{
	int offset = (tx/CELL_SIZE)-1 ;
	if (offset >= 0)
	{
		vpWnd[offset]->bVisible = 
			!(vpWnd[offset]->bVisible) ;
	}

//	pPlayer->useItem (offset) ;
}
*/

	/*
	void ToolBarWnd::draw (HDC hdc)
	{
		Window::draw (hdc) ;

		for (int i = 0; i<UI_COUNT; i++)
		{
			Rectangle (hdc, x+((i+1)*CELL_SIZE),
							y, x+((i+2)*CELL_SIZE),
							y+CELL_SIZE) ;
		}

	}
	*/
