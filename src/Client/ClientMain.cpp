#include "Common.h"
#include "CUnitObject.h"
#include "CPlayer.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPlayer player(_T("xXX"));	//_T _TEXT���N�� �i�N���e�ର��r�Ϊ�2��bytes 1�Ӧr
   return 0;
}