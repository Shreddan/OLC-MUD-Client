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
	sockConn->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_OUTPUT_FLAG);

}

void Connection::read(wxSocketClient *sockConn, char cb[], int& aob, std::string& textrecv, std::vector<std::string>& temp)
{
	std::stringstream ss;
	sockConn->Read(cb, 4096);
	aob = sockConn->LastReadCount();
	for (int i = 0; i < aob; i++)
	{
		ss << cb[i];
	}
	while (std::getline(ss, textrecv, (char)0x001B))
	{
		temp.push_back(textrecv);
	}
	
	
}


