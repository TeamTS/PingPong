#include "pch.h"
#include "PacketProcessor.h"
#include "Session.h"
#include "PacketBase.h"
#include "LogicGameStart.h"
#include "LogicUserId.h"

PacketProcessor::PacketProcessor()
{
	// ���⼭ ���
	
}

void PacketProcessor::Process(PacketBase* packet, SessionPtr session)
{
	// packet ������ ���� ��ȣ������.
	auto command = *reinterpret_cast<unsigned short*>(packet + 2);

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

void PacketProcessor::Initialize()
{
	// ��Ŷ ó�� ��ü ���
	Register(new LogicGameStart);
	Register(new LogicUserId);
}
