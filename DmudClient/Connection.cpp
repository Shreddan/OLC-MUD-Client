#include "Connection.h"



Connection::Connection()
{
	
}


Connection::~Connection()
{
}

//Socket Initialisation
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

//Reading from the Socket
void Connection::read(wxSocketClient *sockConn, int& aob, std::string &out)
{
	char cb[4096];
	sockConn->Read(cb, 4096);
	aob = sockConn->LastReadCount();
	for (int i = 0; i < aob; i++)
	{
		out.push_back(cb[i]);
	}
}

//Splitting printed text from Telnet Negotiations & ANSI Sequences
void Connection::Split(std::string out, std::vector<char>& text)
{
	for (size_t i = 0; i < out.size(); i++)
	{
		if ((uint8_t)out[i] == IAC)
		{
			i += 2;
			continue;
		}
		else
		{
			text.push_back(out[i]);
		}
	}
}


