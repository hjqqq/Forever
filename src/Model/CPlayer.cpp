#include "CPlayer.h"

CPlayer::CPlayer(std::wstring strName, long long uid, char level) : CUnitObject(strName, uid, level), m_levelMax(50)
{
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
