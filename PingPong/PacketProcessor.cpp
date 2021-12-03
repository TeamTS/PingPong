#include "pch.h"
#include "PacketProcessor.h"
#include "Session.h"
#include "InGamePacket.h"

PacketProcessor::PacketProcessor()
{
	// ���⼭ ���
	
}

void PacketProcessor::Process(PacketBase* packet, Session* session)
{
	// test
	SA_UserId* testPacket = reinterpret_cast<SA_UserId*>(packet);

	// packet ������ ���� ��ȣ������.
	auto command = *reinterpret_cast<unsigned short*>(packet + sizeof(unsigned short));

	// ���� ��ȣ�� ó���� ������ ã�´�.
	auto iter = mCommands.find(command);

	// ó���� ������ ���� ���
	if (iter == mCommands.end())
	{
		assert(false && "iter == mCommands.end()");
		return;
	}

	// ���� ó�� ����
	iter->second->Execute(packet, session);


	session->MoveProcessPoint(packet);
}	
