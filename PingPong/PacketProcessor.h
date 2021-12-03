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

		auto code = command->GetCode(); // �ش� ��Ŷ ó����ü�� command���� ������.

		auto iter = mCommands.find(code);

		if (mCommands.end() != iter)
			assert(false && "mCommands.end() != iter");

		mCommands[code] = command;
	}

	void Process(PacketBase* packet, Session* session);

	void Initialize()
	{
		// ��Ŷ ó�� ��ü ���
		Register(new LogicGameStart);
	}

private:
	// packet command, command object

	// key : ��Ŷ ���� ��ȣ, value : ��Ŷ ó�� ��ü 
	std::map<unsigned short, ICommand*> mCommands;
};

