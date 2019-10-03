#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

constexpr int bufflen = 2048;


int main()
{
	WSAData wsaData;

	int recvbufflen = bufflen;

	int iResult;
	char *sendbuf = nullptr;
	char recvbuf[bufflen];


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

	do {
		iResult = recv(ConnectSocket, recvbuf, recvbufflen, 0);
		if (iResult > 0)
		{
			std::cout << recvbuf << std::endl;
		}
		else if (iResult == 0)
		{
			return 2;  
		}
		else
			printf("recv failed: %d\n", WSAGetLastError());
	} while (iResult > 0);

	getchar();


	return 0;
}

