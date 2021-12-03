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

	// ���� ��ġ�� �б� ��ġ���� ���� ���
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

	// �״�� �ٷ� ���� �� �ִ� �б������ ��ġ ���
	if (readableSize >= 2)
	{
		unsigned short packetSize = *reinterpret_cast<unsigned short*>(mReadPoint);

		// ��Ŷ ���̰� ���� �� �ִ� ũ�⺸�� Ŭ ���
		if (packetSize <= readableSize)
			return;
	}

	// ����ó���� ���۷� �����Ѵ�.
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
