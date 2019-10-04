#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <wchar.h>
//#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define SE 240
#define NOP 241
#define DM 242
#define BRK 243
#define IP 244
#define AO 245
#define AYT 246
#define EC 247
#define EL 248
#define GA 249
#define SB 250
#define WILL 251
#define WONT 252
#define DO 253
#define DONT 254
#define IAC 255



constexpr int bufflen = 2056;

void Receive(char recvbuf[], int iResult, SOCKET ConnectSocket, int recvbufflen, std::stringstream &ss, char *sendbuf[])
{
	while (iResult >= 0)
	{
		iResult = recv(ConnectSocket, recvbuf, recvbufflen, 0);

		if (iResult > 0)
		{
			ss << recvbuf;
			std::cout << ss.str() << std::endl;
		}
	}

	
}


int main()
{
	SetConsoleMode(GetConsoleWindow(), ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	WSAData wsaData;

	int recvbufflen = bufflen;

	int iResult;
	char *sendbuf = nullptr;
	char recvbuf[bufflen];

	std::stringstream ss;




	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
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
	if (iResult != 0) {
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
		WSACleanup();
		return 1;
	}


	sendbuf = new char[3];
	sendbuf[0] = ' ';
	sendbuf[1] = '²';
	sendbuf[2] = 'V';

	
	Receive(recvbuf, iResult, ConnectSocket, recvbufflen, ss, &sendbuf);
	

	getchar();


	return 0;
}

