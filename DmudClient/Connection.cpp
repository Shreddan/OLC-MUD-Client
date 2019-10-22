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

void Connection::read(wxSocketClient *sockConn, char cb[], int& aob, std::vector<char> &text)
{

	sockConn->Read(cb, 4096);
	aob = sockConn->LastReadCount();
	for (int i = 0; i < aob; i++)
	{
		if (cb[i] > (char)128)
		{
			tel1.singulars.emplace_back(cb[i]);
		}
		else
		{
			 text.push_back(cb[i]);
		}
	}
	
	
}


