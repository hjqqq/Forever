#include "CWindowMan.h"

CWindowMan::CWindowMan ()
{
	pDragWnd = NULL ;
	bInDrag = false ;
}

void CWindowMan::addWnd (CWindow* pw)
{
	pw->pParent = NULL ;
	vpWindow.push_back (pw) ;
}

void CWindowMan::doDrag (HWND hWnd, CKeyMan& keyMan)
{
	//�즲������
	if (keyMan.isDown (KEY_LBUTTON))
	{
		//�~������
		int dx = clientX - dragX ;//�ƹ��즲�h��
		int dy = clientY - dragY ;//�ƹ��즲�h��

		pDragWnd->x += dx ;
		pDragWnd->y += dy ;

		pDragWnd->onMove () ;

		dragX = clientX ;
		dragY = clientY ;
	}else
	{
		//��}
		bInDrag = false ;
	}
}

bool CWindowMan::work (HWND hWnd, 
							CKeyMan& keyMan)
{
	bool bPressWindow = false ;

	getMouseScreenPos (screenX, screenY) ;
	getMousePos (hWnd, clientX, clientY) ;

	if (bInDrag)
	{
		doDrag (hWnd, keyMan) ;
	}else
	{
		//���O�즲����
		if (keyMan.isPress (KEY_LBUTTON))
		{
			//���U�h������
			VP_WINDOW::iterator pi = vpWindow.begin () ;
			while (pi != vpWindow.end ())
			{
				if ((*pi)->checkPoint (clientX, clientY))
				{
					int tx = clientX ;
					int ty = clientY ;

					if ((*pi)->canDrag (tx-(*pi)->x, 
										ty-(*pi)->y))
					{
						//�i�H�즲
						bInDrag = true ;
					}else
					{
						//���i�H�즲
						(*pi)->onLClick (tx, ty) ;
					}

					//������
					bPressWindow = true ;

					dragX = clientX ;
					dragY = clientY ;

					vpWindow.push_front (*pi) ;

					vpWindow.erase (pi) ;
					pDragWnd = vpWindow.front () ;

					break ;
				}

				++ pi ;
			}
		}
      else if(keyMan.isPress(KEY_RBUTTON)) {
         //���U�h������
			VP_WINDOW::iterator pi = vpWindow.begin();
         while(pi != vpWindow.end()) {
            if((*pi)->checkPoint(clientX, clientY)) {
					int tx = clientX;
					int ty = clientY;

               bInDrag = false;
               (*pi)->onRClick(tx, ty);

               //������
					bPressWindow = true;

               break;
            }

            pi++;
         }
		}
      else if(keyMan.isPress(KEY_P)) {
         bool bPlayerInfoWndVisible = false;
         VP_WINDOW::iterator pi = vpWindow.begin();
         while(pi != vpWindow.end()) {
            if((*pi)->getClassType() == WND_PLAYERINFO) {
               (*pi)->bVisible = !(*pi)->bVisible;
               bPlayerInfoWndVisible = (*pi)->bVisible;
            }
            else if((*pi)->getClassType() == WND_BACKPACK)
               (*pi)->bVisible = bPlayerInfoWndVisible;

            pi++;
         }
      }
      else if(keyMan.isPress(KEY_B)) {
         VP_WINDOW::iterator pi = vpWindow.begin();
         while(pi != vpWindow.end()) {
            if((*pi)->getClassType() == WND_BACKPACK) {
               (*pi)->bVisible = !(*pi)->bVisible;
               break;
            }
            pi++;
         }
      }
      else if(keyMan.isPress(KEY_K)) {
         VP_WINDOW::iterator pi = vpWindow.begin();
         while(pi != vpWindow.end()) {
            if((*pi)->getClassType() == WND_SKILL) {
               (*pi)->bVisible = !(*pi)->bVisible;
               break;
            }
            pi++;
         }
      }
	}

	return bPressWindow ;
}

#ifdef _GAMEENGINE_2D_
void CWindowMan::draw (HDC hdc)
{
	VP_WINDOW::reverse_iterator pi = vpWindow.rbegin () ;
	while (pi != vpWindow.rend ())
	{
		if ((*pi)->bVisible)
			(*pi)->draw (hdc, 0, 0) ;
		++ pi ;
	}
}
#endif

void CWindowMan::deleteAllWindow ()
{
	VP_WINDOW::reverse_iterator pi = 
			vpWindow.rbegin () ;
	while (pi != vpWindow.rend ())
	{
		delete *pi ;

		++pi ;
	}
}