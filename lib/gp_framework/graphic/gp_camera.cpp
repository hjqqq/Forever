#include "gp_camera.h"

namespace GP
{

Camera::Camera ():pos(0,0,0),front(0,0,1),up(0,-1,0)
{
}

void Camera::setPos (const Point3F& p)
{
	pos = p ;
}

void Camera::setProjection (float cancasW, float cancasH, float aspect)//�]�w��v
{
}

const Matrix4& Camera::getFinalMatrix ()//���o�x�}
{
	return finalMatrix ;
}

void Camera::transformCanvas (Point3F& pnt)const//��@�Ӯy�а���v�ഫ,�ܦ�2D�y��
{
}

}