#pragma once


#include "ICommand.h"
#include "LogicGameStart.h"

class Session;
class PacketProcessor
{
public:
	PacketProcessor();
	~PacketProcessor()
	{
		for (auto packet : mCommands)
		{
			delete packet.second;
			packet.second = nullptr;
		}

		mCommands.clear();
	}

	void Register(ICommand* command)
	{
		if (command == nullptr)
			assert(false && "command == nullptr");

		auto code = command->GetCode(); // 해당 패킷 처리객체의 command값을 가져옴.

		auto iter = mCommands.find(code);

		if (mCommands.end() != iter)
			assert(false && "mCommands.end() != iter");

		mCommands[code] = command;
	}

	void Process(PacketBase* packet, Session* session);

	void Initialize()
	{
		// 패킷 처리 객체 등록
		Register(new LogicGameStart);
	}

private:
	// packet command, command object

	// key : 패킷 고유 번호, value : 패킷 처리 객체 
	std::map<unsigned short, ICommand*> mCommands;
};

