#ifndef _GP_APPLICATION_H_
#define _GP_APPLICATION_H_

#include <system\gp_variable_type.h>

#include <io\gp_key_state.h>

namespace GP
{

class Canvas ;

/*
//�ֳt�r��
class FastString
{
} ;

//�@��r��
class String
{
private:

public:
} ;

//�r��
*/


//#########################################
//#########################################
//#########################################

class FPS
{
private:
	float count ;
	float32 fps ;
	float32 accuTime ;

	float totalTime ;

public:
	FPS () ;

	float32 getTotalTime ()const ;
	float32 get ()const ;
	void work (float32) ;
} ;

class Application
{
private:
	static Application* gpApplication ;

	bool bNeedEnd ;//�ݭn����
	enum {NO_PRE_TIME = -1} ;
	int preTime ;//�W�����ɶ�

private:
	Application (const Application&) {} //no copy construct

protected:
	KeyStateMan keyStateMan ;
	FPS fps, wps ;

//	bool b2DPixelMode ;

	Canvas* pCanvas ;

public:
private:
	int coordinateSystem ;

public:
	Application () ;
	~Application () ;

	void setEnd () ;//�����{��

	static void fnInit () ;
	static void fnWork () ;
	static bool fnClose () ;
private:
	void work () ;

public:
	static void fnPaint () ;

	void setDisplayMode (bool, int, int, int) ;//����ܼҦ�
//	void setScreenPixelMode () ;//��x�}�]�w���ù�,���W���O(0,0),�k�U���O(w-1,h)
//	void set2DPixelMode () ;

	Canvas& getMainCanvas () ;//���o�D�e��

	//�~�ӥ�
	virtual void onInit () = 0 ;//�@��l
//	virtual Canvas* onCreaetCanvas () = 0 ;//�@��l
	virtual void onWork (float32) = 0 ;//���o�t�ΰ����v
	virtual void onExtWork () = 0 ;//�B�~���B�@�ɶ�
	virtual void onPrePaint () = 0 ;//�B�zø��
	virtual void onPaint () = 0 ;//�B�zø��
	virtual bool onClose () = 0 ;//�^��true�T�w�n����
} ;

}

#endif