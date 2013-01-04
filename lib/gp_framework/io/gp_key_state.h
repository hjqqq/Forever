#ifndef _GP_KEY_STATE_
#define _GP_KEY_STATE_

#include <graphic\gp_geometry.h>
#include <math.h>

namespace GP
{


//#########################################
//#########################################
//#########################################

//���䪬�A
class KeyState
{
private:
	enum {NO_ID = -1} ;
	int id ;
	bool bPreDown ;//�W��
	bool bCurDown ;


public:

	KeyState () ;
	void work () ;


	void setID (int) ;

	bool isDown ()const ;
	bool isTriggerDown ()const ;
	bool isTriggerUp ()const ;
} ;

enum {KEY_LBUTTON, KEY_RBUTTON,
	KEY_SPACE, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_COUNT} ;

class KeyStateMan
{
public:

private:
	//�Ҧ�������
	KeyState vKeyState[KEY_COUNT] ;

	Point2F cursorPos ;//��Ц�m
public:

	KeyStateMan () ;
	void work (HWND, int, float32, float32) ;

	const Point2F& getCursorCanvasPos ()const ;

	bool isDown (unsigned int)const ;//���A
	bool isTriggerDown (unsigned int)const ;//�O�_�����U����
	bool isTriggerUp (unsigned int)const ;//�O�_����}����
} ;

}

#endif