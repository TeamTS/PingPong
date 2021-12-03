// Server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "Session.h"

// 서버 아이피 포트
#define IP "127.0.0.1"
#define PORT 30002

std::vector<std::string> commands;


enum class PacketCommand : unsigned short
{
    // 일반 채팅
    CHATTING,
    USER_LIST
};

void ProcessPacket(std::shared_ptr<Session> session)
{

}


int main()
{
    // winsock 초기화
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Failed WSAStartup()" << std::endl;
        return 1;
    }

    SOCKET listenSocket = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET)
        return 1;

    SOCKADDR_IN sockAddr;
    ZeroMemory(&sockAddr, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &sockAddr.sin_addr);

    // 소켓 바인딩
    if (SOCKET_ERROR == bind(listenSocket, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockAddr)))
        return 1;

    if (SOCKET_ERROR == listen(listenSocket, SOMAXCONN))
        return 1;

    std::cout << "연결 대기중...." << std::endl;

    fd_set_ex  socketInfos;
    fd_set_ex  readInfos;
    FD_ZERO_EX(&socketInfos);
    FD_SET_EX(listenSocket, nullptr, &socketInfos);

    int userIndex = 0;
    while (true)
    {
        readInfos = socketInfos; // 감시대상을 넣어준다.

        int ret = select(0, (fd_set*)&readInfos, NULL, NULL, NULL);

        if (SOCKET_ERROR == ret)
        {
            std::cout << "Failed select()" << std::endl;
            break;
        }

        for (u_int i = 0; i < socketInfos.fd_count; ++i)
        {
            SOCKET readSocket = socketInfos.fd_array[i];

            if (FD_ISSET_EX(readSocket, &readInfos))
            {
                // 변화가 있는 대상이 listensocket 인 경우 => accept
                if (readSocket == listenSocket)
                {
                    SOCKADDR_IN clientAddr;
                    int addrLen = sizeof(clientAddr);
                    SOCKET clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);

                    if (INVALID_SOCKET == clientSocket)
                    {
                        std::cout << "clientSocket == INVALID_SOCKET" << std::endl;
                        continue;
                    }

                    if (INVALID_SOCKET == listenSocket)
                    {
                        std::cout << "Failed accept()" << std::endl;
                        return false;
                    }

                    // 세션 생성
                    Session* session = new Session(clientSocket, clientAddr, userIndex++);

                    if (nullptr == session)
                        return false;

                    // 감시 대상에 추가
                    FD_SET_EX(clientSocket, session, &socketInfos);

                    std::cout << "[Info] Connected Socket( " << clientSocket << ")" << std::endl;

                    // 플레이어 인덱스 전송
                    //m_pInGamePacketHandler->SendInitGame(pSession);
                    // test
                    //send(clientSocket, (const char*)&userIndex, sizeof(userIndex), 0);
                    continue;
                }

                auto session = socketInfos.session[i];

                if (nullptr == session)
                {
                    std::cout << "[Error] socket(" << readSocket << ") Invalid Session" << std::endl;
                    FD_CLR_EX(readSocket, &socketInfos);
                    continue;
                }

                if (!session->RecvPacket())
                {
                    std::cout << "[Info] disconnect socket(" << readSocket << ")" << std::endl;
                    // 감시 대상에서 제거한다.
                    FD_CLR_EX(readSocket, &socketInfos);
                    continue;
                }

                // 패킷 처리

            }
        }
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;

}
