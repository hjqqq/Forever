#ifndef _CPACKETMONSTERDATA_H_
#define _CPACKETMONSTERDATA_H_
#include "CBasePacket.h"
#include "CMonster.h"

#ifdef _GAMEENGINE_3D_
#include "CMonster3D.h"
#endif

class CPacketMonsterData : public CBasePacket
{
   public:
      CPacketMonsterData() : CBasePacket(PACKET_MONSTER_DATA)
      {
      }

      long long getUID();
      int getKindID();

      void pack(CMonster *pMonster);
      void unpack(CMonster *pMonster);
#ifdef _GAMEENGINE_3D_
      void unpack(CMonster3D *pMonster);
#endif

   private:
      long long             m_uid;             //�ߤ@�s��
      int                   m_kindID;          //�Ǫ�����id
      FPOS                  m_position;        //����X,Y�y�� (2D)
      FPOS                  m_targetPosition;  //�ؼ��IX,Y�y�� (2D)
      float                 m_fDirection;      //�����V(���: ����), �f�ɰw��V���ର+, ���ɰw��V���ର-, ��V��0�O�¤U
      MonsterState          m_state;           //�ثe���A
      FPOS                  m_bornPosition;    //�X��X,Y�y�� (2D)
      FPOS                  m_anchorPosition;  //�i�J�԰��w���I
};

#endif  // #ifndef _CPACKETMONSTERDATA_H_