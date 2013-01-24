#ifndef _CMONSTER_H_
#define _CMONSTER_H_
#include "CUnitObject.h"
#include "CMonsterInfoLoader.h"
#include "obj_mTable.h"

typedef ObjTable<CMonsterInfo*, CMonsterInfoLoader> MONSTER_INFO;

class CScene;

class CMonster:public MONSTER_INFO,
               public CUnitObject
{
   public:
      CMonster(int kindID, long long uid, float fx, float fy);	//�غc �ǤJ�Ǫ����Ҧ����
      ~CMonster();
      static void          initMonster();						      //�إ߰ߤ@�Ǫ���(�Ȧb������
                                                               //�l�ɩI�s�@��)
      void                 addHate(long long uid, int damage); //�W�[����� AngerValue �ǤJ
                                                               //�����̪�UID �y���������
      long long            getTarget();						      //���X�����ؼ�
      int                  getReware();						      //���o�������~(�Ǧ^�������~
                                                               //��id)
      long long            getMoney();							      //���o��������
      unsigned int         getXP();							         //���o�g��
      void                 work(float timePass, CScene& scene);
      bool                 isDead();
      std::vector<CSkill*> getSkill();
#ifdef _GAMEENGINE_2D_
      /** @brief Client��ø�ϰʧ@ 
        * @param hdc ø�ϸ˸m */
      /* virtual */ void draw(HDC hdc);
#endif

   private:
      MonsterState           m_state;             //�ثe���A
      std::list<AngerValue>  m_lHatred;			  //����ȦC��
      FPOS                   m_bonPosition;       // �X��X,Y�y�� (2D)
	 FPOS							 m_anchorPosition;	//�i�J�԰��w���I

      bool                   create(unsigned int id);    //�]�w���ة�
      void                   targetUpdate(CScene& scene);
      void					     AIAction(float timePass, CScene& scene);
      bool                   getBack();
};

#endif  // #ifndef _CMONSTER_H_