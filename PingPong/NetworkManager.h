#pragma once

#include "PacketProcessor.h"

enum class SessionType : unsigned char
{
	GameServer
};


using Sessions = std::unordered_map<SessionType, Session*>;
using PacketData = std::pair<Session*, PacketBase*>;
class NetworkManager : public Singleton::INode
{
private:
	Sessions mSessions;

	concurrency::concurrent_queue<PacketData> mPacketQueue;

	PacketProcessor mPacketProcessor;

	bool mIsInit = false;

public:
	NetworkManager() = default;
	~NetworkManager();

	bool Initialize(); 
	void Run();

	bool Connect(SessionType sessionType, const char* ip, unsigned short port);
	void Update();

	void PushPacket(PacketData packetData);
	Session* GetSession(SessionType sessionType);
};

