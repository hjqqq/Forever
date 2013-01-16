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
    CMonster(int id, long long uid, char level, float dx, float dy,
        std::vector<CSkill> vSkill, std::list<AngerValue> lHatred,
        std::vector<int> vReware, long long money);
	~CMonster();
    static void initMonster();
	void		addHate(AngerValue hate);
	long long	getTarget();
	int			getReware();
	long long	getMoney();
    unsigned int    getXP();         
	#ifdef _GAMEENGINE_2D_
	/** @brief Client��ø�ϰʧ@ 
     * @param hdc ø�ϸ˸m */
	void		draw(HDC hdc);
	#endif

private:
	std::list<AngerValue>	m_lHatred;			//����ȦC��
	std::vector<int>		m_vReware;			//�������~
	long long				m_Money;			//��������
    
    bool                    create(unsigned int id);    //
};

#endif