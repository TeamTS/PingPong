#pragma once

#include "PacketBase.h"

struct ICommand
{
	virtual unsigned short GetCode() = 0;

	virtual void Execute(PacketBase* packet) = 0;
};
