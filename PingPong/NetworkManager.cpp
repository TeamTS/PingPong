#include "pch.h"
#include "NetworkManager.h"
#include "Session.h"

NetworkManager::~NetworkManager()
{
	WSACleanup();
}

bool NetworkManager::Initialize()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		assert(false && "Failed WSAStartUp()");
		return E_FAIL;
	}

	mIsInit = true;
    return true;
}

bool NetworkManager::Connect(SessionType sessionType, const char* ip, unsigned short port)
{
	if (!mIsInit)
		return false;

	auto iter = mSessions.find(sessionType);

	if (iter != mSessions.end())
		return false;

	auto session = std::make_shared<Session>();

	if (session->Initialize() == false)
		return false;

	if (session->Connect(ip, port) == false)
		return false;

	mSessions.insert(Sessions::value_type(sessionType, session));
		
	return true;
}

void NetworkManager::Update()
{
	// 여기에 패킷이 쌓임.
	while (mPacketQueue.empty() == false)
	{
		PacketData packetData;

		// 하나씩 꺼냄
		if (mPacketQueue.try_pop(packetData))
		{
			// 패킷 처리 시도
			mPacketProcessor.Process(packetData.second, packetData.first);
		}
	}
}

void NetworkManager::PushPacket(PacketData&& packetData)
{
	mPacketQueue.push(packetData);
}

SessionPtr NetworkManager::GetSession(SessionType sessionType)
{
	auto iter = mSessions.find(sessionType);

	if (iter == mSessions.end())
		return nullptr;

	return iter->second;
}

void NetworkManager::Run()
{

}

