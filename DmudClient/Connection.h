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

	void read(wxSocketClient * sockConn, char cb[], int & aob, std::vector<char> &text);


	Telnegotiations tel1;

	std::vector<std::string> ESC;
	std::vector<char> text;

	wxSocketClient *sockConn;

	char cb[4096];

	int aob;
};

