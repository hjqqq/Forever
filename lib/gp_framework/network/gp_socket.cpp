#include "gp_socket.h"

#include <stdio.h>
#include <assert.h>

namespace GP
{

//bool bInitNetwork = false ;

void NetAddress::getIPPort (char* buf, WORD bufSize)
{
	sprintf_s (buf, bufSize, "%d.%d.%d.%d : %d", A0, A1, A2, A3, Port) ;
}

void NetAddress::setIPPort (const char* str)
{
	int a0, a1, a2, a3, port ;

	sscanf_s (str, "%d.%d.%d.%d:%d", &a0, &a1, &a2, &a3, &port) ;
	A0 = a0 ;
	A1 = a1 ;
	A2 = a2 ;
	A3 = a3 ;
	Port = port ;
}

void NetAddress::setIP (const char* str)
{
	int a0, a1, a2, a3 ;

	sscanf_s (str, "%d.%d.%d.%d", &a0, &a1, &a2, &a3) ;
	A0 = a0 ;
	A1 = a1 ;
	A2 = a2 ;
	A3 = a3 ;
}

void NetAddress::release ()
{
	memset (this, 0, sizeof (NetAddress)) ;
}

//#########################################################
//#########################################################
//#########################################################

	bool AcceptSocket::isValid ()
	{
		return CurSocket != INVALID_SOCKET ;
	}

	void AcceptSocket::setSocket (SOCKET ckt)
	{
		assert (CurSocket == INVALID_SOCKET) ;
		CurSocket = ckt ;
	}

	SOCKET AcceptSocket::removeSocket ()
	{
		assert (CurSocket != INVALID_SOCKET) ;
		SOCKET skt = CurSocket ;
		CurSocket = INVALID_SOCKET ;
		return skt ;
	}

	void AcceptSocket::release ()
	{
		if (CurSocket != INVALID_SOCKET)
		{
			closesocket (CurSocket) ;
			CurSocket = INVALID_SOCKET ;
		}
	}

	AcceptSocket::AcceptSocket ():CurSocket(INVALID_SOCKET)
	{
	}

