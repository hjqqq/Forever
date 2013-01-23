#ifndef _CPLAYER_H_
#define _CPLAYER_H_
#include "CUnitObject.h"
#include "CBackPack.h"

// Add by Darren Chen on 2013/01/12 {
typedef struct tagHOTKEYITEM {
   CItem *pItem;    // �n��JHotKey�C�������~
   CSkill *pSkill;  // �n��JHotKey�C�����ޯ�
} HotKeyItem;
// } Add by Darren Chen on 2013/01/12

class CPlayer : public CUnitObject
{
public:
	CPlayer(std::string strName, long long uid, char level = 1);	//�إߨ��� �ǤJ�W�r�B����(�w�]�إ߫ᬰ1��)
   virtual ~CPlayer();  // Add by Darren Chen on 2013/01/12

	void addXP(unsigned int xp);	//�W�[XP unsigned ���a�t��
	unsigned int getXP();			//Ū��XP
	unsigned int getXPMax();		//Ū���̤jXP
	CBackPack getBackPack();		//���o�I�]

	void shedEquip(EquipSlot grid);	    //��U ����˳��� �˳�
	std::map<EquipSlot, int> getEquip(); //���o�˳�map�}�C
	int getEquip(EquipSlot equip);	    //���o���@��˳�

   // Add by Darren Chen on 2012/12/26 {
   void addMoney(long long money);  // �W�[����
   long long getMoney();            // Ū������

   void useItem(unsigned int itemID);   // �ϥ�id�����~(�t�Z��/����/���өʹD��)

   /** @brief �s�W�ֱ�����
     * @param field         �������ֱ���
     * @param newHotKeyItem �ֱ����� */
   void addHotKeyItem(int field, HotKeyItem &newHotKeyItem);

   /** @brief ���o�ֱ�����
     * @param field �������ֱ���
     * @return �ֱ����� */
   HotKeyItem* getHotKeyItem(int field);

   /** @brief ���o�ֱ��䦳�X�� */
   int getHotKeySize();

   void skillDamage(AdvancedAttribute targetAttr);

#ifdef _GAMEENGINE_2D_
   /** @brief Client��ø�ϰʧ@ 
     * @param hdc ø�ϸ˸m */
   /* virtual */ void draw(HDC hdc);
#endif
   // } Add by Darren Chen on 2012/12/26

private:
	void updateEquipAttr(); //��s�˳Ƴy���������ݩ�
        void updateSkillAvailable();

   /** @brief ���˳���W
     * @param es �˳Ƴ���
     * @param id �s�˳ƽs��
     * Modify by Darren Chen on 2013/01/07 */
	void wearToEquipSlot(EquipSlot es, unsigned int id);

   // Add by Darren Chen on 2013/01/17 {
   /** @brief �q����ť�̥����󪺭I�]����s */
   void notifyUpdateBackpack();
   void notifyUpdateBackpack(CItem *pItem);

   /** @brief �q����ť�̥�����HotKeyItem����s
     * @param field       �������ֱ���
     * @param pHotKeyItem ��s������ */
   void notifyUpdateHotKeyItem(int field, HotKeyItem *pHotKeyItem);
   // } Add by Darren Chen on 2013/01/17

   unsigned int               m_xp;	       //�g���
	unsigned int               m_xpMax;	    //�̤j�g���
	char                       m_levelMax;	 //�̰����� �w�]50
	std::map<EquipSlot, int>   m_mEquip;	 //�˳���
	CBackPack                  m_backPack;  //�I�]

   // Add by Darren Chen on 2013/01/06 {
   long long                  m_money;     // ��
   std::vector<HotKeyItem *> *m_pvtHotKey; // �ֱ�����
   // } Add by Darren Chen on 2013/01/06
};

#endif