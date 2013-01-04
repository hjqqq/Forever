#include "gp_canvas.h"

#include <assert.h>

namespace GP
{

CanvasDC::CanvasDC (HWND hwnd):hWnd(hwnd),hDC(NULL),hBrush(NULL),
							brushColor(-1, -1, -1, -1)
{
	hDC = GetDC (hwnd) ;
	assert ((hDC != NULL) && "CanvasDC::CanvasDC") ;

	RECT cliRect ;
	GetClientRect (hWnd, &cliRect) ;
	w = (float32)cliRect.right ;
	h = (float32)cliRect.bottom ;

	memDC = CreateCompatibleDC (hDC) ;
	hBMP = CreateCompatibleBitmap (hDC, cliRect.right, cliRect.bottom) ;

	SelectObject (memDC, hBMP) ;

}

CanvasDC::~CanvasDC ()
{
	releaseBrush () ;

	if (memDC != NULL)
		DeleteObject (hBMP) ;

	if (memDC != NULL)//del dc
		DeleteDC (memDC) ;

	if (hDC != NULL)
		ReleaseDC (hWnd, hDC) ;
}

void CanvasDC::setMode (int)
{
}

void CanvasDC::releaseBrush ()
{
	if (hBrush != NULL)
	{
		DeleteObject (hBrush) ;
		hBrush = NULL ;
	}
}

void CanvasDC::setBrushColor (const Color& color)
{
	int s = sizeof (float32) ;

	if (brushColor == color)
	{
		//�P���C�⤣�إ߷s��brush
	}else
	{
		//���P��,���ص���2
		releaseBrush () ;

		brushColor = color ;

		//�إ�brush
		hBrush = CreateSolidBrush (RGB (color.r*255, color.g*255, color.b*255)) ;
		if (hBrush != NULL)
			SelectObject (memDC, hBrush) ;
	}
}

void CanvasDC::clear (const Color& rgb)
{
	int size = sizeof (float32) ;

	RectF rect ;
	rect.left = 0 ;
	rect.top = 0 ;
	rect.right = (float32)w ;
	rect.bottom = (float32)h ;

	setBrushColor (rgb) ;
	drawRect (rect, NULL) ;
}

/*
void CanvasDC::drawText (const char* text, float x, float y, int len)//��ܤ�r
{
	assert ((memDC != NULL) && "CanvasDC::drawText") ;

	if (len == AUTO_LEN)
		len = strlen (text) ;//������
	TextOut (memDC, (int)x, (int)y, text, len) ;
}
*/

void CanvasDC::drawEllipse (const RectF& rect)
{
	assert ((memDC != NULL) && "CanvasDC::drawEllipse") ;

	Ellipse (memDC, (int)rect.left, (int)rect.top, (int)rect.right, (int)rect.bottom) ;
}

void CanvasDC::drawRect (const RectF& rect, Image*)
{
	assert ((memDC != NULL) && "CanvasDC::drawRect") ;

	Rectangle (memDC, (int)rect.left, (int)rect.top, (int)rect.right, (int)rect.bottom) ;
}

	/*
void CanvasDC::drawLine (const VertexC&, const VertexC&)
{
	assert ((memDC != NULL) && "CanvasDC::drawLine") ;
	
	POINT oriPos ;
	MoveToEx (memDC, (int)rect.left, (int)rect.top, &oriPos) ;
	LineTo (memDC, (int)rect.right, (int)rect.bottom) ;
}
*/

void CanvasDC::update ()//�⤺�e��s
{
	assert ((memDC != NULL) && "CanvasDC::update") ;
	BitBlt (hDC, 0, 0, (int)w, (int)h, memDC, 0, 0, SRCCOPY) ; 
}

//###############################################


}