	AcceptSocket::~AcceptSocket ()
	{
		release () ;
	}

//#########################################################
//#########################################################
//#########################################################


void NetListener::procAccept ()
{
	sockaddr_in tcp_address ;
	int size = sizeof (tcp_address) ;

	while (1)
	{
		SOCKET tmpSocket = accept (CurSocket, (sockaddr*)&tcp_address, &size) ;
		if (tmpSocket != INVALID_SOCKET)
		{
			ListAcceptSocket.push_back (AcceptSocket ()) ;
			ListAcceptSocket.back ().setSocket (tmpSocket) ;
		}else
			break ;
	}
}

bool NetListener::listen ()
{
	assert (CurSocket != INVALID_SOCKET) ;
	if (::listen (CurSocket, 1) == SOCKET_ERROR)
	{
		assert (0) ;
//		//DebugStr ("\n[Error]Can't listen") ;
		return false ;
	}
	return true ;
}

bool NetListener::isAccepted ()
{
	procAccept () ;
	return ListAcceptSocket.size () > 0 ;
}

void NetListener::transferAcceptStream (_NetStream& ns)
{
	if (ListAcceptSocket.size () > 0)
	{
		ns.setAcceptStream (ListAcceptSocket.front ().removeSocket ()) ;
		ListAcceptSocket.pop_front () ;
	}
}

/*
bool NetListener::GetAddressPort (NetAddress& addr)
{
	if (CurSocket != INVALID_SOCKET)
	{
		char buf[256] ;
		_NetStream::GetHostAddress (buf, sizeof (buf)) ;
//		_NetStream::GetHostAddress (NetAddress& netAdd)

		sockaddr_in tcp_address ;
		int size = sizeof (tcp_address) ;
		memset (&tcp_address, 0, sizeof (tcp_address)) ;

		getsockname (CurSocket, (sockaddr*)&tcp_address, &size) ;
		addr.Port = ntohs (tcp_address.sin_port) ;

		int a0, a1, a2, a3 ;
		sscanf_s (buf, "%d.%d.%d.%d", &a0, &a1, &a2, &a3) ;
		addr.A0 = a0 ;
		addr.A1 = a1 ;
		addr.A2 = a2 ;
		addr.A3 = a3 ;

		return true ;
	}else
		return false ;
}
*/

bool NetListener::open (const char* strAddress, WORD port, bool bUseTCP)
{
	assert (CurSocket == INVALID_SOCKET) ;

	if (CurSocket == INVALID_SOCKET) 
	{
		//open socket
		if (bUseTCP)
		{
			CurSocket = socket (AF_INET, SOCK_STREAM, 0) ;
//			int b = true ;
//			int bsize = sizeof (b) ;
//			setsockopt (CurSocket, IPPROTO_UDP, TCP_NODELAY, (char*)&b, sizeof (b)) ;
		}
		else
		{
			CurSocket = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP) ;
//			int b = true ;
//			int bsize = sizeof (b) ;
//			setsockopt (CurSocket, IPPROTO_UDP, TCP_NODELAY, (char*)&b, sizeof (b)) ;
		}

		if (CurSocket == SOCKET_ERROR)
		{
			shutdown (CurSocket, 0x01) ;
			closesocket (CurSocket) ;
			CurSocket = INVALID_SOCKET ;
			release () ;
//			//DebugStr ("\n[Error]Can't create socket") ;
			return false ;
		}

		sockaddr_in tcp_address ;
		int size = sizeof (tcp_address) ;
		memset (&tcp_address, 0, sizeof (tcp_address)) ;

		tcp_address.sin_family = AF_INET ;
		if (strAddress == NULL)
			tcp_address.sin_addr.s_addr = INADDR_ANY ;
		else
			tcp_address.sin_addr.s_addr = inet_addr(strAddress) ;
		tcp_address.sin_port = htons (port) ;

			//bind
			if (bind (CurSocket, (sockaddr*)&tcp_address, size) == SOCKET_ERROR)
			{
				shutdown (CurSocket, 0x01) ;
				closesocket (CurSocket) ;
				CurSocket = INVALID_SOCKET ;
				release () ;
				return false ;
			}

			//set to nonblock
			u_long nonBlock = true ;
			if (ioctlsocket (CurSocket, FIONBIO, &nonBlock) == SOCKET_ERROR)
			{
				shutdown (CurSocket, 0x01) ;
				closesocket (CurSocket) ;
				CurSocket = INVALID_SOCKET ;
				release () ;
				assert (!"[Error]can't WSAAsyncSelect socket") ;
				return false ;
			}
	}else
	{
		//���୫��
		assert (0) ;
	}

	if (CurSocket != INVALID_SOCKET)
	{
		//���U�T��
		return true ;
	}else
	{
		//����
		assert (0) ;
		return false ;
	}
}

bool NetListener::startListen (WORD port)
{
	_NetStream::fnInitShareData (NULL) ;

	release () ;
	if (open (NULL, port, true))
	{
		return listen () ;
	}else
		return false ;
}

void NetListener::release ()
{
	ListAcceptSocket.clear () ;

	if (CurSocket != INVALID_SOCKET)
	{
		shutdown (CurSocket, 0x01) ;
		closesocket (CurSocket) ;
		CurSocket = INVALID_SOCKET ;
	}
}

NetListener::NetListener ():CurSocket(INVALID_SOCKET)
{
}

NetListener::~NetListener ()
{
	release () ;
}


//#########################################################

//#########################################################
//#########################################################
//#########################################################

HWND _NetStream::WorkWindow ;

void _NetStream::fnInitShareData (HWND hwnd)
{
	static bool bInit = false ;
	if (!bInit)
	{
		bInit = true ;
		//WIN SOCK INIT
		WSADATA wsaData ;
		WSAStartup (MAKEWORD (2,2), &wsaData) ;

		WorkWindow = hwnd ;

		//listener
	}
}

