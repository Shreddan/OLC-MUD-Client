#pragma once

#include <iostream>
#include <regex>
#include <wx/wx.h>
#include <wx/socket.h>
#include "Ansi.h"
#include "Telnegotiations.h"

class Connection : public wxSocketClient
{
public:
	Connection();
	~Connection();


	void initialise();

	void read(wxSocketClient * sockConn, int & aob, std::string &out);

	void Split(std::string &out, std::vector<std::string>& text);

	void Vectorise(std::vector<std::string>& text1, std::vector<uint8_t>& colour, int & endseq);

	Telnegotiations tel1;
	Ansi ansi1;

	int endseq;

	std::vector<std::string> text1;
	std::string temp;

	std::string out;
	   
	wxSocketClient *sockConn;

	int aob;
};

