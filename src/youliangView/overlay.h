#ifndef _WINDOW_OGRE_H_
#define _WINDOW_OGRE_H_


#include "window.h"

class ImageButton ;
//�ۤv�g��overlay
//����overlay���޲z����
class OverlayUI
{
private:
	Ogre::Overlay* pOverlay ;

public:
	void init () ;//�إ�overlay
	void addImage (ImageButton&) ;
} ;


#endif