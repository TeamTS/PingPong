#pragma once

#include "ICommand.h"

// ���� ���� ó�� 
class LogicGameStart : public ICommand
{
public:
	virtual unsigned short GetCode() override;

	virtual void Execute(PacketBase* packet, Session* session) override;
};

