#ifndef _CMONSTER_H_
#define _CMONSTER_H_
#include "CUnitObject.h"
#include "CMonsterInfoLoader.h"
#include "obj_mTable.h"
#include "IMonsterAIEventListener.h"

typedef ObjTable<CMonsterInfo*, CMonsterInfoLoader> MONSTER_INFO;

class CScene;

class CMonster:public MONSTER_INFO,
               public CUnitObject
{
   public:
      CMonster(std::string machineName, int kindID, long long uid, float fx, float fy);	//�غc �ǤJ�Ǫ����Ҧ����
      ~CMonster();
      static void          initMonster();						      //�إ߰ߤ@�Ǫ���(�Ȧb������l�ɩI�s�@��)

      void                 addHate(long long uid, int damage); //�W�[����� AngerValue �ǤJ�����̪�UID �y���������
      void                 removeHate(long long uid);
      void                 clearHate();

      int                  getReware();						      //���o�������~(�Ǧ^�������~��id)
      long long            getMoney();							      //���o��������
      unsigned int         getXP();							         //���o�g��
      void                 work(float timePass);

      void                 setState(MonsterState state);
      MonsterState         getState();
      FPOS                 getBornPosition();
      FPOS                 getAnchorPosition();
      bool                 isMonsterTargetTooFarAway();

      void addMonsterAIEventListener(IMonsterAIEventListener *pListener);
      void removeMonsterAIEventListener(IMonsterAIEventListener *pListener);

#ifdef _GAMEENGINE_2D_
      /** @brief Client��ø�ϰʧ@ 
        * @param hdc ø�ϸ˸m */
      /* virtual */ void draw(HDC hdc);
#endif

   private:
      friend class CPacketMonsterData;

      bool                   create(unsigned int id);    //�]�w���ة�
      long long              updateTargetObjectUID();    //�Ѥ������s�n��w���ĤHUID

      MonsterState           m_state;             //�ثe���A
      std::list<AngerValue>  m_lHatred;			  //����ȦC��
      FPOS                   m_bornPosition;      //�X��X,Y�y�� (2D)
      FPOS						  m_anchorPosition;	  //�i�J�԰��w���I

      std::set<IMonsterAIEventListener *>    m_monsterAIListeners;    // ��ť�n����Ǫ�AI����ť�̦C��
};

#endif  // #ifndef _CMONSTER_H_