#include "CItemTable.h"



void CItemTable::initItemTable ()
{
	if (ITEM_INFO::read ("item.itb"))
	{
	}else
	{
		CWeapon* pw;
		pw = new CWeapon;
		AdvancedAttribute baseAttr;
		AdvancedAttribute extendAttr;
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);
		baseAttr.iATK = 20;
		baseAttr.iCRI = 10;
		baseAttr.iHIT = 5;
		extendAttr.iHP = 80;
		extendAttr.iMPMax = 8;
		pw->initWeapon(L"刀子", SWORD, false, 1, 1, 20, 50, COMMON,
			baseAttr, extendAttr, ONE_HAND);
		addInfo(pw);

		CArmor* pa;
		pa = new CArmor;
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);
		baseAttr.iATK = 10;
		baseAttr.iHIT = 7;
		extendAttr.iHP = 90;
		extendAttr.iMPMax = 0;
		pa->initWeapon(L"袍", CLOTH, false, 1, 1, 20, 50, COMMON,
			baseAttr, extendAttr, CLOTHES);
		addInfo(pa);

		

		/*
		baseAttr->iATK = 20;
		baseAttr->iCRI = 10;
		baseAttr->iHIT = 5;
		extendAttr->iHP = 80;
		extendAttr->iMPMax = 8;
		pi.initWeapon(_T("刀子"), SWORD, false, 1, 1, 20, 50, COMMON,
			(*baseAttr), (*extendAttr),ONE_HAND);
		baseAttr = NULL;
		extendAttr = NULL;*/
	}
}
CItemTable::CItemTable ():m_iStack(0)
{
}

CItemTable::~CItemTable()
{
	if(getInfoCount()==0)
		return;
	CItem* dx;
	for(int i = 0;i<getInfoCount();i++)
	{
		dx = getInfo(i);
		delete dx;
	}
}

bool CItemTable::addStack (int id, int& st)
{
	if (checkID (id) == false)
		return false ;

	CItem* pinfo = getInfo () ;
	if (pinfo == NULL)
	{
		//空格
		ITEM_INFO::create (id) ;
		pinfo = getInfo () ;
		if (pinfo != NULL)
		{
			if (st <= pinfo->getStackLimit())
			{
				m_iStack = st ;
				st = 0 ;
			}else
			{
				//滿了
				st = st-(pinfo->getStackLimit()) ;
				m_iStack = pinfo->getStackLimit() ;
			}
			return true ;
		}else
			return false ;
	}else
	{
		if (getID () == id)
		{
			//同一種,可以堆疊
			CItem* pinfo = getInfo () ;
			if (m_iStack+st <= pinfo->getStackLimit())
			{
				//堆疊沒滿
				m_iStack += st ;
				st = 0 ;
				return true ;
			}else
			{
				//堆滿了
				st = m_iStack+st-pinfo->getStackLimit() ;
				m_iStack = pinfo->getStackLimit() ;
				return true ;
			}
		}else
		{
			//不同種
			return false ;
		}
	}
}

int CItemTable::getStack ()
{
	return m_iStack ;
}

void CItemTable::create (int id, int st)
{
	ITEM_INFO::create (id) ;

	CItem* pinfo = getInfo () ;
	if (pinfo != NULL)
	{
		if (st < pinfo->getStackLimit() && st >= 1)
			m_iStack = st ;
		else
			m_iStack = pinfo->getStackLimit();
	}
}