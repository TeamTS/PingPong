#include "pch.h"
#include "LogicGameStart.h"
#include "InGamePacket.h"

unsigned short LogicGameStart::GetCode()
{
    return static_cast<unsigned short>(ServerPacket::SN_GameStart);
}

void LogicGameStart::Execute(PacketBase* packet, Session* session)
{
    // ���⼭ GameStart ��Ŷ ó���Ұ�
    SN_GameStart* convertPacket = reinterpret_cast<SN_GameStart*>(packet);

    // ���⼭ ���� ��Ŷ ó��

}
