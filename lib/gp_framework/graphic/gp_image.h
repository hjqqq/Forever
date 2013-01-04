#ifndef _GP_IMAGE_H_
#define _GP_IMAGE_H_

#include "gp_geometry.h"
#include "gp_vertex.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

namespace GP
{
//�@�i�Ϥ�
class Image
{
public:
	enum {NO_TEXTURE_ID = 0} ;

protected:
	GLuint textureID ;
	Point2F textSize ;
	UV uv ;

public:
	Image () ;
	~Image () ;

	//���\�ƻs
	Image& operator= (const Image&) {}

	GLuint getTextureID ()const ;
	void createTestData () ;

protected:
	void setPixel (int, int, void*) ;

public:

	void release () ;
	bool load (const char*) ;
} ;

class TextImage:public Image
{
private:
	int bInit ;
	HDC hMemDC ;
//	HPEN hPen ;
	HBITMAP hBMP ;
	void* pPixel ;
	char Text[256] ;//�W������r���e

public:
	TextImage () ;
	~TextImage () ;
	const Point2F& buildText (const char*, const Point2F&, UV&) ;//�إߤ�r�K��
} ;

class TextImage2
{
private:
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//�o��class���n��,�]������texture�Ϧӳy���į��ܺC
	enum {BUFFER_COUNT = 1} ;
	TextImage vImage[BUFFER_COUNT] ;
	int curImage ;

public:
	TextImage2 () ;

	TextImage& getCurImage () ;
	const Point2F& buildText (const char*, const Point2F&, UV&) ;//�إߤ�r�K��
} ;

} ;

#endif