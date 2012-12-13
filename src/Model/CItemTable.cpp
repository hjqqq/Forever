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
		pw->initWeapon(L"�M�l", SWORD, false, 1, 1, 20, 50, COMMON,
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
		pa->initWeapon(L"�T", CLOTH, false, 1, 1, 20, 50, COMMON,
			baseAttr, extendAttr, CLOTHES);
		addInfo(pa);

		

		/*
		baseAttr->iATK = 20;
		baseAttr->iCRI = 10;
		baseAttr->iHIT = 5;
		extendAttr->iHP = 80;
		extendAttr->iMPMax = 8;
		pi.initWeapon(_T("�M�l"), SWORD, false, 1, 1, 20, 50, COMMON,
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
		//�Ů�
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
				//���F
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
			//�P�@��,�i�H���|
			CItem* pinfo = getInfo () ;
			if (m_iStack+st <= pinfo->getStackLimit())
			{
				//���|�S��
				m_iStack += st ;
				st = 0 ;
				return true ;
			}else
			{
				//�ﺡ�F
				st = m_iStack+st-pinfo->getStackLimit() ;
				m_iStack = pinfo->getStackLimit() ;
				return true ;
			}
		}else
		{
			//���P��
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