#include "gp_canvas_layer.h"

#include <assert.h>

namespace GP
{

//##########################################

	Image* LayerNode::getImage ()
	{
		return &image ;
	}

	bool LayerNode::loadImage (const char* fname)
	{
		//�����ӹw�]���j�p
		size.set (100) ;
		set (0) ;//��m

		image.load (fname) ;

		return true ;
	}

	void LayerNode::setSize (const Point3F& s)
	{
		size = s ;//�j�p
	}

//##########################################
	void CanvasLayer::setGlobalLight (const Color& color)
	{
		globalLight = color ;
	}

	const Color& CanvasLayer::getGlobalLight ()
	{
		return globalLight ;
	}

	void CanvasLayer::sortNode ()
	{
	}

	V_LAYER_NODE& CanvasLayer::getAllNode ()
	{
		return vLayerNode ;
	}

	LayerNode* CanvasLayer::queryNodeImage (const char* fname)//�t�m�@�i�Ϥ�
	{
		vLayerNode.push_back (LayerNode ()) ;

		vLayerNode.back ().loadImage (fname) ;

		return &(vLayerNode.back ()) ;
	}

	void CanvasLayer::releaseNode (LayerNode* pn)
	{
		V_LAYER_NODE::iterator pi = vLayerNode.begin () ;
		while (pi != vLayerNode.end ())
		{
			if (&(*pi) == pn)
			{
				vLayerNode.erase (pi) ;//���R��
				return ;
			}
			++ pi ;
		}
		assert (0) ;
	}
	
	CanvasLayer::CanvasLayer ():globalLight(1, 1, 1, 1)
	{
	}

	/*
	CanvasLayer::~CanvasLayer ()
	{
	}
	*/

}