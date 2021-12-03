#pragma once

class RingBuffer
{
public:
	explicit RingBuffer();
	~RingBuffer();

private:
	static const int PacketBufferSize = 65000; // ���� ũ��
	static const int ExceptBufferSize = 1000;  // ���� ���� ũ��
	char			 mPacketBuffer[PacketBufferSize + ExceptBufferSize] = {};
	char* mStartPoint = nullptr;
	char* mEndPoint = nullptr;
	char* mWritePoint = nullptr;
	char* mReadPoint = nullptr;
	char* mProcessPoint = nullptr;
	int   mRemainSize = 65000;

public:
	int    GetCurPacketLen();
	void   FixReadBuf();
	void   AddPacketLen(int _packetLen);
	void   MoveReadBuf(unsigned short _packetLen);
	void   MoveProcessBuf(unsigned short _packetLen);
	void   TestPrint();
	int GetRemainSize();
	char* GetWritePoint();

	char* GetReadPoint();
};

