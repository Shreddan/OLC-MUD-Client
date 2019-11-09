#include "Connection.h"



Connection::Connection()
{
	this->address = "";
	this->port = 0;
}


Connection::~Connection()
{
}

//Socket Initialisation
void Connection::initialise()
{
	sockConn = new wxSocketClient();
	wxIPV4address addr;
	addr.Hostname(address);
	addr.Service(port);
	if (!sockConn->Connect(addr, true)) {
		std::cout << "Connect failed" << std::endl;
	}
	sockConn->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_OUTPUT_FLAG);

}

//Reading from the Socket
void Connection::read(wxSocketClient *sockConn, int& aob, std::string &out) {
	char cb[4096];
	sockConn->Read(cb, 4096);
	aob = sockConn->LastReadCount();
	for (int i = 0; i < aob; i++)
	{
		out.push_back(cb[i]);
	}
}

//Splitting printed text from Telnet Negotiations & ANSI Sequences
void Connection::Split(std::string& out, std::vector<std::string>& text)
{
	std::stringstream ss;
	for (size_t i = 0; i < out.size(); i++)
	{
		if ((uint8_t)out[i] == IAC)
		{
			tel1.Negotiations.emplace_back((uint8_t)out[i], (uint8_t)out[i + 1], (uint8_t)out[i + 2]);
			i += 2;
			continue;
		}
		else
		{
			ss << out[i];

		}
	}
	
	while (std::getline(ss, temp, (char)0x001B))
	{
		text.emplace_back(temp);
	}
}
int Connection::ParseSeq(std::string &par)
{
	int col = 37;
	if (par.find(';'))
	{
		int longseq = par.find(';');
		std::string Colour = par.substr(longseq + 1, longseq + 2);
		col = std::stoi(Colour);
	}
	return col;
}

void Connection::Vectorise(std::vector<std::string>& text1, std::vector<std::string> &Seq)
{
	std::string par;
	for (size_t i = 0; i < text1.size(); i++)
	{
		if (text1[i][0] == '[')
		{
			int endseq = text1[i].find_first_of('m');
			if (endseq > 3)
			{
				par = text1[i].substr(0, endseq);
				ansi1.Colours.emplace_back(ParseSeq(par));
				ansi1.str.emplace_back(text1[i].substr(endseq + 1, text1[i].npos));
			}
			else
			{
				par = text1[i].substr(1, endseq - 1);
				ansi1.Colours.emplace_back(std::stoi(par));
				std::string text = text1[i].substr(endseq + 1, text1[i].npos);
				ansi1.str.emplace_back(text);
			}
		}
		else
		{
			ansi1.Colours.emplace_back(37);
			ansi1.str.emplace_back(text1[i]);
		}
		
	}
}



