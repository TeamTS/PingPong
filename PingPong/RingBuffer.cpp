#include "pch.h"
#include "RingBuffer.h"

RingBuffer::RingBuffer()
	: mStartPoint(mPacketBuffer + ExceptBufferSize)
	, mEndPoint(mStartPoint + PacketBufferSize)
	, mWritePoint(mStartPoint)
	, mReadPoint(mStartPoint)
	, mProcessPoint(mStartPoint)
{
}

RingBuffer::~RingBuffer()
{
}

int RingBuffer::GetCurPacketLen()
{
	if (mWritePoint == mReadPoint)
		return 0;

	int curPacketSize = static_cast<int>(mWritePoint - mReadPoint);

	// 쓰기 위치가 읽기 위치보다 앞일 경우
	return (curPacketSize < 0 ? PacketBufferSize + curPacketSize : curPacketSize);
}

void RingBuffer::FixReadBuf()
{
	if (mEndPoint == mReadPoint)
	{
		mReadPoint = mStartPoint;
		return;
	}

	unsigned short readableSize = static_cast<unsigned short>(mEndPoint - mReadPoint);

	// 그대로 바로 읽을 수 있는 읽기버퍼의 위치 라면
	if (readableSize >= 2)
	{
		unsigned short packetSize = *reinterpret_cast<unsigned short*>(mReadPoint);

		// 패킷 길이가 읽을 수 있는 크기보다 클 경우
		if (packetSize <= readableSize)
			return;
	}

	// 예외처리용 버퍼로 복사한다.
	memcpy(mStartPoint - readableSize, mReadPoint, readableSize);
	mReadPoint = mStartPoint - readableSize;
}

void RingBuffer::AddPacketLen(int _packetLen)
{
	mWritePoint += _packetLen;

	InterlockedAdd(reinterpret_cast<LONG*>(&mRemainSize), -_packetLen);

	if (mWritePoint == mEndPoint)
		mWritePoint = mStartPoint;
}

void RingBuffer::TestPrint()
{
	printf("Write Buffer : %p \n", mWritePoint);
	printf("Read Buffer : %p \n", mReadPoint);
	printf("Start Buffer : %p \n", mStartPoint);
	printf("End Buffer : %p \n", mEndPoint);
	printf("EndPoint - ReadPoint : %d \n", int(mEndPoint - mReadPoint));
	printf("Cur PacketLen : %d \n", GetCurPacketLen());
}

int RingBuffer::GetRemainSize()
{
	return ((mWritePoint - mProcessPoint > 0) ? static_cast<ULONG>(mEndPoint - mWritePoint) : mRemainSize);
}

char* RingBuffer::GetWritePoint()
{
	return mWritePoint;
}

char* RingBuffer::GetReadPoint()
{
	return mReadPoint;
}



void RingBuffer::MoveReadBuf(unsigned short _packetLen)
{
	mReadPoint += _packetLen;
}

void RingBuffer::MoveProcessBuf(unsigned short _packetLen)
{
	mProcessPoint += _packetLen;

	InterlockedAdd(reinterpret_cast<LONG*>(&mRemainSize), _packetLen);
}
