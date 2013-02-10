#ifndef _CNETPLAYER_H_
#define _CNETPLAYER_H_
#include "Common.h"

#include <network\gp_socket.h>

class CPlayer;

class CNetPlayer
{
   public:
      enum {STATE_WAIT_LOGIN_DATA, 
			   STATE_WAIT_PLAYER_DATA, //��world server�e������
			   STATE_PLAY,
			   STATE_LOGOUT};

      CNetPlayer();
      ~CNetPlayer();

      int            m_state;
      CPlayer       *m_pPlayer;
      GP::NetStream *m_pNetStream;
      long long      m_netID;     //�ߤ@���s��
};

#endif  // #ifndef _CNETPLAYER_H_