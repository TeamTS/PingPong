#pragma once


#include "ICommand.h"

class Session;
class PacketProcessor
{
public:
	PacketProcessor() = default;
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

		auto code = command->GetCode();

		auto iter = mCommands.find(code);

		if (mCommands.end() != iter)
			assert(false && "mCommands.end() != iter");

		mCommands[code] = command;
	}

	void Process(PacketBase* packet, SessionPtr session);

private:
	std::map<unsigned short, ICommand*> mCommands;
};

