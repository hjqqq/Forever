#include "CPlayer.h"
#include "CItemTable.h"
#include "AttributeSet.h"

CPlayer::CPlayer(std::string strName, long long uid, char level) : CUnitObject(strName, uid, level), m_levelMax(50)
{
   m_backPack.initBack();
   upDateEquipAttr();

   // Add by Darren Chen on 2012/12/27 {
   ACTION_DATA actData;
   CActionEvent actEvent;
   CAction *pAction = NULL;
   CActionEventHandler *pActionEventHandler = NULL;

   // Idle�ʧ@->(�y�Ч��)->�]�B�ʧ@
   actData.iID           = 1;
   actData.name          = "����";
   actData.fTime         = 4.33333f;
   actData.animationName = "lm_nidle_001";
   actData.iNextActID    = 0;  // �S���U�@�Ӱʧ@
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);

   actEvent.clear();
   actEvent.m_event      = AET_KEY_WASD;
   actEvent.m_iKeyDownID = 'W';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_KEY_WASD;
   actEvent.m_iKeyDownID = 'A';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_KEY_WASD;
   actEvent.m_iKeyDownID = 'S';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_KEY_WASD;
   actEvent.m_iKeyDownID = 'D';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_NOT_REACH;
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 2);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event      = AET_KEY;
   actEvent.m_iKeyID     = 'X';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 3);
   pAction->addEventHandler(pActionEventHandler);

   m_pActionSystem->addAction(pAction);

   // �]�B�ʧ@->(�y�еL���)->Idle�ʧ@
   actData.iID           = 2;
   actData.name          = "�]�B";
   actData.fTime         = 1.46667f;
   actData.animationName = "lm_nrun_001";
   actData.iNextActID    = 0;  // �S���U�@�Ӱʧ@
   actData.bMove         = true;
   pAction = new CAction();
   pAction->init(actData);

   actEvent.clear();
   actEvent.m_event    = AET_KEY_WASD;
   actEvent.m_iKeyUpID = 'W';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event    = AET_KEY_WASD;
   actEvent.m_iKeyUpID = 'A';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event    = AET_KEY_WASD;
   actEvent.m_iKeyUpID = 'S';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event    = AET_KEY_WASD;
   actEvent.m_iKeyUpID = 'D';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   actEvent.clear();
   actEvent.m_event    = AET_REACH;
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 1);
   pAction->addEventHandler(pActionEventHandler);

   m_pActionSystem->addAction(pAction);

   // Idle�ʧ@->(�ޥX�Z���ֱ���)->�԰����A�ʧ@
   actData.iID           = 3;
   actData.name          = "�ޥX�Z��";
   actData.fTime         = 1.33333f;
   actData.animationName = "lm_cdraw_2weapon_001";
   actData.iNextActID    = 4;  
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);
   m_pActionSystem->addAction(pAction);

   actData.iID           = 4;
   actData.name          = "�԰�����";
   actData.fTime         = 1.0f;
   actData.animationName = "lm_cidle_2weapon_001";
   actData.iNextActID    = 0;  // �S���U�@�Ӱʧ@
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);

   actEvent.clear();
   actEvent.m_event      = AET_KEY;
   actEvent.m_iKeyID     = 'X';
   pActionEventHandler = new CActionEventHandler();
   pActionEventHandler->init(actEvent, 5);
   pAction->addEventHandler(pActionEventHandler);

   m_pActionSystem->addAction(pAction);

   actData.iID           = 5;
   actData.name          = "���^�Z��";
   actData.fTime         = 1.66667f;
   actData.animationName = "lm_nputin_2weapon_001";
   actData.iNextActID    = 1;  
   actData.bMove         = false;
   pAction = new CAction();
   pAction->init(actData);
   m_pActionSystem->addAction(pAction);
   // } Add by Darren Chen on 2012/12/27
}

void CPlayer::addXP(unsigned int xp)
{
	m_xp += xp;
	if(m_xpMax < m_xp)	//���o�g��� �i�ɯ�
	{		
		m_xp -= m_xpMax;
		//�ɯ�function
	}
}

unsigned int CPlayer::getXP()
{
	return m_xp;
}

