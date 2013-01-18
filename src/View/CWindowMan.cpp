#include "CWindowMan.h"

CWindowMan::CWindowMan ()
{
	m_pDragWnd = NULL;
   m_pBackpackWnd = NULL;
	m_bInDrag = false ;
   m_pWindowList = new std::list<CWindow *>();
}

CWindowMan::~CWindowMan()
{
   if(m_pWindowList != NULL) {
      deleteAllWindow();
      delete m_pWindowList;
      m_pWindowList = NULL;
   }
}

void CWindowMan::addWnd(CWindow *pWnd)
{
	pWnd->pParent = NULL;
	m_pWindowList->push_back(pWnd);
   pWnd->setWindowMan(this);

   if(pWnd->getClassType() == WND_BACKPACK)
      m_pBackpackWnd = pWnd;
}

void CWindowMan::deleteAllWindow()
{
	std::list<CWindow *>::reverse_iterator it = m_pWindowList->rbegin();
	while(it != m_pWindowList->rend ()) {
		delete (*it);
		it++;
	}
   m_pWindowList->clear();

   m_pDragWnd = NULL;
   m_pBackpackWnd = NULL;
}

#ifdef _GAMEENGINE_2D_
bool CWindowMan::work(HWND hWnd, CKeyMan &keyMan)
{
	bool bPressWindow = false;

	getMousePos(hWnd, m_iClientX, m_iClientY);

	if(m_bInDrag) {
		doDrag(hWnd, keyMan);
	}
   else {
		//���O�즲�ʧ@

		if(keyMan.isPress(KEY_LBUTTON)) {
			//���U�h������

			std::list<CWindow *>::iterator it = m_pWindowList->begin();
			while(it != m_pWindowList->end ()) {
				if((*it)->checkPoint(m_iClientX, m_iClientY)) {
					int tx = m_iClientX;
					int ty = m_iClientY;

					if((*it)->canDrag(tx - (*it)->x, ty - (*it)->y)) {
						//�i�H�즲
						m_bInDrag = true;
					}
               else {
						//���i�H�즲
						(*it)->onLClick(tx, ty);
					}

					//������
					bPressWindow = true;

					m_iDragX = m_iClientX;
					m_iDragY = m_iClientY;

					m_pWindowList->push_front(*it);
					m_pWindowList->erase(it);
					m_pDragWnd = m_pWindowList->front();
					break ;
				}

				it++;
			}
		}
      else if(keyMan.isPress(KEY_RBUTTON)) {
         //���U�h������
			std::list<CWindow *>::iterator it = m_pWindowList->begin();
         while(it != m_pWindowList->end()) {
            if((*it)->checkPoint(m_iClientX, m_iClientY)) {
					int tx = m_iClientX;
					int ty = m_iClientY;

               m_bInDrag = false;
               (*it)->onRClick(tx, ty);

               //������
					bPressWindow = true;

               break;
            }

            it++;
         }
		}
      else if(keyMan.isPress(KEY_P)) {
         bool bPlayerInfoWndVisible = false;
         std::list<CWindow *>::iterator it = m_pWindowList->begin();
         while(it != m_pWindowList->end()) {
            if((*it)->getClassType() == WND_PLAYERINFO) {
               (*it)->show(!(*it)->isVisible());
               bPlayerInfoWndVisible = (*it)->isVisible();
               break;
            }
            it++;
         }

         it = m_pWindowList->begin();
         while(it != m_pWindowList->end()) {
            if((*it)->getClassType() == WND_BACKPACK) {
               (*it)->show(bPlayerInfoWndVisible);
               break;
            }
            it++;
         }
      }
      else if(keyMan.isPress(KEY_B)) {
         std::list<CWindow *>::iterator it = m_pWindowList->begin();
         while(it != m_pWindowList->end()) {
            if((*it)->getClassType() == WND_BACKPACK) {
               (*it)->show(!(*it)->isVisible());
               break;
            }
            it++;
         }
      }
      else if(keyMan.isPress(KEY_K)) {
         std::list<CWindow *>::iterator it = m_pWindowList->begin();
         while(it != m_pWindowList->end()) {
            if((*it)->getClassType() == WND_SKILL) {
               (*it)->show(!(*it)->isVisible());
               break;
            }
            it++;
         }
      }
	}

	return bPressWindow ;
}

void CWindowMan::draw(HDC hdc)
{
   std::list<CWindow *>::reverse_iterator it = m_pWindowList->rbegin();
   while(it != m_pWindowList->rend()) {
      if((*it)->isVisible() == true)
	      (*it)->draw(hdc, 0, 0);

      it++;
   }
}
#endif  // #ifdef _GAMEENGINE_2D_

#ifdef _GAMEENGINE_2D_
void CWindowMan::doDrag(HWND hWnd, CKeyMan &keyMan)
{
	//�즲������
	if(keyMan.isDown(KEY_LBUTTON)) {
		//�~������

		int dx = m_iClientX - m_iDragX;  //�ƹ��즲�h��
		int dy = m_iClientY - m_iDragY;  //�ƹ��즲�h��

		m_pDragWnd->x += dx;
		m_pDragWnd->y += dy;

      if(m_pDragWnd->getClassType() == WND_PLAYERINFO) {
		   m_pDragWnd->onDrag();

         if(m_pBackpackWnd->isVisible() == true) {
            m_pBackpackWnd->x = m_pDragWnd->x;
            m_pBackpackWnd->y = m_pDragWnd->y + m_pDragWnd->h + 1;
            m_pBackpackWnd->onDrag();
         }
      }
      else
         m_pDragWnd->onDrag();

		m_iDragX = m_iClientX;
		m_iDragY = m_iClientY;
	}
   else {
		//��}

		m_bInDrag = false;
	}
}
#endif  // #ifdef _GAMEENGINE_2D_