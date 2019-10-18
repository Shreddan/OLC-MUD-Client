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
	sockConn->Notify(true);
	
}

void Connection::read(wxSocketClient *sockConn, std::vector<wxString>& recv, int& aob, std::string rec)
{
	char cb[4096];
	std::stringstream ss;
	sockConn->Read(cb, 4096);
	aob = sockConn->LastReadCount();
	for (int i = 24; i < aob; i++)
	{
		ss << cb[i];
	}
	while (std::getline(ss, rec, '\n'))
	{
		recv.push_back(rec);
	}
}




































