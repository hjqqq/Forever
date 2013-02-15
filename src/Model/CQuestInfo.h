#ifndef _CQUESTINFO_H_
#define _CQUESTINFO_H_

#include "Common.h"

class CQuestInfo
{
public:
	CQuestInfo();
	~CQuestInfo();
	void			initQuestInfo(std::string name, std::string desc, char level, int perQuestID,
		QuestType eventType, int MonsterID, int TalkID, int ItemID, int Const,
		std::vector<int> reware, int xp, long long money);
	std::string getName();					//���o�W��
	std::string getDesc();					//���o����
	char			getLevel();					//���o�ӱ�����
	int			getPerQuestID();			//���o�e�m����
	QuestType	getQuestType();			//���o���إ��ȥؼ�
	int			getMonsterID();			//���o�Ǫ�ID
	int			getTalkID();				//���o���ܹ�HID
	int			getItemID();				//���o���~ID
	int			getTragetID();				//���o���ȥؼ�ID
	int			getConst();					//���o�ؼмƶq
	std::vector<int>	getItemReware();	//���o���~���S
	int			getXP();						//���o�g����S
	long long	getMoney();					//���o�������S

	void			read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	void			write(FILE* pFile);
#endif	//#ifdef _GAMEENGINE_2D_EDITOR_
	QuestClassType	getClassType();
private:
	std::string m_strName;			//�W��
	std::string m_strDesc;			//����
	char			m_Level;				//�ӱ�����
	int			m_iPerQuestID;		//�e�m����ID
	QuestType	m_EventType;		//���ȥؼк���
	int			m_iMonsterID;		//�Ǫ�ID
	int			m_iTalkID;			//���ܹ�HID
	int			m_iItemID;			//���~ID
	int			m_iConst;			//�F���ؼмƶq
	std::vector<int> m_viReware;	//���~�^��
	int			m_ixp;				//�g��^��
	long long	m_Money;				//�����^��
};

#endif