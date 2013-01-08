#ifndef _TOOL_BAR_WND_H_
#define _TOOL_BAR_WND_H_

#include "window.h"

//�I�]����
class ToolBarWnd:public Window
{
public:

	enum {UI_COUNT = 4, CELL_SIZE = 40} ;
	Window* vpWnd[UI_COUNT] ;//���V���s������UI

	TextArea* pTA ;
	~ToolBarWnd () {};

	void init (Window*, Window*, Window*, Window*,
			int _x, int _y) ;

	bool canDrag (int tx, int ty) ;
//	void onClick (int tx, int ty) ;
	void onCommand (int) ;

	void onMove () ;
	void setZOrder (int) ;

//	void draw (HDC hdc) ;
} ;

#endif