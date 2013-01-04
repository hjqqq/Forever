#ifndef _GP_SOCKET_H_
#define _GP_SOCKET_H_

#include <winsock.h>

#include <list>

#include <memory\gp_memory_queue.h>

//#########################################################
//#########################################################
//#########################################################

namespace GP
{

class NetAddress
{
public:
	BYTE A0, A1, A2, A3 ;
	WORD Port ;

	void getIPPort (char*, WORD) ;
	void setIPPort (const char*) ;
	void setIP (const char*) ;

	void release () ;
} ;

//#########################################################
//#########################################################
//#########################################################
class AcceptSocket
{
private:
	SOCKET CurSocket ;//�ثe��socket,�Ψ�listen,��connect

public:
	bool isValid () ;

	void setSocket (SOCKET ckt) ;

	SOCKET removeSocket () ;

	void release () ;

	AcceptSocket () ;

	~AcceptSocket () ;
} ;

typedef std::list <AcceptSocket> LIST_ACCEPT_SOCKET ;

//�M���Ψ�listen
class NetStream ;
class NetListener
{
private:
	SOCKET CurSocket ;//�ثe��socket,�Ψ�listen,��connect

	LIST_ACCEPT_SOCKET ListAcceptSocket ;

private:
	void procAccept () ;

private:
	bool listen () ;//server��(TCP)

public:
	bool isAccepted () ;
	void transferAcceptStream (NetStream&) ;//��accecpt��socket�ǥX�Өϥ�

private:
	bool open (const char*, WORD, bool) ;//client & server�ϥ�,
public:
	bool startListen (WORD) ;//TCP/server��

private:
	void closeSocket () ;//����socket

public:
	void release () ;

	NetListener () ;
	~NetListener () ;
} ;

//#########################################################
//#########################################################
//#########################################################

enum {MAX_BUFFER_SIZE = 1024*10} ;
enum {MAX_PACKAGE_SIZE = 1024} ;
typedef GLocalMemory <MAX_PACKAGE_SIZE> NetBuffer ;

//�I���I
class NetStream
{
private:
	SOCKET CurSocket ;//�ثe��socket,�Ψ�listen,��connect
	static HWND WorkWindow ;

protected:
	GMemoryQueue <DWORD, MAX_BUFFER_SIZE> SendBuffer, RecvBuffer ;

public:
	//�X��
	struct _FLAG
	{
		union _BIT
		{
			struct
			{
				BYTE bLink:1 ;//�s�u��
				BYTE bTryConnect:1 ;//���ճs�u
				BYTE bCanSend:1 ;//�i�H�e��ƤF
				BYTE bWaitClose:1 ;//�������������q
			} ;

			BYTE Memory ;
		} BIT ;

		void Reset ()
		{
			BIT.Memory = 0 ;
		}
	} Flag ;

	BYTE _EndTimeRate ;

public:
	static void fnInitShareData (HWND) ;

private:
public:
	//address
	static bool getHostAddress (char*, WORD) ;
	static bool getHostAddress (NetAddress&) ;
	bool getAddressPort (char*, WORD, WORD&) ;
	bool getAddressPort (char*, WORD) ;
	bool getAddressPort (NetAddress&) ;
	bool getPeerAddressPort (char*, WORD) ;
	bool getPeerAddressPort (NetAddress&) ;
	bool getPeerAddress(char*, WORD);

	//state
	bool isConnected () ;

private:
	DWORD unBufSend (const void*, DWORD, NetAddress*) ;
	bool bufSend (const void*, DWORD, NetAddress*) ;
public:
	void send (const void*, DWORD) ;
private:
	DWORD getFullPackage (void*, DWORD) ;

public:
	bool getFullPackage (NetBuffer&) ;

private:
	void* peekRecvBuffer (DWORD&) ;
	void clearRecvBuffer () ;

public:

	void setAcceptStream (SOCKET) ;

	bool procPackage () ;

	bool connect (const NetAddress&) ;//client��(TCP)
	bool connect (const char*, WORD) ;//client��(TCP)

private:
	bool open (const char*, WORD, bool) ;//client & server�ϥ�,
public:
	void startConnect (const NetAddress&) ;//TCP/client��

	void stopConnection () ;//����s�u

	void release () ;

	NetStream () ;
	~NetStream () ;
} ;

}

#endif