bool _NetStream::getHostAddress (char* buf, WORD bufSize)
{
	gethostname (buf, bufSize) ;
	hostent* pHostInfo = gethostbyname (buf) ;
	if (pHostInfo != NULL)
	{
		struct in_addr addr;
		memcpy(&addr, pHostInfo->h_addr_list[0], sizeof(in_addr));
		char* pstr = inet_ntoa (addr) ;
		strcpy_s (buf, bufSize, pstr) ;
		return true ;
	}
	return false ;
}

bool _NetStream::getHostAddress (NetAddress& netAdd)
{
	char buf[256] ;
	if (getHostAddress (buf, sizeof (buf)))
	{
		netAdd.setIP (buf) ;
		return true ;
	}
	else
		return false ;
}

bool _NetStream::getAddressPort (char* buf, WORD bufSize, WORD& port)
{
		getHostAddress (buf, bufSize) ;

		sockaddr_in tcp_address ;
		int size = sizeof (tcp_address) ;
		memset (&tcp_address, 0, sizeof (tcp_address)) ;

		getsockname (CurSocket, (sockaddr*)&tcp_address, &size) ;
		port = ntohs (tcp_address.sin_port) ;
		return true ;
}

bool _NetStream::getAddressPort (NetAddress& addr)
{
	if (CurSocket != INVALID_SOCKET)
	{
		char buf[256] ;
		getHostAddress (buf, sizeof (buf)) ;

		sockaddr_in tcp_address ;
		int size = sizeof (tcp_address) ;
		memset (&tcp_address, 0, sizeof (tcp_address)) ;

		getsockname (CurSocket, (sockaddr*)&tcp_address, &size) ;
		addr.Port = ntohs (tcp_address.sin_port) ;

		int a0, a1, a2, a3 ;
		sscanf_s (buf, "%d.%d.%d.%d", &a0, &a1, &a2, &a3) ;
		addr.A0 = a0 ;
		addr.A1 = a1 ;
		addr.A2 = a2 ;
		addr.A3 = a3 ;

		return true ;
	}else
		return false ;
}

bool _NetStream::getAddressPort (char* buf, WORD bufSize)
{
		getHostAddress (buf, bufSize) ;

		sockaddr_in tcp_address ;
		int size = sizeof (tcp_address) ;
		memset (&tcp_address, 0, sizeof (tcp_address)) ;

		getsockname (CurSocket, (sockaddr*)&tcp_address, &size) ;
		WORD port = ntohs (tcp_address.sin_port) ;

		char buf2[32] ;
		buf2[0] = ' ' ;
		buf2[1] = ':' ;
		buf2[2] = ' ' ;
		_itoa_s (port, buf2+3, sizeof (buf2), 10) ;
		strcat_s (buf, sizeof (buf), buf2) ;

		return true ;
}

bool _NetStream::getPeerAddressPort (char* buf, WORD bufSize) 
{
		sockaddr_in tcp_address ;
		int size = sizeof (tcp_address) ;
		memset (&tcp_address, 0, sizeof (tcp_address)) ;

		int r = getpeername (CurSocket, (sockaddr*)&tcp_address, &size) ;
		WORD port = ntohs (tcp_address.sin_port) ;

		sprintf_s (buf, sizeof (buf), "%d.%d.%d.%d : %d", tcp_address.sin_addr.S_un.S_un_b.s_b1, 
							tcp_address.sin_addr.S_un.S_un_b.s_b2, 
							tcp_address.sin_addr.S_un.S_un_b.s_b3, 
							tcp_address.sin_addr.S_un.S_un_b.s_b4, port) ;
		return true ;
}

