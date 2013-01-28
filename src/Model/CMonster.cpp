#include "CMonster.h"
#include "AttributeSet.h"
#include "CSkill.h"
#include "CScene.h"
#include "CActionDispatch.h"

const int idelRandRange = 5000;

CMonster::CMonster(int kindID, long long uid, float fx, float fy) :
            CUnitObject(MONSTER_INFO::getInfo(kindID)->getName(), uid, 
            MONSTER_INFO::getInfo(kindID)->getLevel()),
                        m_state(ESTABLISH)
{
   if(create(kindID))
   {
      setPosition(fx, fy);
      setTargetPosition(fx, fy);
      m_state = IDLE;
      m_vSkill = getSkill();
      m_bonPosition.fX = fx;
      m_bonPosition.fY = fy;
      m_anchorPosition.fX = 0.0f;
      m_anchorPosition.fY = 0.0f;

      srand((unsigned int)time(NULL));

      ACTION_DATA actData;
      CActionEvent actEvent;
      CAction *pAction = NULL;
      CActionEventHandler *pActionEventHandler = NULL;

      actData.iID           = 101;
      actData.name          = "����";
      actData.fTime         = 4.33333f;
      actData.animationName = "lm_nidle_001";
      actData.iNextActID    = 0;  // �S���U�@�Ӱʧ@
      actData.bMove         = false;
      pAction = new CAction();
      pAction->init(actData);

      actEvent.clear();
      actEvent.m_event      = AET_NOT_REACH;
      pActionEventHandler = new CActionEventHandler();
      pActionEventHandler->init(actEvent, 102);
      pAction->addEventHandler(pActionEventHandler);

      m_pActionSystem->addAction(pAction);

      //----------------------------------------------------------

      actData.iID           = 102;
      actData.name          = "�]�B";
      actData.fTime         = 1.46667f;
      actData.animationName = "lm_nrun_001";
      actData.iNextActID    = 0;  // �S���U�@�Ӱʧ@
      actData.bMove         = true;
      pAction = new CAction();
      pAction->init(actData);

      actEvent.clear();
      actEvent.m_event    = AET_REACH;
      pActionEventHandler = new CActionEventHandler();
      pActionEventHandler->init(actEvent, 101);
      pAction->addEventHandler(pActionEventHandler);

      m_pActionSystem->addAction(pAction);
   }
}

CMonster::~CMonster()
{
}

void CMonster::initMonster()
{
   //if(MONSTER_INFO::read("../Monster.la") == false)
   //   MONSTER_INFO::read("Monster.la");

   if(MONSTER_INFO::read("Monster.la"))
   {
   }
   else
   {
      BasicAttribute basAttr;
      AttributeClear(basAttr);
      basAttr.iSTR = 100;
      basAttr.iVIT = 100;
      basAttr.iINT = 0;
      basAttr.iDEX = 100;
      basAttr.iAGI = 100;
      basAttr.iWIL = 0;

      CMonsterInfo* pm = new CMonsterInfo();
      std::vector<int> reware;
      std::vector<CSkill*> skill;
      reware.push_back(0);
      reware.push_back(1);
      reware.push_back(2);
      CSkill* pskill = new CSkill();
      pskill->create(0);
      skill.push_back(pskill);
      pm->initMonsterInfo("�����;|��", "���q��", "", "", 1, 1, 350, MONSTER_ACTIVE,
                          REGULAR_GRADE, 100, 500, basAttr, 100, reware, skill);
                          addInfo(pm);
   }
}

bool CMonster::create(unsigned int kindID)
{
   if(false == MONSTER_INFO::checkID(kindID))
   {
      return false;
   }
   MONSTER_INFO::create(kindID);
   CMonsterInfo* pInfo = getInfo();
   if(NULL != pInfo)
   {
      m_lHatred.clear();
      setBasAttr(pInfo->getBasAttr());
      return true;
   }
   return false;
}

void CMonster::addHate(long long uid, int damage)
{
   if(RETURN == m_state)//�^�k�~�����p�⤳���
   {
      return;
   }

   if(IDLE == m_state)//idle���A �Q�����������o�ؼ�
   {
      m_state = GOALS;
      m_anchorPosition.fX = getPosition().fX;
      m_anchorPosition.fY = getPosition().fY;
   }

   int iHatred =(int) abs(damage) / 20 ;
   if(0 == m_lHatred.size())
   {
      AngerValue anger;
      anger.uid = uid;
      anger.iHatred = iHatred;
      m_lHatred.push_back(anger);
      return;
   }

   std::list<AngerValue>::iterator pi = m_lHatred.begin();
   while(m_lHatred.end() != pi)
   {
      if(pi->uid == uid)
      {
         pi->iHatred += iHatred;
         break;
      }
      pi++;
   }
}

