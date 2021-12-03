#include "pch.h"
#include "LogicGameStart.h"
#include "InGamePacket.h"

unsigned short LogicGameStart::GetCode()
{
    return static_cast<unsigned short>(ServerPacket::SN_GameStart);
}

void LogicGameStart::Execute(PacketBase* packet, Session* session)
{
    // 여기서 GameStart 패킷 처리할거
    SN_GameStart* convertPacket = reinterpret_cast<SN_GameStart*>(packet);

    // 여기서 이제 패킷 처리

}
