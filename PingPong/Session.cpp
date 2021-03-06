#include "pch.h"
#include "Session.h"
#include "NetworkManager.h"
#include <exception>

Session::Session()
{
	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == mSocket)
		throw new std::exception("create socket error");
}

Session::~Session()
{
	closesocket(mSocket);
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

	if (connect(mSocket, reinterpret_cast<SOCKADDR*>(&servAddr), len) == SOCKET_ERROR)
		return false;

	InterlockedExchange(reinterpret_cast<LONG*>(&mIsConnect), TRUE);

	unsigned int id = 0;
	_beginthreadex(NULL, NULL, Session::RecvThreadFunc, this, 0, &id);

	return true;
}

void Session::SetUserId(int userId)
{
	mUserId = userId;
}

void Session::MoveProcessPoint(PacketBase* packet)
{
	mRecvBuffer.MoveProcessBuf(packet->size);
}

void Session::SendPacket(const PacketBase& packet)
{
	send(mSocket, reinterpret_cast<const char*>(&packet), packet.size, 0);
}

bool Session::IsConnect()
{
	return mIsConnect;
}

unsigned int __stdcall Session::RecvThreadFunc(void* arg)
{
	return static_cast<Session*>(arg)->RecvThread();
}

unsigned int Session::RecvThread()
{
	auto& networkManager = *Singleton::Get<NetworkManager>();

	while (mIsConnect)
	{
		int recvByte = recv(mSocket, mRecvBuffer.GetWritePoint(), mRecvBuffer.GetRemainSize(), 0);

		if (recvByte <= 0)
		{
			InterlockedExchange(reinterpret_cast<LONG*>(&mIsConnect), FALSE);
			continue;
		}

		mRecvBuffer.AddPacketLen(recvByte);

		while (true)
		{
			int curPacketLen = mRecvBuffer.GetCurPacketLen();

			if (curPacketLen < 2)
				break;

			mRecvBuffer.FixReadBuf();

			PacketBase* packet = reinterpret_cast<PacketBase*>(mRecvBuffer.GetReadPoint());

			if (packet->size > curPacketLen)
				break;

			mRecvBuffer.MoveReadBuf(packet->size);
			networkManager.PushPacket(PacketData(this, packet));
		}
	}

	return 0;
}