bool _NetStream::getPeerAddress(char* pBuf, WORD nBufSize)
{
		sockaddr_in tcp_address;
		int size = sizeof(tcp_address);
		memset(&tcp_address, 0, sizeof (tcp_address));

		int r = getpeername(CurSocket, (sockaddr*)&tcp_address, &size);

#ifdef _DEBUG
		char szBuf[64];
		sprintf_s(szBuf, "%d.%d.%d.%d", tcp_address.sin_addr.S_un.S_un_b.s_b1,
			tcp_address.sin_addr.S_un.S_un_b.s_b2, tcp_address.sin_addr.S_un.S_un_b.s_b3,
			tcp_address.sin_addr.S_un.S_un_b.s_b4);
		assert(strlen(szBuf) < nBufSize);
		strcpy_s(pBuf, nBufSize, szBuf);
#else
		sprintf_s(pBuf, sizeof(pBuf), "%d.%d.%d.%d", tcp_address.sin_addr.S_un.S_un_b.s_b1,
			tcp_address.sin_addr.S_un.S_un_b.s_b2, tcp_address.sin_addr.S_un.S_un_b.s_b3,
			tcp_address.sin_addr.S_un.S_un_b.s_b4);
#endif

	assert(0);
	return false;
}

bool _NetStream::getPeerAddressPort (NetAddress& add)
{
		sockaddr_in tcp_address ;
		int size = sizeof (tcp_address) ;
		memset (&tcp_address, 0, sizeof (tcp_address)) ;

		getpeername (CurSocket, (sockaddr*)&tcp_address, &size) ;
		add.Port = ntohs (tcp_address.sin_port) ;

		add.A0 = tcp_address.sin_addr.S_un.S_un_b.s_b1 ;
		add.A1 = tcp_address.sin_addr.S_un.S_un_b.s_b2 ;
		add.A2 = tcp_address.sin_addr.S_un.S_un_b.s_b3 ;
		add.A3 = tcp_address.sin_addr.S_un.S_un_b.s_b4 ;

		return true ;
}

bool _NetStream::isConnected ()
{
		return Flag.BIT.bLink ;
}

DWORD _NetStream::unBufSend (const void* buf, DWORD memSize, NetAddress* pAddress)
{
		int r = ::send (CurSocket, (char*)buf, memSize, 0) ;
		if (r == memSize)//���\
		{
//			//CheckSend ((char*)buf, memSize) ;
			return r ;
		}else if (r == SOCKET_ERROR)//����
		{
			int error = WSAGetLastError () ;
			if ((error == WSAEWOULDBLOCK) //||
//					(error == WSAEINPROGRESS) ||
//					(error == WSAENOBUFS)
					)
			{
				//block ���O���~
//				Flag.BIT.bCanSend = false ;
			}else
			{
				release () ;
			}
			return 0 ;
		}else//�u�ǰe����
		{
//			//CheckSend ((char*)buf, r) ;
			return r ;
		}
}

bool _NetStream::bufSend (const void* buf, DWORD memSize, NetAddress* pAddress)//
{
		DWORD bufSize = SendBuffer.getAllDataSize () ;
		if (bufSize > 0)//���ʥ]�٨S�e�X�h
		{
			//�����n���b�ʥ]�̭�
			//���i�H�~��e�X
			//�K�o�ʥ]���ǿ��~
			if (!SendBuffer.pushStream (buf, memSize))
			{
				assert (0) ;
				release () ;
				return false ;
			}else
				return true ;
		}else
		{
			int r = ::send (CurSocket, (char*)buf, memSize, 0) ;
			if (r == memSize)//���\
			{
//				//CheckSend ((char*)buf, memSize) ;
				return true ;
			}else if (r == SOCKET_ERROR)//����
			{
				//send
				int error = WSAGetLastError () ;
				if ((error == WSAEWOULDBLOCK) 
//						||
//						(error == WSAEINPROGRESS) ||
//						(error == WSAENOBUFS)
						)
				{
//					Flag.BIT.bCanSend = false ;
				//block ���O���~
					//
					if (!SendBuffer.pushStream (buf, memSize))
					{
						assert (0) ;
						release () ;
						return false ;
					}else
						return true ;
				}else
				{
					release () ;
					return false ;
				}
			}else//�u�ǰe����
			{
				//CheckSend ((char*)buf, r) ;
				memSize -= r ;
				if (!SendBuffer.pushStream ((BYTE*)buf+r, memSize))
				{
					//DebugStr ("\n SendPackageMap.AppendData Fail(2)") ;
					assert (0) ;
					release () ;
					return false ;
				}else
				{
					return true ;
				}
			}
		}
}

