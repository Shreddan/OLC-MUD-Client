#pragma once

#include <iostream>
#include <wx/wx.h>
#include <wx/socket.h>

class Connection : public wxSocketClient
{
public:
	Connection();
	~Connection();


	void initialise();

	void read(wxSocketClient * sockConn, char cb[], std::vector<char>& recv, int& aob);


	wxSocketClient *sockConn;

	char *cb;

	int aob;
};

