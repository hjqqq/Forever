#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "key_state.h"
#include "easy_str.h"
#include <list>

//�N��@�ӹC����������
//�N�ӥi�H�Q�X�R�����I�]����,���A����,���Ȭɭ�
class Window
{
public:
	Window* pParent ;//���˵���
	typedef std::list <Window*> VP_WND ;
	VP_WND vpWnd ;//�Ҧ����l����

	int x, y ;//�������y��,���W����
	int w, h ;//�������e��

	bool bVisible ;

	bool checkPoint (int tx, int ty) ;

	virtual void onMove () {} ;

	virtual bool canDrag (int tx, int ty) ;
	virtual void onClick (int tx, int ty) ;

	virtual void draw (HDC hdc, int ox, int oy) ;
	virtual void setZOrder (int) {} ;

	void addChild (Window*) ;

	virtual void onCommand (int) {} ;//�l����,���sbutton,�q��

	Window ():pParent(NULL)
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
} ;

class TextButton:public Button
{
public:
	EasyStr <64> str ;

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

public:
	WindowMan () ;

	void addWnd (Window* pw) ;

private:
	void doDrag (HWND hWnd, KeyMan&) ;

public:
	bool work (HWND hWnd, KeyMan&) ;

	void draw (HDC hdc) ;

	void deleteAllWindow () ;
} ;

#endif