#include "Socket.h"
#include <Windows.h>
#include <sstream>
#include <wchar.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "Telnet.h"



constexpr int bufflen = 2048;

void prettify(std::string& Neg)
{
	std::remove_if(Neg.begin(), Neg.end(), [](const char c) {return c == '[' || c == '{'; });
}

void Send(std::string& in, int iResult, SOCKET ConnectSocket)
{
	std::getline(std::cin, in);
	in += "\n";
	iResult = send(ConnectSocket, in.c_str(), in.size(), 0);
}

void ParseTelnet(std::string Neg, std::vector<std::string>& nego)
{
	for (size_t i = 0; i < Neg.size(); i++)
	{
		if (Neg[i] == (char)IAC)
		{
			nego.emplace_back(" IAC ");
		}
		else if (Neg[i] == (char)ENV)
		{
			nego.emplace_back(" ENV ");
		}
		else if (Neg[i] == (char)MSP)
		{
			nego.emplace_back(" MSP ");
		}
		/*else if (Neg[i] == (char)MXP)
		{
			nego.emplace_back(" MXP ");
		}*/
		/*else if (Neg[i] == (char)ZMP)
		{
			nego.emplace_back(" ZMP ");
		}*/
		else if (Neg[i] == (char)WILL)
		{
			nego.emplace_back(" WILL ");
		}
		else if (Neg[i] == (char)WONT)
		{
			nego.emplace_back(" WONT ");
		}
		else if (Neg[i] == (char)DO)
		{
			nego.emplace_back(" DO ");
		}
		else if (Neg[i] == (char)DONT)
		{
			nego.emplace_back(" DONT ");
		}
		else if (Neg[i] == (char)GA)
		{
			nego.emplace_back(" GO AHEAD ");
		}
		else if (Neg[i] == (char)EL)
		{
			nego.emplace_back(" EL ");
		}
		else if (Neg[i] == (char)EC)
		{
			nego.emplace_back(" EC ");
		}
		else if (Neg[i] == (char)AYT)
		{
			nego.emplace_back(" AYT ");
		}
		else if (Neg[i] == (char)MCCP1)
		{
			nego.emplace_back(" MCCP1 ");
		}
		else if (Neg[i] == (char)MCCP2)
		{
			nego.emplace_back(" MCCP2 ");
		}
		else if (Neg[i] == (char)BEL)
		{
			Beep(300, 500);
		}
		else if (Neg[i] == (char)ECHO)
		{
			nego.emplace_back(" ECHO ");
		}
		else if (Neg[i] == (char)IP)
		{
			nego.emplace_back(" IP ");
		}
		else if (Neg[i] == (char)BRK)
		{
			nego.emplace_back(" BREAK ");
		}
		else if (Neg[i] == (char)DM)
		{
			nego.emplace_back(" DM ");
		}
		else if (Neg[i] == (char)NOP)
		{
			nego.emplace_back(" NO-OPERATION ");
		}
		else if (Neg[i] == (char)EOR)
		{
			nego.emplace_back(" EOR ");
		}
		else if (Neg[i] == (char)GMCP)
		{
			nego.emplace_back(" GMCP ");
		}
		/*else if (Neg[i] == (char)MSDP)
		{
			nego.emplace_back(" MSDP ");
		}*/
		else if (Neg[i] == (char)MSSP)
		{
			nego.emplace_back(" MSSP ");
		}
		else if (Neg[i] == (char)MTTS)
		{
			nego.emplace_back(" MTTS ");
		}
		else if (Neg[i] == (char)NAWS)
		{
			nego.emplace_back(" NAWS ");
		}
		else if (Neg[i] == (char)SUPPRGA)
		{
			nego.emplace_back(" SUPPRESS GO-AHEAD ");
		}
		else if (Neg[i] == (char)SB)
		{
			nego.emplace_back(" SB ");
		}
		else if (Neg[i] == (char)SE)
		{
			nego.emplace_back(" SE ");
		}
		else if (Neg[i] == (char)ABRT)
		{
			nego.emplace_back(" ABORT ");
		}
		else if (Neg[i] == (char)XEOF)
		{
			nego.emplace_back(" XEOF ");
		}
		else if (Neg[i] == (char)ATCP)
		{
			nego.emplace_back(" ATCP ");
		}
		else if (Neg[i] == (char)EXTASC)
		{
			nego.emplace_back(" EXTENDED ASCII ");
		}
		else if (Neg[i] == (char)STATUS)
		{
			nego.emplace_back(" STATUS ");
		}
		else if (Neg[i] == (char)TIMINGMARK)
		{
		nego.emplace_back(" TIMING-MARK ");
		}
	}
}

void OnConnect(char recvbuf[], int iResult, SOCKET ConnectSocket, int recvbufflen, std::string& Neg, std::vector<std::string>& nego)
{
	iResult = recv(ConnectSocket, recvbuf, recvbufflen, 0);
	if (iResult > 0)
	{

		for (int i = 0; i < iResult; i++)
		{
			Neg.push_back(recvbuf[i]);
		}
		if (Neg.size() > 0)
		{
			ParseTelnet(Neg, nego);
		}
			for (size_t j = 0; j < nego.size(); j++)
			{
				std::cout << nego[j] + " ";
				if (j == 13)
				{
					std::cout << std::endl;
				}
			}
			//std::cout << nego.size() << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			for (size_t k = 24; k < Neg.size(); k++)
			{
				std::cout << Neg[k];
			}
	}	
}

void Receive(int iResult, char recvbuf[], SOCKET ConnectSocket, std::string& Neg, int recvbufflen, std::vector<std::string>& nego)
{
	memset(recvbuf, 0, recvbufflen);
	Neg.clear();
	if (iResult >= 0)
	{
		iResult = recv(ConnectSocket, recvbuf, recvbufflen, 0);
		if (iResult > 0)
		{
			for (int i = 0; i <= iResult; i++)
			{
				Neg.push_back(recvbuf[i]);
			}
			if (Neg.size() > 0)
			{
				//prettify(Neg);
			}
			for (int j = 0; j < Neg.size(); j++)
			{
				std::cout << Neg[j];
			}
			
		}
	}
}

void Communicate(std::string &in, int iResult, SOCKET ConnectSocket, char recvbuf[], std::string &Neg, int &recvbufflen, std::vector<std::string> &nego, fd_set readfs, fd_set writefs)
{
	if (select(0, &readfs, 0, 0, 0))
	{
		Receive(iResult, recvbuf, ConnectSocket, Neg, recvbufflen, nego);
	}
	if (select(0, 0, &writefs, 0, 0))
	{
		Send(in, iResult, ConnectSocket);
	}
}


int main()
{
	SetConsoleCP(437);
	SetConsoleOutputCP(437);
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
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

	OnConnect(recvbuf, sock1.iResult, sock1.ConnectSocket, recvbufflen, Neg, nego);
	std::cout << std::endl;
	Send(in, sock1.iResult, sock1.ConnectSocket);
	
	while (Connected)
	{
		Communicate(in, sock1.iResult, sock1.ConnectSocket, recvbuf, Neg, recvbufflen, nego, readfs, writefs);
		if (sock1.ConnectSocket == INVALID_SOCKET)
		{
			Connected = false;
		}
	}
	getchar();
	return 0;
}

