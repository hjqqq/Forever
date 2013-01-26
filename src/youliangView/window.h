#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "key_state.h"
#include "easy_str.h"
#include "player.h"
#include <list>
#ifdef _PROJECT_OGRE_3D_
	#include "overlayUI.h"
#endif
//�N��@�ӹC����������
//�N�ӥi�H�Q�X�R�����I�]����,���A����,���Ȭɭ�

class WindowMan ;
class Window
{
public:
	WindowMan* pWindowMan ;

	Window* pParent ;//���˵���
	typedef std::list <Window*> VP_WND ;
	VP_WND vpWnd ;//�Ҧ����l����

#ifdef _PROJECT_OGRE_3D_
	OverlayUI overlayUI ;//�޲zoverlay
#endif

	int x, y ;//�������y��,���W����
	int w, h ;//�������e��

	bool bVisible ;

	bool checkPoint (int tx, int ty) ;

	void setInfoWnd (Window* pw) ;

	virtual void onMove () {} ;
	virtual void onSwitch () {} ;

	virtual bool canDrag (int tx, int ty) ;
	virtual void onClick (int tx, int ty) ;
	virtual void onClickR (int tx, int ty) ;
	virtual void onMouseFocus (int tx, int ty) ;

	virtual void show (bool) ;
	bool isVisible () ;

	void addChild (Window*) ;
	void delChild (Window*) ;

	virtual void draw (HDC hdc, int ox, int oy) ;
	virtual void setZOrder (int) {} ;

	virtual void onCommand (int) {} ;//�l����,���sbutton,�q��
	virtual void onCommandR (int) {} ;
	virtual void onCommandFocus (int) {} ;

	Window ():pParent(NULL) , bVisible (true)
	{
	}
	virtual ~Window () {}
} ;

class Button:public Window
{
public:
	int id ;

public:

	void init (int _x, int _y, int _w, int _h, int _id) ;
	virtual void onClick (int tx, int ty) ;
	virtual void onClickR (int tx, int ty) ;
	virtual void onMouseFocus (int tx, int ty) ;
} ;

class TextButton:public Button
{
public:
	EasyStr <256> str ;

	void draw (HDC hdc, int ox, int oy) ;
} ;

#ifdef _PROJECT_GDI_

class TextArea:public Window
{
private:
	EasyStr <256> str ;

public:
	void init (int _x, int _y, int _w, int _h) ;

	void setText (const char*, float, float, float) ;
	void setPos (int _x, int _y) ;
	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif

class WindowMan//�����޲z��(manager)
{
protected:
	typedef std::list <Window*> VP_WINDOW ;
	VP_WINDOW vpWindow ;
	Window* pDragWnd ;//�즲��������

	bool bInDrag ;//�N������O�_�b�즲��
	int dragX, dragY ;

//	KeyState keyLButton ;

	int screenX, screenY ;

	int clientX, clientY ;

	Window* pInfoWindow ;//��ܸ�T�Ϊ�

public:
	WindowMan () ;

	void addWnd (Window* pw) ;

private:
	void doDrag (HWND hWnd, KeyMan&) ;

public:
	bool work (HWND hWnd, KeyMan&) ;

	void setInfoWnd (Window*) ;//�]�w��T����

	void draw (HDC hdc) ;

	void deleteAllWindow () ;
} ;

#endif