#ifndef _CBACKPACK_H_
#define _CBACKPACK_H_
#include "Common.h"
#include "CItem.h"
#include "IPlayerBackpackEventListener.h"

class CBackpack
{
   public:
	   void setGrid(int grid, CItem& itm);		           //�]�w�椤���e�O����(net pack�ϥ�)

	   CItem* getItem(int grid);					           //���o�o�椺�e
      CItemInfo* getItemInfo(int grid);                 //���o�o�椺�e

	   void addItem(int itemID, int &stack, int &grid);  //�W�[���~ id ���~�s�� stack �ƶq
      void removeItem(int itemID);                      //�������~(���| - 1)
		void removeGrid(int grid);

      // Add by Darren Chen on 2013/01/13 {
      int getSize();                                     // ���o�I�]�`���

      /** @brief �[�J��ť���a�I�]�ƥ󪺪���
        * @param pListener ��ť�� */
      void addPlayerBackpackEventListener(IPlayerBackpackEventListener *pListener);

      /** @brief ������ť���a�I�]�ƥ󪺪���
           * @param pListener ��ť�� */
      void removePlayerBackpackEventListener(IPlayerBackpackEventListener *pListener);
      // } Add by Darren Chen on 2013/01/13

	   void initBack();								          //�w�]����إߦ������~

   private:
      /** @brief �q�����a�I�]����s */
      void notifyPlayerBackpackUpdate();

	   CItem m_itemBack[BACK_MAX];

      std::set<IPlayerBackpackEventListener *> m_playerBackpackEventListeners; // ��ť���a�I�]���ܪ���ť�̦C��
};

#endif