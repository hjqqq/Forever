#include "CBuffTable.h"
#include "AttributeSet.h"

void CBuffTable::initCBuffTable()
{
	if(BUFF_INFO::read("Buff.la"))
	{
	}
	else
	{
		CBuff* pB = new CBuff();
		ComplexAttribute ComAttr;
		ComplexAttribute ComPercent;

		AttributeClear(ComAttr);
		AttributeClear(ComPercent);

		ComAttr.ObsAttr.iHPR = 50;
		ComPercent.AdvAttr.iHPMax = 50;

		pB->initBuff("�D������", "3�������A�̤j�ͩR����50%�B�ͩR�^�_�t�״���50�I", "",
			ComAttr, ComPercent, 3, true);
	}
}

float CBuffTable::getSurplus()
{
	return m_fSurplus;
}

void CBuffTable::create(unsigned int id)
{
	BUFF_INFO::create(id);

	CBuff* pInfo = BUFF_INFO::getInfo();

	if(NULL != pInfo)
	{
		m_fSurplus = pInfo->getContinued();
	}
}

bool CBuffTable::afterTime(float timePass)
{
	m_fSurplus -= timePass;

	if(0.0f >= timePass)
	{
		m_fSurplus = 0.0f;
		clear();
		return true;
	}
	return false;
}

CBuffTable::CBuffTable()
{
}

CBuffTable::~CBuffTable()
{
}