long long CMonster::getTarget()
{
	return getTargetObject()->getUID();
}

int CMonster::getReware()
{
    std::vector<int> reware = MONSTER_INFO::getInfo()->getReware();
    int offset = (rand() % reware.size());
	return reware[offset];
}

long long CMonster::getMoney()
{
    long long money = MONSTER_INFO::getInfo()->getMoney();
    money -= (int) (money * (rand() % 10) * 0.1f);
	return money;
}

unsigned int CMonster::getXP()
{
   CMonsterInfo* pInfo = MONSTER_INFO::getInfo();
   return (pInfo->getxp() * getLevel());
}

void CMonster::work(float timePass, CScene& scene)
{
   targetUpdate(scene);
   CUnitObject::work(timePass);
   AIAction(timePass, scene);
   //����Ȫ����a�����~�欰�y������
}

bool CMonster::isDead()
{
	return 0 >= getAdvAttr().iHP;
}

std::vector<CSkill*> CMonster::getSkill()
{
   return MONSTER_INFO::getInfo()->getSkill();
}

void CMonster::targetUpdate(CScene& scene)
{
   if(0 == m_lHatred.size())
   {
      return;
   }

   std::list<AngerValue>::iterator pi = m_lHatred.begin();
   AngerValue hate;
   AngerValue hateSec;
   hate.iHatred = -1;
   hate.uid = -1;
   hateSec.iHatred = -1;
   hateSec.uid = -1;
	while(m_lHatred.end() != pi)
	{
		if(hate.iHatred < pi->iHatred)
		{
         hateSec = hate;
         hate = (*pi);
		}
		pi++;
	}

   if((-1) == hateSec.uid)
   {
      CUnitObject* punit = scene.getUnitObject(hate.uid);
      setTargetObject(punit);
   }
   else if(hateSec.uid == getTarget())
   {
      int compare = hateSec.iHatred + ((int) (hateSec.iHatred * 0.05f));
      if(hate.iHatred > compare)//��%�Ƥ�����|��
      {
         CUnitObject* punit = scene.getUnitObject(hate.uid);
         setTargetObject(punit);
      }
   }
   else if(hate.uid != getTarget())
   {
      CUnitObject* punit = scene.getUnitObject(hate.uid);
      setTargetObject(punit);
   }
}

