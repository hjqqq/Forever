#ifndef _CNPCINFO_H_
#define _CNPCINFO_H_

#include "Common.h"
#include "CQuest.h"

const int talkSentence = 3;

class CNPCInfo
{
public:
	CNPCInfo();
	void					initNPCInfo(std::string name, std::string meshName,
		std::vector<std::string> talk, NPCType type, std::vector<int> vQuest,
		std::vector<int> viSell);
	std::string			getName();			//���o�W��
	std::string			getMeshName();		//���o�ɮצW��
	std::string			getTalk();			//���o��ܤ��e
	NPCType				getNPCType();		//���o�O����NPC
	std::vector<int>	getQuest();		//���o�֦�����(ID)
	std::vector<int>	getSell();			//���o�c�檫�~(ID)

	NPCClassType		getClassType();
	void					read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	void					write(FILE* pFile);
#endif	//#ifdef _GAMEENGINE_2D_EDITOR_
private:
	std::string m_strName;							//�W��
	std::string	m_strMeshName;						//�ɮצW��
	std::vector<std::string>	m_vstrTalk;		//���
	NPCType		m_workType;							//���� �ө� ���� NPC
	std::vector<int>	m_viQuest;					//�֦�����
	std::vector<int>	m_viSell;					//�c�檫�~
#ifdef _GAMEENGINE_2D_EDITOR_
	friend class DLGNPC;
#endif	//_GAMEENGINE_2D_EDITOR_
};

#endif