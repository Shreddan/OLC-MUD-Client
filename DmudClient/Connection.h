#pragma once

#include <iostream>
#include <sstream>
#include <wx/wx.h>
#include <wx/socket.h>
#include "Telnegotiations.h"

class Connection : public wxSocketClient
{
public:
	Connection();
	~Connection();


	void initialise();

	void read(wxSocketClient * sockConn, int & aob, std::string &out);

	void Split(std::string out, std::vector<char> &text);

	Telnegotiations tel1;

	std::vector<std::string> ESC;
	std::vector<char> text;

	std::string out;
	   
	wxSocketClient *sockConn;

	int aob;
};

