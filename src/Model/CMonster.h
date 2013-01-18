#ifndef _CMONSTER_H_
#define _CMONSTER_H_
#include "CUnitObject.h"
#include "CMonsterInfoLoader.h"
#include "obj_mTable.h"

typedef ObjTable<CMonsterInfo*, CMonsterInfoLoader> MONSTER_INFO;

class CMonster:public MONSTER_INFO,
               public CUnitObject
{
   public:
      /*CMonster(int kindID, long long uid, char level, float dx, float dy,
               std::vector<CSkill *> vSkill, std::list<AngerValue> lHatred,
               std::vector<int> vReware, long long money);	//�غc �ǤJ�Ǫ����Ҧ����*/
      CMonster(int kindID, long long uid, char level, float dx, float dy, long long money);

      ~CMonster();

      static void			initMonster();						      //�إ߰ߤ@�Ǫ���(�Ȧb������l
                                                            //�ɩI�s�@��)
      void			  	   addHate(long long uid, int damage); //�W�[����� AngerValue �ǤJ
                                                            //�����̪�UID �y���������
      long long			getTarget();						      //���X�����ؼ�
      int             	getReware();						      //���o�������~(�Ǧ^�������~��id vector)
      long long			getMoney();							      //���o��������
      unsigned int		getXP();							         //���o�g��
      void              work(float timePass);
#ifdef _GAMEENGINE_2D_
      /** @brief Client��ø�ϰʧ@ 
        * @param hdc ø�ϸ˸m */
      /* virtual */ void draw(HDC hdc);
#endif

private:
	std::list<AngerValue> m_lHatred;			//����ȦC��
	std::vector<int>		 m_vReware;			//�������~
	long long				 m_Money;			//��������
	long long				 m_Target;			//�ؼ�
    
   bool                 create(unsigned int kindID);    //�]�w���ة�
   void                 targetUpdate();
};

#endif  // #ifndef _CMONSTER_H_