void CMonster::AIAction(float timePass, CScene& scene)
{    
   CMonsterInfo* pInfo = MONSTER_INFO::getInfo();
   if(NULL == pInfo)
   {
      return;
   }

	if(IDLE == m_state)
	{
      if(MONSTER_ACTIVE == pInfo->getATKtype())
      {
         std::list<CPlayer*>* playerList = scene.getvtPlayer();
         std::list<CPlayer*>::iterator pp = playerList->begin();
         float distance = pInfo->getAlert();
         long long playerID = -1;
         while(playerList->end() != pp)
         {
            float dis = getDistance(getPosition().fX, getPosition().fY,
            (*pp)->getPosition().fX, (*pp)->getPosition().fY);
            if(pInfo->getAlert() > dis)
            {
               if(distance > dis)
               {
                  distance = dis;
                  playerID = (*pp)->getUID();
               }
            }
            pp++;
         }

         if(-1 != playerID)
         {
            addHate(playerID, 0);
            return;
         }
      }

      if(isReachTarget())
      {
         int pass = rand() % idelRandRange;
         if(3 == pass)
         {
            float range = pInfo->getAlert();
            int fx = (rand() % (int) (range * 2)) - (int) (range);
            int fy = (rand() % (int) (range * 2)) - (int) (range);
            float ftx = m_bonPosition.fX + fx;
            float fty = m_bonPosition.fY + fy;
#ifdef _GAMEENGINE_2D_
            setTargetPosition(ftx, fty, true);
#endif

            CActionEvent actEvent;
            actEvent.m_event = AET_NOT_REACH;
            CActionDispatch::getInstance()->sendEvnet(getUID(), actEvent);
         }
         else
         {
            setTargetPosition(getPosition().fX, getPosition().fY);

            CActionEvent actEvent;
            actEvent.m_event = AET_REACH;
            CActionDispatch::getInstance()->sendEvnet(getUID(), actEvent);
         }
      }
      return;
   }

   if(RETURN == m_state)//�^�k��� �ˬd��F�S ��F�}�lidle
   {
      setBasAttr(pInfo->getBasAttr());
      if(isReachTarget())
      {
         m_state = IDLE;
      }
      return;
   }

   if(GOALS == m_state)
   {
      CUnitObject* punit = getTargetObject();
      if(NULL == punit)
      {
         return;
      }

      float fx = punit->getPosition().fX;
      float fy = punit->getPosition().fY;
#ifdef _GAMEENGINE_2D_
      setTargetPosition(fx, fy, true);
#endif

      CActionEvent actEvent;
      actEvent.m_event = AET_NOT_REACH;
      CActionDispatch::getInstance()->sendEvnet(getUID(), actEvent);

      m_state = DOLLY;
      return;
   }

   if(DOLLY == m_state)
   {
      CUnitObject* punit = getTargetObject();
      if(NULL == punit)
      {
         return;
      }
      float fx = punit->getPosition().fX;
      float fy = punit->getPosition().fY;
#ifdef _GAMEENGINE_2D_
      setTargetPosition(fx, fy, true);
#endif

      float distance = getDistance(getPosition().fX, getPosition().fY, fx, fy);
      if(getBack())//���}�ӻ��^�k
      {
         return;
      }
#ifdef _GAMEENGINE_2D_
      if(35.0f > distance)
      {
         //setTargetPosition(getPosition().fX, getPosition().fY);
         CActionEvent actEvent;
         actEvent.m_event = AET_REACH;
         CActionDispatch::getInstance()->sendEvnet(getUID(), actEvent);
         m_state = ATTACK;
      }
      return;
#endif //#ifdef _GAMEENGINE_2D_
   }

   if(ATTACK == m_state)
   {
#ifdef _GAMEENGINE_2D_
      float fx = getTargetObject()->getPosition().fX;
      float fy = getTargetObject()->getPosition().fY;
      float distance = getDistance(getPosition().fX, getPosition().fY, fx, fy);
      if(40.0f < distance)
      {
         m_state = GOALS;
         return;
      }
#endif //#ifdef _GAMEENGINE_2D_
      std::vector<CSkill*> vskill = getSkill();
      std::vector<CSkill*>::iterator pskill = vskill.begin();
      switch(pInfo->getWistom())
      {
         case 1:
            while (vskill.end() != pskill)
            {
               if((*pskill)->isReady())
               {
                  useSkill((*pskill)->getID());
                  break;
               }
               pskill++;
            }
            break;

         case 2:  
         {   //��j�ޯ�� �׭^
            int hp = 0;
            int no = -1;
            while(vskill.end() != pskill)
            {
               if((*pskill)->isReady())
               {
                  CSkillInfo* pInfo = (*pskill)->getInfo();
                  AdvancedAttribute effectAttr = pInfo->getEffectAttr();
                  FloatPrecentAttribute effectPrecentAttr = pInfo->getEffectAttrPercent();
                  AttributeMulti(effectAttr, effectPrecentAttr);
                  if(hp < effectAttr.iHP)
                  {
                     hp = effectAttr.iHP;
                     no = (*pskill)->getID();
                  }
               }
               pskill++;
            }
            useSkill(no);
            break;
         }

         case 3: 
         {    //��
            int hp = 0;
            int no = -1;
            while(vskill.end() != pskill)
            {
               if((*pskill)->isReady())
               {
                  CSkillInfo* pInfo = (*pskill)->getInfo();
                  AdvancedAttribute effectAttr = pInfo->getEffectAttr();
                  FloatPrecentAttribute effectPrecentAttr = pInfo->getEffectAttrPercent();
                  AttributeMulti(effectAttr, effectPrecentAttr);
                  if(hp < effectAttr.iHP)
                  {
                     hp = effectAttr.iHP;
                     no = (*pskill)->getID();
                  }
               }
               pskill++;
            }
            useSkill(no);
            break;
         }
      }
   }
}

bool CMonster::getBack()
{
   if(0 == m_lHatred.size())
   {
      return false;
   }

   CMonsterInfo* pInfo = MONSTER_INFO::getInfo();
   if(NULL == pInfo)
   {
      return false;
   }

   float range = pInfo->getRegress() * 0.6f;
   float fx = getTargetPosition().fX;
   float fy = getTargetPosition().fY;
   float fbx = m_anchorPosition.fX;
   float fby = m_anchorPosition.fY;
   float distance = getDistance(fbx, fby, fx, fy);
   if(range < distance)
   {
      //�ഫ�l���b�d�򤺪����몱�a
      m_state = RETURN;
      m_lHatred.clear();
      setTargetObject(NULL);
#ifdef _GAMEENGINE_2D_
      setTargetPosition(fbx, fby, true);
#endif
      return true;
   }

   return false;
}

#ifdef _GAMEENGINE_2D_
void CMonster::draw(HDC hdc)
{
   CUnitObject::draw(hdc);

   int size = 20;
   char buf[128];
   sprintf_s(buf, sizeof(buf), "%s", getName().c_str());
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY + size + 5, buf, strlen(buf));
}
#endif  // #ifdef _GAMEENGINE_2D_