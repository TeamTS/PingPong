#pragma once

#include "PacketProcessor.h"

enum class SessionType : unsigned char
{
	GameServer
};


class NetworkManager : public Singleton::INode
{
private:
	using Sessions = std::unordered_map<SessionType, SessionPtr>;
	Sessions mSessions;

	using PacketData = std::pair<SessionPtr, PacketBase*>;
	concurrency::concurrent_queue<PacketData> mPacketQueue;

	PacketProcessor mPacketProcessor;

public:
	NetworkManager() = default;
	~NetworkManager() = default;

	bool Initialize(); 
	void Run();

	bool Connect(SessionType sessionType, const char* ip, unsigned short port);
	void Update();
	void SendPacket();

};

