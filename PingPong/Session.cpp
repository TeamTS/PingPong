#include "pch.h"
#include "Session.h"

Session::Session()
{
}

Session::~Session()
{
}

bool Session::Initialize()
{
	if (INVALID_SOCKET == mSocket)
	{
		assert(false && "Failed socket()");
		return false;
	}

	return true;
}

bool Session::Connect(const char* ip, unsigned short port)
{
	SOCKADDR_IN servAddr;
	ZeroMemory(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &servAddr.sin_addr);
	
	int len = sizeof(servAddr);

	if (connect(mSocket, reinterpret_cast<SOCKADDR*>(&servAddr), len) == false)
		return false;

	InterlockedExchange(reinterpret_cast<LONG*>(&IsConnect), TRUE);

	unsigned int id = 0;
	_beginthreadex(NULL, NULL, Session::RecvThreadFunc, this, 0, &id);
	_beginthreadex(NULL, NULL, Session::SendThreadFunc, this, 0, &id);

	return true;
}

unsigned int __stdcall Session::RecvThreadFunc(void* arg)
{
	return static_cast<Session*>(arg)->RecvThread();
}

unsigned int __stdcall Session::SendThreadFunc(void* arg)
{
	return static_cast<Session*>(arg)->SendThread();
}

unsigned int Session::SendThread()
{
	while (IsConnect)
	{
		int recvByte = recv(mSocket, mRecvBuffer + mCurPacketLen, MaxRecvBufferLen - mCurPacketLen, 0);

		if (recvByte <= 0)
		{
			InterlockedExchange(reinterpret_cast<LONG*>(&IsConnect), FALSE);
			continue;
		}

		mCurPacketLen += recvByte;
		while (mCurPacketLen >= 2)
		{
			PacketBase* packet = reinterpret_cast<PacketBase*>(mRecvBuffer);

			if (packet->size > mCurPacketLen)
				break;


		}
	}

	return 0;
}

unsigned int Session::RecvThread()
{
	while (IsConnect)
	{

	}

	return 0;
}
