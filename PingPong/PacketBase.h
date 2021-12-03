#pragma once

#pragma pack(push, 1)
struct PacketBase
{
	unsigned short size; // 패킷 길이
	unsigned short code;

	PacketBase(unsigned short _size, unsigned short _code) 
		: size(_size) 
		, code(_code)
	{ }
};
#pragma pack(pop)
