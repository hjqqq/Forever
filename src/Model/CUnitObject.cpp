#include "CUnitObject.h"

CUnitObject::CUnitObject(std::string strName, long long uid, char level) : m_strName(strName),m_uid(uid),m_level(level)
{
	AttributeClear(m_advAttr);
}

long long CUnitObject::getUID()
{
	return m_uid;
}

std::string CUnitObject::getName()
{
	return m_strName;
}

char CUnitObject::getLevel()
{
	return m_level;
}

void CUnitObject::addHP(int hp)
{
	m_advAttr.iHP += hp;
	if(m_advAttr.iHP < 0 || m_advAttr.iHP == 0)	//�S��F ���`
	{
		m_advAttr.iHP = 0;
		//���`�{��
	}
	else if(m_advAttr.iHP > m_advAttr.iHPMax)	//�ɦ�W�L�̤j��q �O���̤j��q
	{
		m_advAttr.iHP = m_advAttr.iHPMax;
	}
}

int CUnitObject::getHP()
{
	return m_advAttr.iHP;
}

int CUnitObject::getHPMax()
{
	return m_advAttr.iHPMax;
}

void CUnitObject::addMP(int mp)
{
	m_advAttr.iMP += mp;
	if(m_advAttr.iMP < 0 || m_advAttr.iMP == 0)	//�S�]�O�F
	{
		m_advAttr.iMP = 0;
	}
	else if(m_advAttr.iMP > m_advAttr.iMPMax)	//�]�O�W�L�̤j�]�O �O���̤j�]�O
	{
		m_advAttr.iMP = m_advAttr.iMPMax;
	}
}

int CUnitObject::getMP()
{
	return m_advAttr.iMP;
}

int CUnitObject::getMPMax()
{
	return m_advAttr.iMPMax;
}
  
void CUnitObject::setAdvAttr(AdvancedAttribute advattr)
{
	m_advAttr = advattr;	//�]�w�ݩʸ��
}

AdvancedAttribute CUnitObject::getAdvAttr()
{
	return m_advAttr;
}
