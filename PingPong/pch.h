#pragma once


#include <WinSock2.h>
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <process.h>
#include <exception>
#include <iostream>
#include <tchar.h>
#include <deque>
#include <queue>
#include <fstream>
#include <unordered_map>
#include <cassert>
#include <functional>
#include <array>
#include <assert.h>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <type_traits>
#include <memory>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

#include "Singleton.h"
#include "PacketBase.h"

class Session;
using SessionPtr = std::shared_ptr<Session>;

#define WINCX 1280
#define WINCY 720