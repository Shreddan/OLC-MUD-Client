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
	sockConn->SetNotify(wxSOCKET_INPUT_FLAG);

}

void Connection::read(wxSocketClient *sockConn, char cb[], int& aob)
{
	sockConn->Read(cb, 4096);
	aob = sockConn->LastReadCount();
}


