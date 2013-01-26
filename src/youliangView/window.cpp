#include "window.h"


bool Window::checkPoint (int tx, int ty)
{
	if (bVisible == false)
		return false ;

	if ((tx >= x) && (tx < (x+w)) &&
		(ty >= y) && (ty < (y+h)))
		return true ;
	else
		return false ;
}

void Window::setInfoWnd (Window* pw)
{
	pWindowMan->setInfoWnd (pw) ;
}

bool Window::canDrag (int tx, int ty)
{
	return true ;
}

void Window::onClick (int tx, int ty)
{
	tx -= x ;
	ty -= y ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			if ((*pi)->checkPoint (tx, ty))
			{
				(*pi)->onClick (tx, ty) ;
				break ;
			}

		++ pi ;
	}

	if (pi == vpWnd.end ())
	{
		//�S����l����
	}
}

void Window::onClickR (int tx, int ty)
{
	tx -= x ;
	ty -= y ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			if ((*pi)->checkPoint (tx, ty))
			{
				(*pi)->onClickR (tx, ty) ;
				break ;
			}

		++ pi ;
	}

	if (pi == vpWnd.end ())
	{
		//�S����l����
	}
}

void Window::onMouseFocus (int tx, int ty)
{
	tx -= x ;
	ty -= y ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			if ((*pi)->checkPoint (tx, ty))
			{
				(*pi)->onMouseFocus (tx, ty) ;
				break ;
			}

		++ pi ;
	}

	if (pi == vpWnd.end ())
	{
		//�S����l����
	}
}

void Window::show (bool b)
{
	bVisible = b ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		(*pi)->show (bVisible) ;
		++ pi ;
	}
}

bool Window::isVisible ()
{
	return bVisible ;
}

void Window::addChild (Window* pw)
{
	pw->pParent = this ;
	vpWnd.push_back (pw) ;
}

void Window::delChild (Window* pw)
{
	vpWnd.remove (pw) ;
}

void Window::draw (HDC hdc, int ox, int oy)
{
	Rectangle (hdc, x+ox, y+oy, x+ox+w, y+oy+h) ;

	VP_WND::iterator pi = vpWnd.begin () ;
	while (pi != vpWnd.end ())
	{
		if ((*pi)->bVisible)
			(*pi)->draw (hdc, x+ox, y+oy) ;
		++ pi ;
	}
}


WindowMan::WindowMan ()
{
	pDragWnd = NULL ;
	bInDrag = false ;
	pInfoWindow = NULL ;

//		keyLButton.setKey (VK_LBUTTON) ;
}

void WindowMan::addWnd (Window* pw)
{
	pw->pWindowMan = this ;

	pw->pParent = NULL ;
	vpWindow.push_back (pw) ;
}

//########################

void Button::init (int _x, int _y, int _w, int _h, int _id)
{
	x = _x ;
	y = _y ;
	w = _w ;
	h = _h ;
	id = _id ;
}

void Button::onClick (int tx, int ty)
{
	pParent->onCommand (id) ;
}


void Button::onClickR (int tx, int ty)
{
	pParent->onCommandR (id) ;
}

void Button::onMouseFocus (int tx, int ty)
{
	pParent->onCommandFocus (id) ;
}


//########################

void TextButton::draw (HDC hdc, int ox, int oy)
{
	Button::draw (hdc, ox, oy) ;
	TextOut (hdc, x+ox+2, y+oy+2, str, str.length ()) ;
}

#ifdef _PROJECT_GDI_

void TextArea::init (int _x, int _y, int _w, int _h)
{
	x = _x ;
	y = _y ;
	w = _w ;
	h = _h ;
}

void TextArea::setText (const char* ps, float, float, float)
{
	str = ps ;
}

void TextArea::setPos (int _x, int _y)
{
	x = _x ;
	y = _y ;
}

void TextArea::draw (HDC hdc, int ox, int oy)
{
	TextOut (hdc, x+ox+2, y+oy+2, str, str.length ()) ;
}

#endif


void WindowMan::doDrag (HWND hWnd, KeyMan& keyMan)
{
	//�즲������
//	if (keyLButton.isDown ())
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

bool WindowMan::work (HWND hWnd, KeyMan& keyMan)
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
						(*pi)->onClick (tx, ty) ;
					}

					//������
					bPressWindow = true ;

					dragX = clientX ;
					dragY = clientY ;

//					vpWindow.push_front (*pi) ;

//					vpWindow.erase (pi) ;
//					pDragWnd = vpWindow.front () ;

					pDragWnd = (*pi) ;

					break ;
				}

				++ pi ;
			}
		}else if (keyMan.isPress (KEY_RBUTTON))
		{
			//���U�h������
			VP_WINDOW::iterator pi = vpWindow.begin () ;
			while (pi != vpWindow.end ())
			{
				if ((*pi)->checkPoint (clientX, clientY))
				{							
					//���i�H�즲
					(*pi)->onClickR (clientX, clientY) ;				

					//������
					bPressWindow = true ;

					break ;
				}

				++ pi ;
			}
		}else
		{
			//�S�����k��
			//���U�h������
			VP_WINDOW::iterator pi = vpWindow.begin () ;
			while (pi != vpWindow.end ())
			{
				if ((*pi)->checkPoint (clientX, clientY))
				{
					int tx = clientX ;
					int ty = clientY ;

					//��Ы���
					(*pi)->onMouseFocus (tx, ty) ;

					break ;
				}else
				{
					if (pInfoWindow != NULL)
						pInfoWindow->show (false) ;
				}

				++ pi ;
			}

/*			if (pi == vpWindow.end ())
			{
				if (pInfoWindow != NULL)
					pInfoWindow->show (false) ;
			}*/
		}
	}

	return bPressWindow ;
}


void WindowMan::setInfoWnd (Window* pw)//�]�w��T����
{
	pInfoWindow = pw ;
}

void WindowMan::draw (HDC hdc)
{
	VP_WINDOW::reverse_iterator pi = vpWindow.rbegin () ;
	while (pi != vpWindow.rend ())
	{
		if ((*pi)->bVisible)
			(*pi)->draw (hdc, 0, 0) ;
		++ pi ;
	}

	if (pInfoWindow != NULL)
		if (pInfoWindow->isVisible ())
			pInfoWindow->draw (hdc, 0, 0) ;
}

void WindowMan::deleteAllWindow ()
{
	VP_WINDOW::reverse_iterator pi = 
			vpWindow.rbegin () ;
	while (pi != vpWindow.rend ())
	{
		delete *pi ;

		++pi ;
	}
}
