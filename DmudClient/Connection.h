#pragma once

#include <iostream>
#include <sstream>
#include <wx/wx.h>
#include <wx/socket.h>

class Connection : public wxSocketClient
{
public:
	Connection();
	~Connection();


	void initialise();

	void read(wxSocketClient * sockConn, char cb[], int & aob, std::string & textrecv, std::vector<std::string>& temp);

	//void read(wxSocketClient * sockConn, char cb[], int & aob, std::string& recv);

	
	std::string textrecv;

	wxSocketClient *sockConn;

	char cb[4096];

	int aob;
};

