#include "pch.h"
#include "PacketProcessor.h"

void PacketProcessor::Process(PacketBase* packet, SessionPtr session)
{
	auto command = reinterpret_cast<unsigned short>(packet + sizeof(PacketBase));
	auto iter = mCommands.find(command);

	if (iter == mCommands.end())
	{
		assert(false && "iter == mCommands.end()");
		return;
	}

	iter->second->Execute(packet, session);
}	
