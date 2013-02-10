/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWorldServer.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#ifndef _CWORLDSERVER_H_
#define _CWORLDSERVER_H_
#include "Common.h"
#include "CPlayerServerID.h"
#include "CPacketPasswordGW.h"

#include <network\gp_socket.h>

class CWorldServer
{
   public:
      CWorldServer(std::string machineName);
      ~CWorldServer();

      /** @brief ��l�� */
      void init(int port);

      /** @brief �޿��s
        * @param hWnd window����
        * @param timePass �@��frame�X�� */
      void work(HWND hWnd, float timePass);

   private:
      CPlayerServerID* addPlayerServerID(GP::NetStream *pNetStream);

      /** @brief �B�zGameServer���ʥ] 
        * @param pNetStream GameServer�������s�u */
      void procGameServer(GP::NetStream *pNetStream);

      void onRecvPasswordGW(GP::NetStream *pNetStream, CPacketPasswordGW *pPacket);

      std::string                    m_machineName;     // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      std::vector<std::string>       m_nameVector;       // ���a�W�٦C��
      GP::NetListener                m_listener;
      long long                      m_curUID;           // �ثe��UID
      std::list<GP::NetStream *>    *m_pNetStreamList;   // �PGameServer�����s�u
      std::list<CPlayerServerID *>  *m_pPlayerList;      // �Ҧ����a
};

#endif  // #ifndef _CWORLDSERVER_H_