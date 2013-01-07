#include "CItemInfo.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"

std::string CItemInfo::getName()
{
	return m_strName;
}

std::string CItemInfo::geticonName()
{
	return m_iconName;
}

ItemType CItemInfo::getItemType()
{
	return m_type;
}

bool CItemInfo::getSoulBind()
{
	return m_bSoulBind;
}

char CItemInfo::getLevel()
{
	return m_level;
}

int CItemInfo::getStackLimit()
{
	return m_iStackLimit;
}

int CItemInfo::getSellPrice()
{
	return m_iSellPrice;
}

int CItemInfo::getBuyPrice()
{
	return m_iBuyPrice;
}

CItemInfo::~CItemInfo()
{
}

AdvancedItem* CItemInfo::getAll()
{
	AdvancedItem *pItem = new AdvancedItem;
	pItem->name = getName();				//�W��
	pItem->iconName = geticonName();		//�ϥܦW��
	pItem->type = getItemType();			//����
	pItem->soulBind = getSoulBind();		//�j�w
	pItem->level = getLevel();				//����
	pItem->stackLimit = getStackLimit();	//���|�W��
	pItem->sellPrice = getSellPrice();		//���
	pItem->buyPrice = getBuyPrice();		//�R��

	return pItem;
}

void CItemInfo::setName(std::string name)
{
	m_strName = name;
}

void CItemInfo::seticonName(std::string iconName)
{
	m_iconName = iconName;
}

void CItemInfo::setItemType(ItemType type)
{
	m_type = type;
}

void CItemInfo::setSoulBind(bool soulBind)
{
	m_bSoulBind = soulBind;
}

void CItemInfo::setLevel(char level)
{
	if(level<0)
		return;
	m_level = level;
}

void CItemInfo::setStackLimit(int stackLimit)
{
	if(stackLimit<0)
		return;
	m_iStackLimit = stackLimit;
}

void CItemInfo::setSellPrice(int sellPrice)
{
	if(sellPrice<0)
		return;
	m_iSellPrice = sellPrice;
}

void CItemInfo::setBuyPrice(int buyPrice)
{
	if(buyPrice<0)
		return;
	m_iBuyPrice = buyPrice;
}

void CItemInfo::read(FILE* pFile)
{
	int version = 0;
	fread (&version, sizeof(version), 1, pFile);

	fread (&m_strName, sizeof(m_strName), 1, pFile);
	fread (&m_iconName, sizeof(m_iconName), 1, pFile);
	fread (&m_type, sizeof(m_type), 1, pFile);
	fread (&m_bSoulBind, sizeof(m_bSoulBind), 1, pFile);
	fread (&m_level, sizeof(m_level), 1, pFile);
	fread (&m_iStackLimit, sizeof(m_iStackLimit), 1, pFile);
	fread (&m_iSellPrice, sizeof(m_iSellPrice), 1, pFile);
	fread (&m_iBuyPrice, sizeof(m_iBuyPrice), 1, pFile);

}