bool bEnableNetDebug = false ;
void EnableNetDebug (bool b)
{
	bEnableNetDebug = b ;
}

#define _SEND_IN_BUFFER_

void _NetStream::send (const void* pMem, DWORD size)
{
	if (!Flag.BIT.bLink)
	{
		release () ;
		return ;
	}

	#ifdef _SEND_IN_BUFFER_
	//�Ҧ�send���ʧ@
	//�u����e��buffer

	//�j�p
	SendBuffer.pushBlock (pMem, size) ;

	#else
	//�i�H�����e�X�h
	WORD memSize = size ;
	assert (size <= 65535) ;
	assert (((DWORD)memSize) == size) ;

	//�e�X�j�p
	if (BufSend (&memSize, sizeof (memSize), NULL))
	{
		BufSend (pMem, memSize, NULL) ;
	}else
	{
		//�p�Gbuf send������
		//�N��s�u����
		//���i�H�A�e�X
	}
	#endif
}

DWORD _NetStream::getFullPackage (void* pMem, DWORD bufSize)
{
	if (!Flag.BIT.bLink)
	{
//		release () ;
		return 0 ;
	}

	DWORD getSize ;
	void* pData = RecvBuffer.popBlock (getSize) ;
	if (pData != NULL)
	{
		assert (bufSize >= getSize) ;
		memcpy (pMem, pData, getSize) ;
		return getSize ;
	}
	else
	{
		return 0 ;
	}
}

bool _NetStream::getFullPackage (NetBuffer& tmpMem)
{
	if (!Flag.BIT.bLink)
	{
//		release () ;
		return false ;
	}

	DWORD getSize ;
	void* pData = RecvBuffer.popBlock (getSize) ;
	if (pData != NULL)
	{
		assert (tmpMem.getBufferSize () >= getSize) ;
		memcpy (tmpMem.getBuffer (), pData, getSize) ;
		tmpMem.setDataSize (getSize) ;
		return getSize != 0 ;
	}else
	{
		return false ;
	}
}

void* _NetStream::peekRecvBuffer (DWORD& dataSize)
{
	return RecvBuffer.peekStream (dataSize) ;
}

void _NetStream::clearRecvBuffer ()
{
	RecvBuffer.cutStream (RecvBuffer.getAllDataSize ()) ;
}

void _NetStream::setAcceptStream (SOCKET acceptSocket)
{
	assert (CurSocket == INVALID_SOCKET) ;

	CurSocket = acceptSocket ;
//	Register_NetStream (this) ;
	Flag.BIT.bCanSend = true ;

	//set to nonblock
	u_long nonBlock = true ;
	if (ioctlsocket (CurSocket, FIONBIO, &nonBlock) == SOCKET_ERROR)
	{
		assert (0) ;
	}

	Flag.BIT.bLink = true ;
}

