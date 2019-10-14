#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

class Socket
{
public:
	Socket();
	~Socket();

	void initialiseSocket(int &iResult, SOCKET &ConnectSocket);

	WSAData wsaData;
	SOCKET ConnectSocket;
	SOCKET sockets[1];
	int iResult;

};

