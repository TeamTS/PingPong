#pragma once
#include "ICommand.h"
class LogicUserId :
    public ICommand
{
    // ICommand을(를) 통해 상속됨
    virtual unsigned short GetCode() override;
    virtual void Execute(PacketBase* packet, SessionPtr session) override;
};

