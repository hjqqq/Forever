#ifndef _GP_VERTEX_H_
#define _GP_VERTEX_H_

#include "gp_geometry.h"

namespace GP
{

template <class T> class _Color
{
public:
	T r, g, b, a ;

	void set (T _r, T _g, T _b, T _a)
	{
		r = _r ; g = _g ; b = _b ; a = _a ;
	}

	_Color (T _r, T _g, T _b, T _a):r(_r),g(_g),b(_b),a(_a)
	{
	}

	_Color ()
	{
	}

	bool operator!= (const _Color& rgb)const
	{
		return (r != rgb.r) || (g != rgb.g) || (b != rgb.b) || (a != rgb.a) ;
	}

	bool operator== (const _Color& rgb)const
	{
		return (r == rgb.r) && (g == rgb.g) && (b == rgb.b) && (a == rgb.a);
	}
} ;

typedef _Color <float32> Color ;
typedef unsigned char ES_COLOR_TYPE ;
typedef _Color <ES_COLOR_TYPE > ColorES ;

//########################################

template <class T> 
class _UV
{
public:
	T u, v ;

	void set (T _u, T _v)
	{
		u = _u ;
		v = _v ;
	}
} ;

typedef _UV <float32> UVfloat32 ;

//typedef float32 ES_UV_TYPE ;
typedef _UV <float32> UV ;

//�y��+�C��
class VertexC
{
public:
	//��private,�ӽT�O�@�w�n�z�Lfunction�ഫ
	Point3F pos ;
	Color color ;
} ;

//#######################

class VertexU
{
public:
	Point3F pos ;
	UVfloat32 uv ;
} ;

class VtxU
{
private:
	Point3F pos ;
	UV uv ;

public:
	static int fnGetMemOffsetUV ()
	{
		return sizeof (Point3F) ;
	}

	void operator= (const VertexU& v)
	{
		pos = v.pos ;
		uv = v.uv ;
//		uv.u = ES_UV_TYPE(v.uv.u) ;
//		uv.v = ES_UV_TYPE(v.uv.v) ;
	}
} ;

//#######################

class VertexCU
{
public:
	//��private,�ӽT�O�@�w�n�z�Lfunction�ഫ
	Point3F pos ;
	Color color ;
	UVfloat32 uv ;
} ;

class VtxCU
{
private:
	Point3F pos ;//�y��
	UV uv ;

public:
	void operator= (const VertexCU& v)
	{
		pos = v.pos ;
		uv = v.uv ;
//		uv.u = ES_UV_TYPE (v.uv.u) ;
//		uv.v = ES_UV_TYPE (v.uv.v) ;
	}
} ;

//#######################

//Vtx�Oopengl es���榡
class VtxC
{
public:
	Point3F pos ;//�y��
private:
	ColorES color ;//�C��

public:
	static int fnGetMemOffsetColor ()
	{
		return sizeof (Point3F) ;
	}

	void operator= (const VertexC& v)
	{
		pos = v.pos ;
		color.r = ES_COLOR_TYPE(v.color.r*255.0) ;
		color.g = ES_COLOR_TYPE(v.color.r*255.0) ;
		color.b = ES_COLOR_TYPE(v.color.r*255.0) ;
		color.a = ES_COLOR_TYPE(v.color.r*255.0) ;
	}
} ;

//�y��+�C��+UV
/*
class VertexCU:public Point3F, public Color, public UV
{
} ;
*/

}


#endif