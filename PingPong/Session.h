#pragma once

class GameObject;
class Session
{
public:
	Session();
	virtual ~Session();

	bool Initialize();
	bool Connect(const char* ip, unsigned short port);

	static unsigned int __stdcall RecvThreadFunc(void* arg);
	static unsigned int __stdcall SendThreadFunc(void* arg);

private:
	unsigned int SendThread();
	unsigned int RecvThread();

private:
	SOCKET mSocket = NULL;
	static const int MaxRecvBufferLen = 2048;
	char mRecvBuffer[MaxRecvBufferLen] = {};
	int  mCurPacketLen = 0;
	BOOL IsConnect = false;
};

