#pragma once

#include "RingBuffer.h"

class GameObject;
class Session
{
public:
	Session();
	virtual ~Session();

	bool Initialize();
	bool Connect(const char* ip, unsigned short port);
	void SetGameObject(std::shared_ptr<GameObject> gameObject);
	void MoveProcessPoint(PacketBase* packet);
	void SendPacket(const PacketBase& packet);
	std::shared_ptr<GameObject> GetGameObject() { return mGameObject; }

	static unsigned int __stdcall RecvThreadFunc(void* arg);

private:
	unsigned int RecvThread();

private:
	SOCKET mSocket = NULL;
	RingBuffer mRecvBuffer;
	BOOL IsConnect = false;

	std::shared_ptr<GameObject> mGameObject;
};

