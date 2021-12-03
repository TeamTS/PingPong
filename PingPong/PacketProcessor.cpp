#include "pch.h"
#include "PacketProcessor.h"
#include "Session.h"
#include "PacketBase.h"
#include "LogicGameStart.h"
#include "LogicUserId.h"

PacketProcessor::PacketProcessor()
{
	// 여기서 등록
	
}

void PacketProcessor::Process(PacketBase* packet, SessionPtr session)
{
	// packet 마다의 고유 번호가져옴.
	auto command = *reinterpret_cast<unsigned short*>(packet + 2);

	// 고유 번호로 처리할 로직을 찾는다.
	auto iter = mCommands.find(command);

	// 처리할 로직이 없는 경우
	if (iter == mCommands.end())
	{
		assert(false && "iter == mCommands.end()");
		return;
	}

	// 로직 처리 실행
	iter->second->Execute(packet, session);


	session->MoveProcessPoint(packet);
}

void PacketProcessor::Initialize()
{
	// 패킷 처리 객체 등록
	Register(new LogicGameStart);
	Register(new LogicUserId);
}
