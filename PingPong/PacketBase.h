#pragma once

#pragma pack(push, 1)
struct PacketBase
{
	unsigned short size; // ��Ŷ ����
	unsigned short code;

	PacketBase(unsigned short _size, unsigned short _code) 
		: size(_size) 
		, code(_code)
	{ }
};
#pragma pack(pop)
