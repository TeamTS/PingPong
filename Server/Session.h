#pragma once
class Session
{
public:
	Session(SOCKET socket, SOCKADDR_IN sockAddr, int id);
	~Session();
	bool RecvPacket();

private:
	static const int RecvBufferSize = 1024;
	char mRecvBuffer[RecvBufferSize] = {};
	int mCurPacketLen = 0;
	SOCKET mSocket;
	SOCKADDR_IN mSockAddr;
	int mId;
};

