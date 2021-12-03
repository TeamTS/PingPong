#pragma once

#include "PacketBase.h"
#include "PacketCommand.h"
#include "Vector2.h"

#pragma pack(push, 1)

struct SA_UserId : public PacketBase
{
	int userId;

	SA_UserId() : PacketBase(sizeof(SA_UserId), static_cast<unsigned short>(ServerPacket::SA_UserId)) { }
};


struct SN_GameStart : public PacketBase
{
	// 예를들어 공 스폰 위치?
	Vector2 ballSpawnPos;

	SN_GameStart() : PacketBase(sizeof(SN_GameStart), static_cast<unsigned short>(ServerPacket::SN_GameStart)) { }
};

#pragma pack(pop)