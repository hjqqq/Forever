#ifndef _CPLAYER_H_
#define _CPLAYER_H_
#include "CUnitObject.h"
#include "CBackpack.h"
#include "IPlayerAttrEventListener.h"
#include "IPlayerEquipEventListener.h"
#include "IPlayerBackpackEventListener.h"
#include "IPlayerHotKeyEventListener.h"

// Add by Darren Chen on 2013/01/12 {
typedef struct tagHOTKEYITEM {
   int     iField;  // ���@����쪺�ֱ���
   CItem  *pItem;   // �n��JHotKey�C�������~
   CSkill *pSkill;  // �n��JHotKey�C�����ޯ�
} HotKeyItem;
// } Add by Darren Chen on 2013/01/12

class CPlayer : public CUnitObject
{
public:
   CPlayer(std::string machineName, std::string strName, long long uid, char level = 1);	//�إߨ��� �ǤJ�W�r�B����(�w�]�إ߫ᬰ1��)
   virtual ~CPlayer();  // Add by Darren Chen on 2013/01/12

	void addXP(unsigned int xp);	//�W�[XP unsigned ���a�t��
	unsigned int getXP();			//Ū��XP
	unsigned int getXPMax();		//Ū���̤jXP
	CBackpack* getBackpack();		//���o�I�]

   /** @brief ���˳���W
     * @param es     �˳Ƴ���
     * @param itemID ���~�s�� (�Y�˳�)
     * Modify by Darren Chen on 2013/01/07 */
	void wearToEquipSlot(EquipSlot es, int itemID);
	void shedEquip(EquipSlot grid);	    //��U ����˳��� �˳�
	std::map<EquipSlot, int> getEquip(); //���o�˳�map�}�C
	int getEquip(EquipSlot equip);	    //���o���@��˳�

   // Add by Darren Chen on 2012/12/26 {
   void addMoney(long long money);  // �W�[����
   long long getMoney();            // Ū������

   void useItem(int itemID);        // �ϥ�id�����~(�t�Z��/����/���өʹD��)

   /** @brief �s�W�ֱ�����
     * @param newHotKeyItem �ֱ����� */
   void addHotKeyItem(HotKeyItem &newHotKeyItem);

   /** @brief ���o�ֱ�����
     * @param field �������ֱ���
     * @return �ֱ����� */
   HotKeyItem* getHotKeyItem(int field);

   /** @brief ���o�ֱ��䦳�X�� */
   int getHotKeySize();

   void skillDamage(AdvancedAttribute targetAttr);

   /** @brief �[�J��ť���a�ݩʨƥ󪺪���
        * @param pListener ��ť�� */
   void addPlayerAttrEventListener(IPlayerAttrEventListener *pListener);

   /** @brief ������ť���a�ݩʨƥ󪺪���
        * @param pListener ��ť�� */
   void removePlayerAttrEventListener(IPlayerAttrEventListener *pListener);

   /** @brief �[�J��ť���a�˳ƨƥ󪺪���
        * @param pListener ��ť�� */
   void addPlayerEquipEventListener(IPlayerEquipEventListener *pListener);

   /** @brief ������ť���a�˳ƨƥ󪺪���
        * @param pListener ��ť�� */
   void removePlayerEquipEventListener(IPlayerEquipEventListener *pListener);

   /** @brief �[�J��ť���a�I�]�ƥ󪺪���
        * @param pListener ��ť�� */
   void addPlayerBackpackEventListener(IPlayerBackpackEventListener *pListener);

   /** @brief ������ť���a�I�]�ƥ󪺪���
        * @param pListener ��ť�� */
   void removePlayerBackpackEventListener(IPlayerBackpackEventListener *pListener);

   /** @brief �[�J��ť���a�ֱ���ƥ󪺪���
        * @param pListener ��ť�� */
   void addPlayerHotKeyEventListener(IPlayerHotKeyEventListener *pListener);

   /** @brief ������ť���a�ֱ���ƥ󪺪���
        * @param pListener ��ť�� */
   void removePlayerHotKeyEventListener(IPlayerHotKeyEventListener *pListener);

#ifdef _GAMEENGINE_2D_
   /** @brief Client��ø�ϰʧ@ 
     * @param hdc ø�ϸ˸m */
   /* virtual */ void draw(HDC hdc);
#endif
   // } Add by Darren Chen on 2012/12/26

private:
   friend class CWorldServer;         // ���\CWorldServer���󪽱���private/protected�������s��
   friend class CPacketPlayerDataWG;  // ���\CPacketPlayerDataWG���󪽱���private/protected�������s��
   friend class CPacketPlayerInit;    // ���\CPacketPlayerInit���󪽱���private/protected�������s��
   friend class CPacketPlayerData;

	void updateEquipAttr(); //��s�˳Ƴy���������ݩ�
   void updateSkillAvailable();

   // Add by Darren Chen on 2013/01/17 {
   /** @brief �q�����a�ݩ�(xp, money)����s */
   void notifyPlayerAttrUpdate();

   /** @brief �q�����a�˳Ʀ���s
     * @param es     �˳Ƴ���
     * @param itemId ���~�s�� (�Y�˳�) */
   void notifyPlayerEquipUpdate(EquipSlot es, int itemID);

   /** @brief �q�����a���ֱ��䦳��s
     * @param pHotKeyItem ��s���ֱ��� */
   void notifyPlayerHotKeyUpdate(HotKeyItem *pHotKeyItem);
   // } Add by Darren Chen on 2013/01/17

   unsigned int               m_xp;	        //�g���
	unsigned int               m_xpMax;	     //�̤j�g���
	char                       m_levelMax;	  //�̰����� �w�]50
	std::map<EquipSlot, int>   m_mEquip;	  //�˳���
	CBackpack                 *m_pBackpack;  //�I�]

   // Add by Darren Chen on 2013/01/06 {
   long long                  m_money;     // ��
   std::vector<HotKeyItem *> *m_pvtHotKey; // �ֱ�����

   std::set<IPlayerAttrEventListener *>     m_playerAttrEventListeners;     // ��ť���a�ݩʧ��ܪ���ť�̦C��
   std::set<IPlayerEquipEventListener *>    m_playerEquipEventListeners;    // ��ť���a�˳Ƨ��ܪ���ť�̦C��
   std::set<IPlayerHotKeyEventListener *>   m_playerHotKeyEventListeners;   // ��ť���a�ֱ�����ܪ���ť�̦C��
   // } Add by Darren Chen on 2013/01/06
};

#endif