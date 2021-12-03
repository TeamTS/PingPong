#include "pch.h"
#include "Session.h"

Session::Session(SOCKET socket, SOCKADDR_IN sockAddr, int id)
	: mSocket(socket)
	, mSockAddr(sockAddr)
	, mId(id)
{

}

bool Session::RecvPacket()
{
	int recvByte = recv(mSocket, mRecvBuffer + mCurPacketLen, RecvBufferSize - mCurPacketLen, 0);

	if (recvByte <= 0)
		return false;

	mCurPacketLen += recvByte;
	return true;
}
