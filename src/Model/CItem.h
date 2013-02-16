#ifndef _CITEM_H_
#define _CITEM_H_
#include "obj_mTable.h"
#include "CItemInfoLoader.h"
#include "IItemEventListener.h"

typedef ObjTable <CItemInfo*, CItemInfoLoader> ITEM_INFO;

class CItem : public ITEM_INFO
{
public:	
	static void initItem ();
	CItem ();
	~CItem();
	bool addStack (int id, int& st);   //�W�[���~ id st�X��
	int getStack ();                   //���o��F�X��
	void create (int id, int st);      //�إ� �]�w

   /** @brief ���~���|��@, ���0��|�۰ʮ������~ */
	void taken();

   // Add by Darren Chen on 2013/01/21 {
   /** @brief �[�J��ť���~��ƥ󪺪���
     * @param pListener ��ť�� */
   void addItemEventListener(IItemEventListener *pListener);

   /** @brief ������ť���~��ƥ󪺪���
     * @param pListener ��ť�� */
   void removeItemEventListener(IItemEventListener *pListener);
   // } Add by Darren Chen on 2013/01/21

private:
	int m_iStack;   //���|�X��

   // Add by Darren Chen on 2013/01/21 {
   /** @brief �q�����~�榳��s */
   void notifyItemUpdate();

   std::set<IItemEventListener *> m_itemEventListeners;   // ��ť���~����ܪ���ť�̦C��
   // } Add by Darren Chen on 2013/01/21
};

#endif  // #ifndef _CITEM_H_