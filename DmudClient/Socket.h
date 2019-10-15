#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>

#include "Telnet.h"

#pragma comment(lib, "Ws2_32.lib")


class Socket
{
public:
	Socket();
	~Socket();

	void initialiseSocket(int &iResult, SOCKET &ConnectSocket);
	void Send(std::string& in, int iResult, SOCKET ConnectSocket);

	void ParseTelnet(std::string Neg, std::vector<std::string>& nego);

	void OnConnect(char recvbuf[], int iResult, SOCKET ConnectSocket, int recvbufflen, std::string & Neg, std::vector<std::string>& nego);

	void Receive(int iResult, char recvbuf[], SOCKET ConnectSocket, std::string & Neg, int recvbufflen, std::vector<std::string>& nego);

	void Communicate(std::string & in, int iResult, SOCKET ConnectSocket, char recvbuf[], std::string & Neg, int & recvbufflen, std::vector<std::string>& nego, fd_set readfs, fd_set writefs);

	WSAData wsaData;
	SOCKET ConnectSocket;
	SOCKET sockets[1];
	int iResult;

};

