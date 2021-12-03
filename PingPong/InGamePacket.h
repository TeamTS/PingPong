#pragma once

#include "PacketBase.h"
#include "PacketCommand.h"
#include "Vector2.h"

struct SN_GameStart : public PacketBase
{
	static unsigned short code; 

	// 예를들어 공 스폰 위치?
	Vector2 ballSpawnPos;

};
unsigned short SN_GameStart::code = static_cast<unsigned short>(ServerPacket::SN_GameStart);