bool _NetStream::procPackage ()
{
	if (!Flag.BIT.bLink)
	{
		//�|���s�u
		//�����T�{�i�H�s�u�~��

		fd_set tmpSet ;
		tmpSet.fd_array[0] = CurSocket ;
		tmpSet.fd_count = 1 ;

		//����i�H�g�J
		timeval timeV ;
		timeV.tv_sec = 0 ;
		timeV.tv_usec = 1 ;
		if (select (0, NULL, &tmpSet, NULL, &timeV) == 1)
		{
			//�i�H�g�J,�N��s�u���\
			Flag.BIT.bLink = true ;
			Flag.BIT.bTryConnect = false ;
			Flag.BIT.bCanSend = true ;
		}else
		{
			//�|���s�u
			return false ;
		}
	}

	if (!Flag.BIT.bLink)
		return false ;

	//�ˬd�O�_�i�H�g�J

	bool bHasPkg = false ;
		//���ʥ]
		//�ϥ�while loop
		//�T�w�⦬���ʥ]�������X����
//		u_long dataSize ;
		while (1)
		{
			//�w�q10k�Ӧ����
			enum {RECV_TMP_BUF_SIZE = 1024} ;
//			dataSize = 1024*100 ;
//			if (ioctlsocket (CurSocket, FIONREAD, &dataSize) != SOCKET_ERROR)
			//�令��recv�Ӵ��լO�_�_�u
			if (1)
			{
//				if (dataSize > 0)
//				if (1)
//				{
					void* pBuf = RecvBuffer.pushStream (RECV_TMP_BUF_SIZE) ;
					if (pBuf != NULL)
					{
						int r = recv (CurSocket, (char*)pBuf, RECV_TMP_BUF_SIZE, 0) ;
						if (r != SOCKET_ERROR)
						{
							if (r > 0)
							{
								bHasPkg = true ;

								//�k�٦h�t�m���Ŷ�
								RecvBuffer.popStreamTail (RECV_TMP_BUF_SIZE-r) ;

								//check
							}else//close
							{
								release () ;
								break ;
							}
						}else//error
						{
							int error = WSAGetLastError () ;
							if ((error == WSAEWOULDBLOCK))
							{
								//�k�٦h�t�m���Ŷ�
								RecvBuffer.popStreamTail (RECV_TMP_BUF_SIZE) ;

								//block ���O���~
							}else if (error == WSAEMSGSIZE)
							{
								//�ʥ]�Ӥj���i��
								assert (0) ;
								//�k�٦h�t�m���Ŷ�
								RecvBuffer.popStreamTail (RECV_TMP_BUF_SIZE) ;
							}else
							{
								release () ;
							}
							break ;
						}
					}else
					{
						assert (0) ;
						break ;
					}
//				}else
//				{
//					//�S�����
//					break ;
//				}
			}else
			{
				release () ;
				break ;
				//socket error
			}
		}

		//�e�X�ֿn���ʥ]
		if (Flag.BIT.bCanSend)
		{
			DWORD peekSize ;
			void* pData = SendBuffer.peekStream (peekSize) ;
			if (pData != NULL)//���ʥ]�٨S�e�X�h
			{
				int sendSize = unBufSend (pData, peekSize, NULL) ;

				//�����e�X�����
				if (sendSize > 0)
					SendBuffer.popStream (sendSize) ;
			}
		}

	//����O����
	RecvBuffer.alignMemory () ;
	SendBuffer.alignMemory () ;

	return bHasPkg ;
}

bool _NetStream::connect (const NetAddress& addr)//client��
{
//	assert (SocketType == TYPE_TCP) ;
	assert (CurSocket != INVALID_SOCKET) ;

	sockaddr_in tcp_address ;
	int size = sizeof (tcp_address) ;
	memset (&tcp_address, 0, sizeof (tcp_address)) ;
	tcp_address.sin_family = AF_INET ;
	tcp_address.sin_addr.S_un.S_un_b.s_b1 = addr.A0 ;
	tcp_address.sin_addr.S_un.S_un_b.s_b2 = addr.A1 ;
	tcp_address.sin_addr.S_un.S_un_b.s_b3 = addr.A2 ;
	tcp_address.sin_addr.S_un.S_un_b.s_b4 = addr.A3 ;
	tcp_address.sin_port = htons (addr.Port) ;

	Flag.BIT.bTryConnect = true ;

	return ::connect (CurSocket, (sockaddr*)&tcp_address, size) == 0 ;
}

bool _NetStream::connect (const char* strAddress, WORD port)
{
	assert (CurSocket != INVALID_SOCKET) ;

	sockaddr_in tcp_address ;
	int size = sizeof (tcp_address) ;
	memset (&tcp_address, 0, sizeof (tcp_address)) ;
	tcp_address.sin_family = AF_INET ;
	tcp_address.sin_addr.s_addr = inet_addr(strAddress) ;
	tcp_address.sin_port = htons (port) ;

	Flag.BIT.bTryConnect = true ;

	return ::connect (CurSocket, (sockaddr*)&tcp_address, size) == 0 ;
}

