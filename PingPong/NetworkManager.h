#pragma once

#include "PacketProcessor.h"

enum class SessionType : unsigned char
{
	GameServer
};


using Sessions = std::unordered_map<SessionType, SessionPtr>;
using PacketData = std::pair<SessionPtr, PacketBase*>;
class NetworkManager : public Singleton::INode
{
private:
	Sessions mSessions;

	concurrency::concurrent_queue<PacketData> mPacketQueue;

	PacketProcessor mPacketProcessor;

public:
	NetworkManager() = default;
	~NetworkManager();

	bool Initialize(); 
	void Run();

	bool Connect(SessionType sessionType, const char* ip, unsigned short port);
	void Update();

	void PushPacket(PacketData&& packetData);
	SessionPtr GetSession(SessionType sessionType);
};

