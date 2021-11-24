#include "pch.h"
#include "NetworkManager.h"
#include "Session.h"

NetworkManager* NetworkManager::mInstance = nullptr;

NetworkManager& NetworkManager::GetInstance()
{
	if (mInstance == nullptr)
		mInstance = new NetworkManager;

	return *mInstance;
}

bool NetworkManager::Initialize()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		assert(false && "Failed WSAStartUp()");
		return E_FAIL;
	}



	//m_tServAddr.sin_family = AF_INET;
	//m_tServAddr.sin_port = htons(_wPort);
	//inet_pton(AF_INET, _pszIpAddress, &m_tServAddr.sin_addr);
    return false;
}

bool NetworkManager::Connect(SessionType sessionType, const char* ip, unsigned short port)
{
	auto iter = mSessions.find(sessionType);

	if (iter != mSessions.end())
		return false;

	auto session = std::make_shared<Session>();

	if (session->Initialize() == false)
		return false;

	if (session->Connect(ip, port) == false)
		return false;

	mSessions.insert(Sessions::value_type(sessionType, session));
		
	return true;
}

void NetworkManager::Update()
{

}

void NetworkManager::Run()
{

}

