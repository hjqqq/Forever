/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   Common.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/13 */
#include "Common.h"

// + Add by Darren Chen on 2012/12/13 {
std::string getCurDateTime()
{
   time_t rawTime = time(NULL);

   tm timeInfo;
   localtime_s(&timeInfo, &rawTime);

   char buf[30];
   strftime(buf, 30, "%Y/%m/%d %H:%M:%S", &timeInfo);
   
   return std::string(buf);
}

void getMousePos(HWND hWnd, int &cx, int &cy)
{
	POINT pnt;
	GetCursorPos(&pnt);  // ���o�ƹ�����m (�ù��y��)
						
	ScreenToClient(hWnd, &pnt); // ��ù��y���ন�����y��
	cx = pnt.x;
	cy = pnt.y;
}

void getMouseScreenPos(int &cx, int &cy)
{
	POINT pnt;
	GetCursorPos(&pnt);  // ���o�ƹ�����m (�ù��y��)
						
	cx = pnt.x;
	cy = pnt.y;
}

float getDistance(float x1, float y1, float x2, float y2)
{
   return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void movePoint(float &x1, float &y1, float x2, float y2, float step)
{
   float L = getDistance(x1, y1, x2, y2);
   if(L > step) {
      x1 = x1 + (x2 - x1) / L * step;
      y1 = y1 + (y2 - y1) / L * step;
   }
   else {
      x1 = x2;
      y1 = y2;
   }
}
// - Add by Darren Chen on 2012/12/13 } 