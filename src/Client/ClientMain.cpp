#include "Common.h"
#include "CUnitObject.h"
#include "CPlayer.h"
#include "CItem.h"
#include "CWeapon.h"
#include "CItemTable.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPlayer player(_T("xXX"));	//_T _TEXT���N�� �i�N���e�ର��r�Ϊ�2��bytes 1�Ӧr

	AdvancedItem *itemInfo;		//item�����ظ��struct
	CItem item;					//�nŪ����item
	itemInfo = item.getAll();	//���o��T

	itemInfo->level=20;				//��name

	if(itemInfo != NULL)
	{
		delete itemInfo;
		itemInfo = NULL;
	}

	CItemTable cta;
	cta.initItemTable();
	cta;

	CItem* pk;
	pk = cta.getInfo(0);

	WeaponWieldType ti;
	ti = ((CWeapon*)pk)->getWield();


   return 0;
}