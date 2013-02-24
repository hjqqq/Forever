#ifndef _CQUEST_H_
#define _CQUEST_H_

#include "CQuestInfoLoader.h"
#include "obj_mTable.h"
#include "CBackPack.h"

typedef ObjTable<CQuestInfo*, CQuestInfoLoader> QUEST_INFO;

class CQuest:public QUEST_INFO
{
public:
	CQuest();
	~CQuest();
	static void	initQuest();						//��l
	bool	create(int kindID);						//�]�w
	int		getConst();								//���o�ثe�����ƶq
	bool	canReply();								//���o�O�_����
	bool	onKill(int id);							//��s���ǥ��ȸ�T
	bool	getItem(int grid, CBackpack& backPack);	//��s���o���~��T�A�ǤJ�I�]�B��s�F���@��
	bool	onTalk(int id);							//��s��ܥ���
private:
	friend class CPacketQuestData;
	int		m_iConst;	//���ȥؼХثe�����ƶq
	bool	m_bFinish;	//�O�_����
};
#endif