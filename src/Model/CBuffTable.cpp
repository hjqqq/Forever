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
		FloatPrecentAttribute preAttr;

		AttributeClear(ComAttr);
        ComAttr.AdvAttr.fATKSpeed = 0.0f;
        ComAttr.AdvAttr.fCasting = 0.0f;
        ComAttr.AdvAttr.fMove = 0.0f;
		AttributeClear(preAttr);

		ComAttr.ObsAttr.iHPR = 50;
		preAttr.fHPMax = 150;

		pB->initBuff("�D������", "3�������A�̤j�ͩR����50%�B�ͩR�^�_�t�״���50�I", "",
			ComAttr, preAttr, 3, true);
        addInfo(pB);
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

	if(0.0f >= m_fSurplus)
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