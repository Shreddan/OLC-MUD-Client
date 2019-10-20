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

	void read(wxSocketClient * sockConn, char cb[], int &aob);

	//void read(wxSocketClient *sockConn, std::vector<char>& recv, int & aob);


	wxSocketClient *sockConn;

	char cb[4096];

	int aob;
};

