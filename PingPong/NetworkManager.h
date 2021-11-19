#pragma once

enum class SessionType : unsigned char
{
	GameServer
};

class Session;
class NetworkManager
{
private:
	NetworkManager() = default;

	static NetworkManager* mInstance;

	using PlayerSession = std::shared_ptr<Session>;
	using Sessions = std::unordered_map<SessionType, PlayerSession>;
	Sessions mSessions;

public:
	~NetworkManager() = default;
	static NetworkManager& GetInstance();

	bool Initialize(); 
	void Run();

	bool Connect(SessionType sessionType, const char* ip, unsigned short port);
	void Update();

};

