#include "npc_chat_wnd.h"
#include "npc.h"
#include "net_packet.h"

//�I�]����
void NPCChatWnd::init (int _x, int _y, Player* pb, NetStream* pns)
	{
		selQuestID = -1 ;//�ثe�諸���Ƚs��

		type = TYPE_CHAT ;

		pPlayer = pb ;
		x = _x ;
		y = _y ;
		pStream = pns ;
		pNPC = NULL ;

		w = 200 ;
		h = (CHAT_H_COUNT+QUEST_H_COUNT+1)*CELL_SIZE+CELL_SIZE ;

		for (int i = 0; i<QUEST_H_COUNT+CHAT_H_COUNT+1; i++)
		{
			TextButton* pBtn = new TextButton ;
			pBtn->x = 0 ;
			pBtn->y = (i+1)*CELL_SIZE ;
			pBtn->w = w ;
			pBtn->h = CELL_SIZE ;
			pBtn->id = i ;
			pBtn->str = "" ;

			if (i == QUEST_H_COUNT+CHAT_H_COUNT)
			{
				//������
				pBtn->x = w/2 ;
				pBtn->w = w/2 ;
				pBtn->str = "��������" ;
				pBtn->bVisible = false ;
			}

			vpBtn[i] = pBtn ;

			addChild (pBtn) ;
		}
	}

void NPCChatWnd::setNPC (NPC* pnp)
{
	pNPC = pnp ;
	selQuestID = -1 ;//�ثe�諸���Ƚs��

	if (pNPC == NULL)
		return ;

	Quest* pQuest = pPlayer->questMap.onClickNPC (pNPC->getID ()) ;
	if (pQuest != NULL)
	{
		//�i�H��������
		type = TYPE_REWARD ;

		for (int i = 0; i<QUEST_H_COUNT+CHAT_H_COUNT+1; i++)
			vpBtn[i]->bVisible = false ;

		QuestInfo* pQuestInfo = pQuest->getInfo () ;

		for (int i = 0; i<2; i++)
		{
			ItemInfo* pItemInfo = Item::getInfo (pQuestInfo->vRewardItem[i]) ;
			if (pItemInfo != NULL)
			{
				vpBtn[i]->str = pItemInfo->name ;
				vpBtn[i]->bVisible = true ;
			}
		}
	}else
	{
		type = TYPE_CHAT ;

		NPCInfo* pinfo = pNPC->getInfo () ;

		for (int i = 0; i<QUEST_H_COUNT+CHAT_H_COUNT+1; i++)
			vpBtn[i]->bVisible = false ;

		int offset = 0 ;
		for (int i = 0; i<pinfo->vQuestID.size (); i++)
		{
			int questID = pinfo->vQuestID[i] ;
			if (pPlayer->questMap.canAddQuest (questID))
			{
				//�i�H�[����
				QuestInfo* pQuestInfo = QUEST_INFO::getInfo (questID) ;
				if (pQuestInfo != NULL)
				{
					vpBtn[offset]->str = pQuestInfo->name ;
					vpBtn[offset]->bVisible = true ;
					offset ++ ;
				}
			}
		}

		for (int i = 0; i<3; i++)
		{
			EasyStr <64> text = pinfo->vChatInfo[i] ;

			if (text.length () > 0)
			{
				vpBtn[QUEST_H_COUNT+i]->str = text ;
				vpBtn[QUEST_H_COUNT+i]->bVisible = true ;
			}
		}

	}
}

bool NPCChatWnd::canDrag (int tx, int ty)
{
	return ty < CELL_SIZE ;
}

void NPCChatWnd::onCommand (int btnID)
{
	if (pNPC == NULL)
		return ;

	if (type == TYPE_REWARD)
	{
		//
		Quest* pQuest = pPlayer->questMap.onClickNPC (pNPC->getID ()) ;
		if (pQuest != NULL)
		{
			PacketQuestReward pkg ;
			pkg.npcUID = pNPC->UID ;
			pkg.rewardPos = btnID ;


			pStream->send (&pkg, sizeof (pkg)) ;
			bVisible = false ;
		}
	}else
	{
		if (btnID == QUEST_H_COUNT+CHAT_H_COUNT)
		{
			//�I�F������
			PacketAddQuest pkg ;
			pkg.questID = selQuestID ;
			pStream->send (&pkg, sizeof (pkg)) ;
			bVisible = false ;
			return ;
		}

		NPCInfo* pinfo = pNPC->getInfo () ;

		int offset = 0 ;
		for (int i = 0; i<pinfo->vQuestID.size (); i++)
		{
			int questID = pinfo->vQuestID[i] ;
			if (pPlayer->questMap.canAddQuest (questID))
			{
				//�i�H�[����
				QuestInfo* pQuestInfo = QUEST_INFO::getInfo (questID) ;
				if (pQuestInfo != NULL)
				{
					if (btnID == offset)
					{
						//�I��Y�ӥ���button
						selQuestID = questID ;

						//�ק��ܤ��e,�令���ȸ�T
						vpBtn[QUEST_H_COUNT]->str = 
									pQuestInfo->info ;
						vpBtn[QUEST_H_COUNT]->bVisible = true ;
						vpBtn[QUEST_H_COUNT+1]->bVisible = false ;
						vpBtn[QUEST_H_COUNT+2]->bVisible = false ;

						//�Ⱶ���Ȫ����s��ܥX��
						vpBtn[QUEST_H_COUNT+CHAT_H_COUNT]->bVisible = true ;
					}

					offset ++ ;
				}
			}
		}

	}

}


void NPCChatWnd::draw (HDC hdc, int ox, int oy)
{
	Window::draw (hdc, ox, oy) ;

	if (pNPC == NULL)
		return ;

	NPCInfo* pinfo = pNPC->getInfo () ;

	/*
	int offset = 0 ;
	for (int i = 0; i<pinfo->vQuestID.size (); i++)
	{
		int questID = pinfo->vQuestID[i] ;
		if (pPlayer->questMap.canAddQuest (questID))
		{
			//�i�H�[����
			QuestInfo* pQuestInfo = QUEST_INFO::getInfo (questID) ;
			if (pQuestInfo != NULL)
			{
				TextOut (hdc, x+2, y+2+(offset+1)*CELL_SIZE,
					pQuestInfo->name, pQuestInfo->name.length ()) ;
				offset ++ ;
			}
		}
	}


	for (int i = 0; i<3; i++)
	{
		EasyStr <64> text = pinfo->vChatInfo[i] ;

		TextOut (hdc, x+2, y+2+(CELL_SIZE+i+3)*3,
			text, text.length ()) ;
	}
	*/
}