unsigned int CPlayer::getXPMax()
{
	return m_xpMax;
}

CBackPack CPlayer::getBackPack()
{
	return m_backPack;
}

void CPlayer::wearEquip(unsigned int id)
{
	CItem* pItem = CItemTable::getInfo(id);
	if(NULL == pItem)
	{
		return;
	}
	if(WEAPON == pItem->getClassType())
	{
		CWeapon* pWp;
		pWp = (CWeapon*) pItem;
		if(ONE_HAND == pWp->getWield())
		{
			wearToEquipSlot(MAIN_HAND, id);
		}
		else if(TWO_HAND == pWp->getWield())
		{
			wearToEquipSlot(OFF_HAND, id);
		}
		else
		{
			return;
		}
		
	}
	else if(pItem->getClassType() == ARMOR)
	{
		CArmor* pAm;
		pAm = (CArmor*) pItem;
		if(CLOTHES == pAm->getWear())
		{
			wearToEquipSlot(CHEST, id);
		}
		else if(BELTS == pAm->getWear())
		{
			wearToEquipSlot(BELT, id);
		}
		else if(PANTS == pAm->getWear())
		{
			wearToEquipSlot(LEGS, id);
		}
		else if(PAULDRONS == pAm->getWear())
		{
			wearToEquipSlot(SHOULDER, id);
		}
		else if(GLOVES == pAm->getWear())
		{
			wearToEquipSlot(GLOVE, id);
		}
		else if(BOOTS == pAm->getWear())
		{
			wearToEquipSlot(BOOT, id);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
	upDateEquipAttr();
}

void CPlayer::shedEquip(EquipSlot grid)
{
	if(m_mEquip.end() == m_mEquip.find(grid))
	{
		return;
	}
	int st = 1;
	int gr = 0;
	m_backPack.addItem(m_mEquip.find(grid)->second, st, gr);
	m_mEquip.erase(grid);
	upDateEquipAttr();
	//
}

void CPlayer::upDateEquipAttr()
{
	std::map<EquipSlot , int>::iterator pi = m_mEquip.begin();
	AdvancedAttribute advAttr;
	AttributeClear(advAttr);
	ObscureAttribute obsAttr;
	AttributeClear(obsAttr);
	BasisAttributeSet(getLevel(), getBasAttr(), advAttr, obsAttr);		//���o�����l����
	while (m_mEquip.end() != pi)
	{
		CWeapon* wp = (CWeapon*) CItemTable::getInfo(pi->second);
		if(NULL == wp)
		{
			break;
		}
		AttributeAdd (advAttr, wp->getBaseAttr());
		AttributeAdd (advAttr, wp->getExtendAttr());
		
		pi++;
	}
	setAdvAttr(advAttr);

    std::vector<CSkillTable>::iterator ps = m_vSkill.begin();
    while(m_vSkill.end() != ps)
    {
        ps->chackAvailable(getEquip());
        ps++;
    }
}

void CPlayer::wearToEquipSlot(EquipSlot es, unsigned int id)
{
	if(m_mEquip.end() == m_mEquip.find(es))
	{
		m_mEquip.insert(std::make_pair(es, id));
	}
	else
	{
		int st = 1;
		int bu = 0;
		m_backPack.addItem(m_mEquip.find(es)->second, st, bu);
		m_mEquip.insert(std::make_pair(es, id));
	}
}

std::map<EquipSlot, int> CPlayer::getEquip()
{
	return m_mEquip;
}
int CPlayer::getEquip(EquipSlot equip)
{
	int id ;
	if(m_mEquip.end() == m_mEquip.find(equip))
	{
		id = -1;
	}
	else
	{
		id = m_mEquip.find(equip)->second;
	}
	return id;
}

// Add by Darren Chen on 2012/12/26 {
#ifdef _GAMEENGINE_2D_
void CPlayer::draw(HDC hdc)
{
   CUnitObject::draw(hdc);

   int size = 20;
   char buf[128];
   sprintf_s(buf, sizeof(buf), "%s", getName().c_str());
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY + size + 5, buf, strlen(buf));
}
#endif  // #ifdef _GAMEENGINE_2D_
// } Add by Darren Chen on 2012/12/26