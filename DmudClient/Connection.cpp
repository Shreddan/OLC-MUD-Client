#include "Connection.h"



Connection::Connection()
{
	
}


Connection::~Connection()
{
}

void Connection::initialise()
{
	sockConn = new wxSocketClient();
	wxIPV4address addr;
	addr.Hostname(wxT("23.111.136.202"));
	addr.Service(4000);
	if (!sockConn->Connect(addr, true)) {
		std::cout << "Connect failed" << std::endl;
	}
	
}

void Connection::read(wxSocketClient *sockConn, char cb[], std::vector<char>& recv, int& aob)
{
	cb = new char[2048];
	sockConn->Read(cb, 2048);
	aob = sockConn->LastReadCount();
	for (int i = 0; i < aob; i++)
	{
		recv.emplace_back(cb[i]);
	}
}            






























