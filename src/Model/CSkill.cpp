#include "CSkill.h"
#include "AttributeSet.h"
#include "CPlayer.h"

void CSkill::initSkill()
{
   if(SKILL_INFO::read("../Skill.fla") == false)
      SKILL_INFO::read("Skill.fla");

	/*if(SKILL_INFO::read("Skill.la"))
   {
   }
	else
	{
      AdvancedAttribute adv;
      FloatPrecentAttribute preAttr;
      CSkillInfo *ps = NULL;

      // ���q����
      AttributeClear(adv);
      adv.iHP = -10;
      adv.fATKSpeed = 0.0f;
      adv.fCasting = 0.0f;
      adv.fMove = 0.0f;

      AttributeClear(preAttr);

      ps = new CSkillInfo();
      ps->initSkillInfo(TYPE_ACTIVE, 1, "Skill/Common/Action_operation", "���q����",
	      "�����ĤH",
	      6, 0, 0, 0, 50.0f, ENEMY, adv, preAttr, 0, -1, -1, true, false);   // ActionID �n��
      addInfo(ps);

      // --------------------------------------------

      // �D������
      AttributeClear(adv);
      adv.fATKSpeed = 0.0f;
      adv.fCasting = 0.0f;
      adv.fMove = 0.0f;

      AttributeClear(preAttr);
      preAttr.fHP = 25;    // �ͩR�O��_25%

      // buff: �b3�������A�̤j�ͩR����50%�B�ͩR�^�_�t�״���50�I (�٨S��)
      ps = new CSkillInfo();
      ps->initSkillInfo(TYPE_ACTIVE, 1, "Skill/Knight/Stonebody_g1", "�D������",
	      "�^�_�ۨ�25%�ͩR�O�A�b3�������A�̤j�ͩR����50%�B�ͩR�^�_�t�״���50�I",
	      7, 0, 0, 6.0f * 60.0f, 0, SELF, adv, preAttr, 0, -1, -1, false, false);    //mp = 113
      addInfo(ps);

      //-----------------------------------------------

      // �r�P�@��
      AttributeClear(adv);
      adv.iHP = -138;        // �y��138���ˮ`
      adv.fATKSpeed = 0.0f;
      adv.fCasting = 0.0f;
      adv.fMove = 0.0f;

      AttributeClear(preAttr);

      ps = new CSkillInfo();
      ps->initSkillInfo(TYPE_ACTIVE, 1, "Skill/Knight/Robusthit_g1", "�r�P�@��", "��ؼгy�� 138 �����z�ˮ`",
         8, 0, 0, 10.0f, 50.0f, ENEMY, adv, preAttr, 0, -1, -1, true, false);
      addInfo(ps);
	}*/
}

CSkill::CSkill() : m_bAvailable(false) , m_fSurplus(0.0f)
{
}

CSkill::~CSkill()
{
}

float CSkill::getSurplus()
{
	return m_fSurplus;
}

bool CSkill::getAvailable()
{
	return m_bAvailable;
}

void CSkill::create(unsigned int skillID)
{
   if(false == SKILL_INFO::checkID(skillID))
   {
     return;
   }
	SKILL_INFO::create(skillID);

	CSkillInfo* pInfo = getInfo();
	if(NULL != pInfo)
   {
		m_fSurplus = 0.0f;
      m_bAvailable = true;
	}
}

void CSkill::startCoolDown()
{
   CSkillInfo *pInfo = getInfo();
	if(NULL != pInfo)
      m_fSurplus = pInfo->getCoolDown();
}

void CSkill::updateCoolDown(float timePass)
{
   if(m_fSurplus == 0.0f)
      return;

	m_fSurplus -= timePass;
	if(0.0f > m_fSurplus)
		m_fSurplus =  0.0f;

   notifySkillCoolDownUpdate();
}

bool CSkill::isReady()
{
	return 0.0f >= m_fSurplus;
}

bool CSkill::canLearn(unsigned int lv)
{
   CSkillInfo* pInfo = getInfo();
   if(NULL != pInfo)
   {
      return lv >= (unsigned int)pInfo->getLevel();
   }
   return false;
}

void CSkill::checkAvailable(std::map<EquipSlot, int> equip)
{
	CSkillInfo* pInfo = getInfo();
	if(NULL != pInfo)
	{
		bool bW = true;
		bool bS = true;
      if(pInfo->isRequireWeapon())
      {
			if(equip.end() == equip.find(MAIN_HAND))
			{
				bW = false;
			}
      }

      if(pInfo->isRequireShield())
		{
			if(equip.end() == equip.find(OFF_HAND))
         {
				bS = false;
         }
		}

      if(false == pInfo->isRequireWeapon() && false == pInfo->isRequireShield())
      {
			m_bAvailable = true;
      }
		else
      {
			if(false == bW || false == bS)
         {
				m_bAvailable = false;
         }
			else
         {
				m_bAvailable = true;
         }
      }
   }
}

// Add by Darren Chen on 2013/01/21 {
void CSkill::addSkillEventListener(ISkillEventListener *pListener)
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.find(pListener);
   if(it == m_skillEventListeners.end())
      m_skillEventListeners.insert(pListener);
}

void CSkill::removeSkillEventListener(ISkillEventListener *pListener)
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.find(pListener);
   if(it != m_skillEventListeners.end())
      m_skillEventListeners.erase(it);
}

void CSkill::notifySkillCoolDownUpdate()
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.begin();
   while(it != m_skillEventListeners.end()) {
      (*it)->updateSkillCoolDown(this);
      it++;
   }
}
// } Add by Darren Chen on 2013/01/21