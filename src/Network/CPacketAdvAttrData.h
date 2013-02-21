#ifndef _CPACKETADVATTRDATA_H_
#define _CPACKETADVATTRDATA_H_
#include "CBasePacket.h"
#include "CUnitObject.h"

class CPacketAdvAttrData : public CBasePacket
{
   public:
      CPacketAdvAttrData() : CBasePacket(PACKET_ADVATTR_DATA)
      {
      }

      long long getUID();
      void pack(CUnitObject *pUnitObject);
      void unpack(CUnitObject *pUnitObject);

   private:
      long long         m_uid;            //�ߤ@�s��
      AdvancedAttribute m_advAttr;        //�ݩ�
};

#endif  // #ifndef _CPACKETADVATTRDATA_H_