bool _NetStream::open (const char* strAddress, WORD port, bool bUseTCP)
{
	assert (CurSocket == INVALID_SOCKET) ;

	if (CurSocket == INVALID_SOCKET) 
	{
		//open socket
		if (bUseTCP)
		{
			CurSocket = socket (AF_INET, SOCK_STREAM, 0) ;
//			int b = true ;
//			int bsize = sizeof (b) ;
//			setsockopt (CurSocket, IPPROTO_UDP, TCP_NODELAY, (char*)&b, sizeof (b)) ;
		}
		else
		{
			CurSocket = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP) ;
//			int b = true ;
//			int bsize = sizeof (b) ;
//			setsockopt (CurSocket, IPPROTO_UDP, TCP_NODELAY, (char*)&b, sizeof (b)) ;
		}
		if (CurSocket == SOCKET_ERROR)
		{
			shutdown (CurSocket, 0x01) ;
			closesocket (CurSocket) ;
			CurSocket = INVALID_SOCKET ;
			release () ;
			//DebugStr ("\n[Error]Can't create socket") ;
			return false ;
		}

		sockaddr_in tcp_address ;
		int size = sizeof (tcp_address) ;
		memset (&tcp_address, 0, sizeof (tcp_address)) ;

		tcp_address.sin_family = AF_INET ;
		if (strAddress == NULL)
			tcp_address.sin_addr.s_addr = htonl(INADDR_ANY) ;
		else
			tcp_address.sin_addr.s_addr = inet_addr(strAddress) ;
		tcp_address.sin_port = htons (port) ;

		if (!bUseTCP)
		{
			//bind
			if (port != 0)
			if (bind (CurSocket, (sockaddr*)&tcp_address, size) == SOCKET_ERROR)
			{
				assert (0) ;
				shutdown (CurSocket, 0x01) ;
				closesocket (CurSocket) ;
				CurSocket = INVALID_SOCKET ;
				release () ;
				return false ;
			}
		}

		//set to nonblock
		u_long nonBlock = true ;
		if (ioctlsocket (CurSocket, FIONBIO, &nonBlock) == SOCKET_ERROR)
		{
			assert (0) ;
		}
	}else
	{
		//���୫��
		assert (0) ;
	}

	if (CurSocket != INVALID_SOCKET)
	{
		return true ;
	}else
	{
		//����
		assert (0) ;
		return false ;
	}
}

void _NetStream::startConnect (const NetAddress& addr)//client��
{
	_NetStream::fnInitShareData (NULL) ;

	release () ;
	if (open (NULL, 0, true))
		connect (addr) ;
}

void _NetStream::stopConnection ()//����s�u
{
	release () ;
}

void _NetStream::release ()
{
	//##############################
	//�쥻���@�k����
	//�����I�sclosesocket�i��y��socket�S���u���Q���\����
	//��Osocket�귽����
	//�y���į�~�V
	//##############################
	//�I�srelease���ɭ�
	//�����n����shutdown
	//shutdown�|�e�XFD_CLOSE�T�������
	//��覬��FD_CLOSE����,�]�n�I�sshutdown
	//��O�ۤv�]�|����FD_CLOSE�T��
	
	//���ެO�֦���FD_CLOSE
	//���n���I�srecv,���ƲM��
	//�M��~��I�sclosesocket
	//##############################

	//�ѩ�bserver�ݪ��B��
	//��@�Ө���n�Q��,�Ϊ��_�u���ɭ�
	//server�|�����R������
	//��p��login server�R��LoginUserConnection
	//LoginUserConnection::release�|�I�s_NetStream��release
	//�o��_NetStream�|�Q���������w�g�O�L�Ī�
	//����ڤW���s�u�o�٨S����

	//�ѨM���覡�O
	//��n������socket�P�L�{
	//�浹�M��������޲z


	SendBuffer.release () ;
	RecvBuffer.release () ;

	if (CurSocket != INVALID_SOCKET)
	{
		//�q���n����
		shutdown (CurSocket, 0x01) ;
		CurSocket = INVALID_SOCKET ;
	}

	Flag.Reset () ;
}

_NetStream::_NetStream ():CurSocket(INVALID_SOCKET)
{
	Flag.Reset () ;
}

_NetStream::~_NetStream ()
{
	release () ;
}

}