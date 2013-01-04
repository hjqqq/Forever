#ifndef _GP_NET_H_
#define _GP_NET_H_

#include <RakPeerInterface.h>
//#include <RakNetTypes.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <memory\gp_memory_queue.h>

#include <list>

namespace GP
{

typedef GMemoryQueue <unsigned int, 1024> MemoryBuffer ;

//�u���s�u�إ�
class NetStream
{
private:
	bool bServer ;

	enum {MAX_CONNECTION = 99} ;
	RakNet::RakPeerInterface *pPeer;

	RakNet::Packet *pPacket ;

	RakNet::RakNetGUID guid ;
	RakNet::SystemAddress clientID ;//client���s��

	MemoryBuffer recvBuffer ;

public:

	bool checkID (RakNet::RakNetGUID)const ;
	void pushRecvData (RakNet::Packet*) ;

//	bool startListen (int port) ;

	bool startConnect (const char* ip, int port) ;

	void send (const char* pdata, int dataSize) ;

private:
	void work () ;

public:
	const char* getPacket (unsigned int* pSize = NULL) ;

//	void close () ;

	NetStream () ;
	NetStream (RakNet::RakPeerInterface*, const RakNet::SystemAddress&,
				RakNet::RakNetGUID) ;
	~NetStream () ;
} ;

//###################################

typedef std::list <NetStream*> VP_NET_STREAM ;

class NetListener
{
private:
	enum {MAX_CONNECTION = 99} ;
	RakNet::RakPeerInterface *pPeer;

	RakNet::Packet *pPacket ;

	//�����s�u��
	VP_NET_STREAM vpNewStream ;//�s�s�u��
	VP_NET_STREAM vpWorkStream ;//�w�g�B�@����

public:
	NetListener () ;
	~NetListener () ;

	bool startListen (int port) ;

private:
	bool pushRecvData (RakNet::Packet*, VP_NET_STREAM&) ;
	void pushRecvData (RakNet::Packet*) ;

	void work () ;//
public:

	//���o�s�u
	NetStream* getNetStream () ;
} ;


}


#endif