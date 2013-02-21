#ifndef _CPACKETNPCDATA_H_
#define _CPACKETNPCDATA_H_

#include "CBasePacket.h"
#include "CNPC.h"

#ifdef _GAMEENGINE_3D_
#include "CNPC3D.h"
#endif

class CPacketNPCData : public CBasePacket
{
public:
	CPacketNPCData();

	long long getUID();
   int getKindID();

   void pack(CNPC *pNPC);
   void unpack(CNPC *pNPC);
#ifdef _GAMEENGINE_3D_
   void unpack(CNPC3D *pNPC);
#endif
private:
	long long             m_uid;             //�ߤ@�s��
   int                   m_kindID;          //npc����id
   FPOS                  m_position;        //����X,Y�y�� (2D)
   float                 m_fDirection;      //�����V(���: ����), �f�ɰw��V���ର+, ���ɰw��V���ର-, ��V��0�O�¤U
};

#endif