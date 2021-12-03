#pragma once

#include "ICommand.h"

// 게임 시작 처리 
class LogicGameStart : public ICommand
{
public:
	virtual unsigned short GetCode() override;

	virtual void Execute(PacketBase* packet, Session* session) override;
};

