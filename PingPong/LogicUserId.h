#pragma once
#include "ICommand.h"
class LogicUserId :
    public ICommand
{
    // ICommand��(��) ���� ��ӵ�
    virtual unsigned short GetCode() override;
    virtual void Execute(PacketBase* packet, SessionPtr session) override;
};

