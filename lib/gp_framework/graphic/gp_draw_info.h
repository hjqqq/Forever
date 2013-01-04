#ifndef _GP_DRAW_INFO_H_
#define _GP_DRAW_INFO_H_

#include "gp_geometry.h"

#include <list>


#include "gp_vertex.h"

namespace GP
{

//�e���󪺸�T
class DrawInfo:public Point3F
{
private:
	//blending
	enum {NO_BLEND, //�@��ø��
			BLEND_MODULATE, BLEND_ADD //alpha blend
			} ;
	int blendType ;
	float32 alpha ;//�b�z��

	bool bFillColor ;
	Color fillColor ;//�ѦҥΪ����

	int drawOrder ;//ø�ϱƧǥ�

public:
	Point3F size ;//�j�p

	float time ;//�ʵe�ɶ�

	DrawInfo () ;

	void setFillColor (bool, const Color&) ;//���
	void setBlend (int, float32) ;
} ;

//###############################



}

#endif