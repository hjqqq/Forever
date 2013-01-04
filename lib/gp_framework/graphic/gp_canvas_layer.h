#ifndef _GP_CANVANS_LAYER_H
#define _GP_CANVANS_LAYER_H

#include "gp_draw_info.h"
#include "gp_image.h"

namespace GP
{

class LayerNode:public DrawInfo
{
private:
	Image image ;//�Ϥ�

	//���\�ƻs
	LayerNode& operator= (const LayerNode&) {}

public:
	Image* getImage () ;

	bool loadImage (const char*) ;
	void setSize (const Point3F&)  ;
} ;

typedef std::list <LayerNode> V_LAYER_NODE ;

class CanvasLayer
{
private:
	friend class Canvas ;
	V_LAYER_NODE vLayerNode ;

	Color globalLight ;

public:
	void setGlobalLight (const Color&) ;
	const Color& getGlobalLight () ;

	void sortNode () ;
	V_LAYER_NODE& getAllNode () ;

	LayerNode* queryNodeImage (const char*) ;//�t�m�@�i�Ϥ�
	void releaseNode (LayerNode*) ;//�k��

//	void draw () ;

	CanvasLayer () ;
//	~CanvasLayer () ;
} ;

}

#endif