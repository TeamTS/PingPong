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
	void SetUserId(int userId);
	void MoveProcessPoint(PacketBase* packet);
	void SendPacket(const PacketBase& packet);
	bool IsConnect();
	int GetUserId() { return mUserId; }

	static unsigned int __stdcall RecvThreadFunc(void* arg);

private:
	unsigned int RecvThread();

private:
	SOCKET mSocket = NULL;
	RingBuffer mRecvBuffer;
	BOOL mIsConnect = false;
	int mUserId = -1;
};

