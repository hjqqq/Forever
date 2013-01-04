#ifndef _GP_CAMERA_H_
#define _GP_CAMERA_H_

#include "gp_geometry.h"
#include "gp_matrix.h"

namespace GP
{

class Matrix4 ;

class Camera
{
private:
	Point3F pos, front, up ;
	Matrix4 finalMatrix ;

public:
	Camera () ;

	void setPos (const Point3F&) ;
	void setProjection (float, float, float) ;//�]�w��v

	const Matrix4& getFinalMatrix () ;//���o�x�}

	void transformCanvas (Point3F&)const ;//��@�Ӯy�а���v�ഫ,�ܦ�2D�y��
} ;

}

#endif