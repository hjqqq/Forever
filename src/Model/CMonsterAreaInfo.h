#ifndef _CMONSTERAREAINFO_H_
#define _CMONSTERAREAINFO_H_

#include "Common.h"

class CMonsterAreaInfo
{
public:
	void					initMonsterAreaInfo(int maxMonster, float fx, float fy, float bornSize,
		                                   int AddTime, std::vector<int> viMonsterID);	//��l
	int					getMaxMonster();					//���o�̤j�X�Ͷq
	const FPOS&			getPosition();						//���o�X���I
	float					getBornSize();						//���o�d��
	int					getAddTime();						//�h�[�ͤ@��
	std::vector<int>	getBornMonsterID();				//���o�|�ͪ��Ǻ���
	void					read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	void					write(FILE* pFile);
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
	MonsterArea			getClassType();

private:
	int					m_iMaxMonster;		//�̤j�ƶq
	FPOS					m_position;			//�X���I
	float					m_fBornSize;		//�d���
	int					m_fAddTime;			//�h�[�ͤ@��
	std::vector<int>	m_viMonsterID;		//�|�ͪ���
#ifdef _GAMEENGINE_2D_EDITOR_
	friend class DLGMonsterArea;
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
};

#endif //#ifndef _CMONSTERAREAINFO_H_