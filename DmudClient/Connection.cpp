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

void Connection::Vectorise(std::vector<std::string>& text1, std::vector<std::string> &Seq)
{
	for (size_t i = 0; i < text1.size(); i++)
	{
		if (text1[i][0] == '[')
		{
			int endseq = text1[i].find_first_of('m');
			Seq.emplace_back(text1[i].substr(0, endseq));
			//ansi1.Colours.emplace_back(37);
			ansi1.str.emplace_back(text1[i].substr(endseq + 1, text1[i].npos));
		}
		else
		{
			ansi1.Colours.emplace_back(37);
			ansi1.str.emplace_back(text1[i]);
		}
	}
}

void Connection::ParseSeq(std::vector<std::string> &Seq)
{
	
	for (size_t i = 0; i < Seq.size(); i++)
	{
		if (Seq[i].find(';'))
		{
			int longseq = Seq[i].find(';');
			std::string Colour = Seq[i].substr(longseq + 1, longseq + 2);
			ansi1.Colours.emplace_back(std::stoi(Colour));
		}
		
	}
}

