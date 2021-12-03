#include "pch.h"
#include "LogicUserId.h"
#include "InGamePacket.h"
#include "Session.h"

unsigned short LogicUserId::GetCode()
{
    return static_cast<unsigned short>(ServerPacket::SA_UserId);
}

void LogicUserId::Execute(PacketBase* packet, SessionPtr session)
{
    SA_UserId* convertPacket = reinterpret_cast<SA_UserId*>(packet);

    session->SetUserId(convertPacket->userId);
}
