#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <wchar.h>
#include <vector>
#include <stdio.h>

#include "Telnet.h"

#pragma comment(lib, "Ws2_32.lib")


 



constexpr int bufflen = 2056;

void OnConnect(char recvbuf[], int iResult, SOCKET ConnectSocket, int recvbufflen, char* sendbuf, std::vector<char>& Neg, std::vector<std::string>& nego)
{
	iResult = 0;
	recvbuf = new char[bufflen];
	while (iResult >= 0)
	{
		iResult = recv(ConnectSocket, recvbuf, recvbufflen, 0);

		if (iResult == 1863)
		{
			for (int i = 0; i < iResult; i++)
			{
				Neg.emplace_back(recvbuf[i]);

				if (Neg[i] == (char)IAC)
				{
					nego.emplace_back(" IAC ");
				}
				if (Neg[i] == (char)WILL)
				{
					nego.emplace_back(" WILL ");
				}
				if (Neg[i] == (char)WONT)
				{
					nego.emplace_back(" WONT ");
				}
				if (Neg[i] == (char)DO)
				{
					nego.emplace_back(" DO ");
				}
				if (Neg[i] == (char)DONT)
				{
					nego.emplace_back(" DONT ");
				}
				if (Neg[i] == (char)GA)
				{
					nego.emplace_back(" GO AHEAD ");
				}
				if (Neg[i] == (char)EL)
				{
					nego.emplace_back(" EL ");
				}
				if (Neg[i] == (char)EC)
				{
					nego.emplace_back(" EC ");
				}
				if (Neg[i] == (char)AYT)
				{
					nego.emplace_back(" AYT ");
				}
				if (Neg[i] == (char)MCCP2)
				{
					nego.emplace_back(" MCCP2 ");
				}
				if (Neg[i] == (char)BEL)
				{
					Beep(300, 500);
				}
				if (Neg[i] == (char)ECHO)
				{
					nego.emplace_back(" ECHO ");
				}
			}
			for (size_t j = 0; j < nego.size(); j++)
			{
				std::cout << nego[j] << " ";
				if (j == 8)
				{
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
			std::cout << std::endl;
			for (size_t k = 24; k < Neg.size() - 1; k++)
			{
				std::cout << Neg[k];
			}

			
			
			break;
		}
	}

	
}

void Receive(int iResult, char recvbuf[], SOCKET ConnectSocket, std::vector<char> Neg, int recvbufflen)
{
	if (iResult >= 0)
	{
		iResult = recv(ConnectSocket, recvbuf, recvbufflen, 0);

		if (iResult > 0)
		{
			for (int i = 0; i <= iResult; i++)
			{
				Neg.emplace_back( recvbuf[i]);
				std::cout << Neg[i] << std::endl;
			}

			
			
		}
	}
}


int main()
{
	SetConsoleCP(437);
	SetConsoleOutputCP(437);

	WSAData wsaData;

	int recvbufflen = bufflen;

	int iResult;
	char *sendbuf = nullptr;
	char *recvbuf = nullptr;

	std::stringstream ss;
	std::vector<char> Neg;
	std::vector<std::string> nego;

	bool Connected = false;


	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return 1;
	}

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("23.111.136.202", "4000", &hints, &result);
	if (iResult != 0) 
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Connection Successful!" << std::endl;
		std::cout << std::endl;
	}

	SOCKET ConnectSocket = INVALID_SOCKET;

	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
		ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << "Unable to connect to server!" << std::endl;
		getchar();
		WSACleanup();
		return 1;
	}

	sendbuf = new char[9];

	sendbuf[0] = 'D';
	sendbuf[1] = 'a';
	sendbuf[2] = 'n';
	sendbuf[3] = 'i';
	sendbuf[4] = 'c';
	sendbuf[5] = 'r';
	sendbuf[6] = 'o';
	sendbuf[7] = 'n';
	sendbuf[8] = '\r';
	sendbuf[9] = '\n';

	OnConnect(recvbuf, iResult, ConnectSocket, recvbufflen, sendbuf, Neg, nego);
	Connected = true;
	send(ConnectSocket, sendbuf, 10, 0);

	while (Connected)
	{
		Receive(iResult, recvbuf, ConnectSocket, Neg, recvbufflen);
	}

	

	return 0;
}

