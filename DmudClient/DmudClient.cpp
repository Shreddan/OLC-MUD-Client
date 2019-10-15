#include "Socket.h"
#include <Windows.h>
#include <wchar.h>
#include <vector>

#include <algorithm>




constexpr int bufflen = 4096;


int main()
{
	
	int recvbufflen = bufflen;
	
	char recvbuf[bufflen];
	std::string in;
	
	fd_set readfs;
	fd_set writefs;
	std::string Neg;
	std::vector<std::string> nego;

	//bool Connected = false;
	Socket sock1;

	sock1.initialiseSocket(sock1.iResult, sock1.ConnectSocket);
	bool Connected = true;

	sock1.sockets[0] = sock1.ConnectSocket;

	FD_ZERO(&readfs);
	FD_ZERO(&writefs);

	FD_SET(sock1.sockets[0], &writefs);
	FD_SET(sock1.sockets[0], &readfs);

	sock1.OnConnect(recvbuf, sock1.iResult, sock1.ConnectSocket, recvbufflen, Neg, nego);
	std::cout << std::endl;
	sock1.Send(in, sock1.iResult, sock1.ConnectSocket);
	
	while (Connected)
	{
		sock1.Communicate(in, sock1.iResult, sock1.ConnectSocket, recvbuf, Neg, recvbufflen, nego, readfs, writefs);
		if (sock1.ConnectSocket == INVALID_SOCKET)
		{
			Connected = false;
		}
	}
	getchar();
	return 0;
}

