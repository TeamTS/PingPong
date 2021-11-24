#include "pch.h"
#include "PacketProcessor.h"

void PacketProcessor::Process(PacketBase* packet, SessionPtr session)
{
	auto iter = mCommands.find(packet->command);

	if (iter == mCommands.end())
	{
		assert(false && "iter == mCommands.end()");
		return;
	}

	iter->second->Execute(packet);
}	
